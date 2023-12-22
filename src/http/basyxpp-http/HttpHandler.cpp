#include "HttpHandler.h"

#include <basyx/serialization/json/serializer.h>

#include <basyx/util/algorithm/string.hpp>

namespace basyx {
namespace http {

using json_t = basyx::serialization::json::json_t;

HttpHandler::HttpHandler(util::string_view host, int port)
	: host(host.to_string()), port(port)
{
	server.Get("/shells/?", [this](const httplib::Request& req, httplib::Response& res)
	{
		auto shells = this->api->getAssetAdministrationShells();

		auto aas_list = json_t::array();
		for (const auto & shell : shells) {
			aas_list.emplace_back(basyx::serialization::json::serialize(*shell));
		};

		res.set_content(aas_list.dump(4), "application/json");
		res.status = 200;
	});

	server.Get(R"(/shells/(\w+)(?:/|(?:/aas/?))?)", bind_front_handler(&HttpHandler::handle_get_aas));

	server.Get(R"(/shells/(\w+)/aas/submodels/?)", [this](const httplib::Request& req, httplib::Response& res)
	{
		auto aas_id = req.matches[1];
		auto shell = this->api->getAssetAdministrationShellByIdShort(aas_id.str());

		if (!shell) {
			res.status = 404;
			return;
		};

		auto submodel_list = json_t::array();

		for (const auto & submodel : shell->getSubmodels()) {
			submodel_list.emplace_back(basyx::serialization::json::serialize(*submodel));
		};

		res.set_content(submodel_list.dump(4), "application/json");
		res.status = 200;
	});

	server.Get(R"(/shells/(\w+)/aas/submodels/(\w+)(?:/|(?:/submodel/?))?)", [this](const httplib::Request& req, httplib::Response& res)
	{
		auto aas_id = req.matches[1];
		auto submodel_id = req.matches[2];

		auto shell = this->api->getAssetAdministrationShellByIdShort({ aas_id.first, aas_id.second });

		if (!shell) {
			res.status = 404;
			return;
		};

		auto submodel = shell->getSubmodels().get({submodel_id.first, submodel_id.second});
		if (!submodel) {
			res.status = 404;
			return;
		};

		res.set_content(basyx::serialization::json::serialize(*submodel).dump(4), "application/json");
		res.status = 200;
	});

	server.Get(R"(/shells/(\w+)/aas/submodels/(\w+)/submodel/submodelElements/?)", [this](const httplib::Request& req, httplib::Response& res)
	{
		auto aas_id = req.matches[1];
		auto submodel_id = req.matches[2];

		auto shell = this->api->getAssetAdministrationShellByIdShort(aas_id.str());

		if (!shell) {
			res.status = 404;
			return;
		};

		auto submodel = shell->getSubmodels().get(submodel_id.str());
		if (!submodel) {
			res.status = 404;
			return;
		};

		auto sel_list = json_t::array();
		for (const auto & element : submodel->getSubmodelElements()) {
			sel_list.emplace_back(basyx::serialization::json::serialize(*element));
		};

		res.set_content(sel_list.dump(4), "application/json");
		res.status = 200;
	});

	server.Get(R"(/shells/(\w+)/aas/submodels/(\w+)/submodel/submodelElements/((?:\w|/)+)/value)", [this](const httplib::Request& req, httplib::Response& res)
	{
		auto aas_id = req.matches[1];
		auto submodel_id = req.matches[2];
		auto path = util::string_view{ req.matches[3].first, req.matches[3].second };

		auto shell = this->api->getAssetAdministrationShellByIdShort(aas_id.str());
		if (!shell) {
			res.status = 404;
			return;
		};

		auto submodel = shell->getSubmodels().get(submodel_id.str());
		if (!submodel) {
			res.status = 404;
			return;
		};

		auto path_splits = util::algorithm::string::split(path, '/');
		if (path_splits.empty()) {
			res.status = 404;
			return;
		};

		auto it = path_splits.begin();

		auto element = submodel->getSubmodelElements().get(*it);
		if (element == nullptr) {
			res.status = 404;
			return;
		};

		for (++it; it != path_splits.end(); ++it) {
			if (SubmodelElementHelper::IsSubmodelElementCollection(*element)) {
				auto coll = SubmodelElement::element_cast<SubmodelElementCollection>(element);
				element = coll->getSubmodelElements().get(*it);

				if (element == nullptr) {
					res.status = 404;
					return;
				};
			}
			else {
				res.status = 404;
				return;
			};
		}

		if (SubmodelElementHelper::IsProperty(*element)) {
			auto prop = SubmodelElement::element_cast<Property>(element);
			if (prop->has_value()) {
				auto value = prop->get_value_string();
				res.set_content( json_t(value).dump(4), "application/json");
			}
			else {
				res.set_content("{}", "application/json");
			};
			res.status = 200;
			return;
		};

		res.status = 404;
	});

	server.Put(R"(/shells/(\w+)/aas/submodels/(\w+)/submodel/submodelElements/((?:\w|/)+)/value)", [this](const httplib::Request& req, httplib::Response& res)
		{
			auto aas_id = req.matches[1];
			auto submodel_id = req.matches[2];
			auto path = util::string_view{ req.matches[3].first, req.matches[3].second };

			auto value = json_t::parse(req.body);
			if (!value.is_primitive()) {
				res.status = 400;
				return;
			}

			auto shell = this->api->getAssetAdministrationShellByIdShort(aas_id.str());
			if (!shell) {
				res.status = 404;
				return;
			};

			auto submodel = shell->getSubmodels().get(submodel_id.str());
			if (!submodel) {
				res.status = 404;
				return;
			};

			auto path_splits = util::algorithm::string::split(path, '/');
			if (path_splits.empty()) {
				res.status = 404;
				return;
			};

			auto it = path_splits.begin();

			auto element = submodel->getSubmodelElements().get(*it);
			if (element == nullptr) {
				res.status = 404;
				return;
			};

			for (++it; it != path_splits.end(); ++it) {
				if (SubmodelElementHelper::IsSubmodelElementCollection(*element)) {
					auto coll = SubmodelElement::element_cast<SubmodelElementCollection>(element);
					element = coll->getSubmodelElements().get(*it);

					if (element == nullptr) {
						res.status = 404;
						return;
					};
				}
				else {
					res.status = 404;
					return;
				};
			}

			if (SubmodelElementHelper::IsProperty(*element)) {
				auto prop = SubmodelElement::element_cast<Property>(element);
				prop->assign(req.body);
				res.status = 204;
				return;
			};

			res.status = 404;
		});

	server.Get(R"(/shells/(\w+)/aas/submodels/(\w+)/submodel/submodelElements/((?:\w|/)+))", [this](const httplib::Request& req, httplib::Response& res)
	{
		auto aas_id = req.matches[1];
		auto submodel_id = req.matches[2];
		auto path = util::string_view{ req.matches[3].first, req.matches[3].second };

		auto shell = this->api->getAssetAdministrationShellByIdShort(aas_id.str());
		if (!shell) {
			res.status = 404;
			return;
		};

		auto submodel = shell->getSubmodels().get(submodel_id.str());
		if (!submodel) {
			res.status = 404;
			return;
		};


		auto path_splits = util::algorithm::string::split(path, '/');
		if(path_splits.empty()) {
			res.status = 404;
			return;
		};

		auto it = path_splits.begin();

		auto element = submodel->getSubmodelElements().get(*it);
		if(element == nullptr) {
			res.status = 404;
			return;
		};

		for (++it; it != path_splits.end(); ++it) {
			if (SubmodelElement::is_element_type<SubmodelElementCollection>(element)) {
				auto coll = SubmodelElement::element_cast<SubmodelElementCollection>(element);
				element = coll->getSubmodelElements().get(*it);

				if (element == nullptr) {
					res.status = 404;
					return;
				};
			}
			else {
				res.status = 404;
				return;
			};
		}

		res.set_content(basyx::serialization::json::serialize(*element).dump(4), "application/json");
		res.status = 200;
	});
};

void HttpHandler::handle_get_aas(const httplib::Request& req, httplib::Response& res)
{
	auto aas_id = req.matches[1];

	auto shell = this->api->getAssetAdministrationShellByIdShort(aas_id.str());
	if (!shell) {
		res.status = 404;
		return;
	}

	res.set_content(basyx::serialization::json::serialize(*shell).dump(4), "application/json");
	res.status = 200;
};

void HttpHandler::run()
{
	std::cout << "Starting server on " << host << ":" << port << std::endl;
	if (!server.bind_to_port(host.c_str(), port))
		throw std::runtime_error("port not available!");

	server.listen_after_bind();
}

void HttpHandler::stop() 
{
	server.stop();
}

}
}
