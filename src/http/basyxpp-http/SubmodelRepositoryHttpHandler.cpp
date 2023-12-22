//#include "SubmodelRepositoryHttpHandler.h"
//
//#include <basyx/serialization/json/serializer.h>
//
//#include <spdlog/fmt/ostr.h>
//#include <spdlog/spdlog.h>
//
//#include <iostream>
//
//using namespace basyx::http;
//using namespace httplib;
//using namespace basyx;
//
//const std::string regex_idShort = "([a-zA-Z][a-zA-Z0-9_]+)";
//const std::string regex_idShortPath = "([a-zA-Z][a-zA-Z0-9_/]+)";
//
//SubmodelRepositoryHttpHandler::SubmodelRepositoryHttpHandler(std::string ip, uint16_t port, int json_intend_level) :
//	HttpHandler(ip, port, json_intend_level)
//{}
//
//template<typename T>
//inline util::string_view view_from_match(const T & t) {
//	return util::string_view(&(*t.first), t.length());
//}
//
//void SubmodelRepositoryHttpHandler::registerHandleRequests()
//{
//	// Retrieves all Submodels
//	server.Get("/submodels/?",
//		[](const Request& req, Response& res)
//	{
//		res.set_content("TODO: Implement view of hosted submodels!", TXT_PLAIN);
//		spdlog::info("GET all submodels");
//	});
//
//	// Retrieves the entire Submodel for "/submodels/{submodelId}" and "/submodels/{submodelId}/submodel"
//	server.Get("/submodels/" + regex_idShort + "(/submodel/?)?",
//		[this](const Request& req, Response& res)
//	{
//		auto idShort = view_from_match(req.matches[1]);
//		spdlog::info("GET submodel: {}", idShort);
//
//		auto sm = getSubmodel(idShort);
//
//		if (!sm)
//			return submodel_not_found(idShort, res);
//
//		auto interface_response = sm->getSubmodel(regular_om);
//		response_message_with_content(interface_response, res);
//	});
//
//	// Creates or updates a Submodel at the Submodel repository
//	server.Put("/submodels/" + regex_idShort,
//		[this](const Request& req, Response& res)
//	{
//		std::cout << "PUT Handler: " << req.matches[1] << std::endl;
//		std::cout << req.body << std::endl;
//
//		spdlog::warn("PUT of submodel not implemented!");
//		res.set_content("PUT of submodel not implemented!", TXT_JSON);
//	});
//
//	// Deletes a specific Submodel at the Submodel repository
//	server.Delete("/submodels/" + regex_idShort + "/?",
//		[this](const Request& req, Response& res)
//	{
//		auto idShort = view_from_match(req.matches[1]);
//		spdlog::info("Delete submodel: {}", idShort);
//
//		this->submodels.erase(idShort.to_string());
//		res.set_content("Deleted!", TXT_PLAIN);
//		res.status = 200;
//	});
//
//	// Retrieves the minimized version of a Submodel, i.e. only the values of SubmodelElements are serialized and returned
//	server.Get("/submodels/" + regex_idShort + "/submodel/values/?",
//		[this](const Request& req, Response& res)
//	{
//		auto idShort = view_from_match(req.matches[1]);
//		spdlog::info("GET submodel values: {}", idShort);
//
//		auto sm = getSubmodel(idShort);
//
//		if (!sm)
//			return submodel_not_found(idShort, res);
//
//		auto interface_response = sm->getSubmodel(regular_om);
//		response_message_with_content_values(interface_response, res);
//	});
//
//	// Retrieves all Submodel-Elements from the Submodel
//	server.Get("/submodels/" + regex_idShort + "/submodel/submodelElements/?",
//		[this](const Request& req, Response& res)
//	{
//		spdlog::warn("Method not yet implementd!");
//		res.set_content("Method not yet implementd!", TXT_PLAIN);
//
//		//TODO implement ElementContainer serialization
//	//		auto idShort = view_from_match(req.matches[1]);
//	//		spdlog::info("GET submodel elements: {}", idShort);
//	//
//	//    auto sm = getSubmodel(idShort);
//	//
//	//    if (!sm)
//	//      return submodel_not_found(idShort, res);
//	//
//	//    auto interface_response = sm->getAllSubmodelElements(DepthEnum::NonRecursive, regular_om);
//	//    response_message_with_content(interface_response, res);
//	});
//
//	// Creates or updates a Submodel-Element at the Submodel
//	server.Put("/submodels/" + regex_idShort + "/submodel/submodelElements/" + regex_idShortPath,
//		[this](const Request& req, Response& res)
//	{
//		spdlog::warn("Method not yet implementd!");
//		res.set_content("Method not yet implementd!", TXT_PLAIN);
//
//		//    auto idShort = view_from_match(req.matches[1]);
//		//    spdlog::info("PUT submodel elements: {}", idShort);
//		//
//		//    auto sm = getSubmodel(idShort);
//		//
//		//    if (!sm)
//		//      return submodel_not_found(idShort, res);
//		//
//		//    Reference path{idShort};
//		//    TODO: implement SubmodelElement deserialization
//		//    SubmodelElement element = deserialize(req.body)
//		//    auto interface_response = sm->putSubmodelElementByPath(path, element);
//		//    response_message_with_content(interface_response, res);
//	});
//
//	// Retrieves a specific Submodel-Element from the Submodel
//	server.Get("/submodels/" + regex_idShort + "/submodel/submodelElements/" + regex_idShortPath,
//		[this](const Request& req, Response& res)
//	{
//		auto idShort = view_from_match(req.matches[1]);
//		auto idShortPath = view_from_match(req.matches[2]);
//
//		spdlog::info("GET submodelElements: {}/{}", idShort, idShortPath);
//
//		auto sm = getSubmodel(idShort);
//
//		if (!sm)
//			return submodel_not_found(idShort, res);
//
//		Reference ref(idShortPath);
//		auto interface_response = sm->getSubmodelElementByPath(ref, regular_om);
//
//		response_message_with_content(interface_response, res);
//	});
//
//	// Deletes a specific Submodel-Element from the Submodel
//	server.Delete("/submodels/" + regex_idShort + "/submodel/submodelElements/" + regex_idShortPath,
//		[this](const Request& req, Response& res)
//	{
//		auto idShort = view_from_match(req.matches[1]);
//		auto idShortPath = view_from_match(req.matches[2]);
//
//		spdlog::info("GET submodelElements: {}/{}", idShort, idShortPath);
//
//		auto sm = getSubmodel(idShort);
//
//		if (!sm)
//			return submodel_not_found(idShort, res);
//
//		Reference ref(idShortPath);
//		api::StatusCode statusCode = sm->deleteSubmodelElementByPath(ref);
//
//		empty_response_message(statusCode, res);
//	});
//
//	// Retrieves the value of a specific Submodel-Element from the Submodel
//	server.Get("/submodels/" + regex_idShort + "/submodel/submodelElements/" + regex_idShortPath + "/value/?",
//		[this](const Request& req, Response& res)
//	{
//		auto idShort = view_from_match(req.matches[1]);
//		auto idShortPath = view_from_match(req.matches[2]);
//
//		spdlog::info("GET submodelElements: {}/{}", idShort, idShortPath);
//
//		auto sm = getSubmodel(idShort);
//
//		if (!sm)
//			return submodel_not_found(idShort, res);
//
//		Reference ref(idShortPath);
//		auto interface_response = sm->getSubmodelElementByPath(ref, regular_om);
//
//		response_message_with_content_values(interface_response, res);
//	});
//
//	// Updates the Submodel-Element's value
//	server.Put("/submodels/" + regex_idShort + "/submodel/submodelElements/" + regex_idShortPath + "/value/?",
//		[this](const Request& req, Response& res)
//	{
//		auto idShort = view_from_match(req.matches[1]);
//		auto idShortPath = view_from_match(req.matches[2]);
//
//		spdlog::info("PUT submodelElements: {}/{}", idShort, idShortPath);
//
//		auto sm = getSubmodel(idShort);
//
//		if (!sm)
//			return submodel_not_found(idShort, res);
//
//		Reference ref(idShortPath);
//		sm->setSubmodelElementValueByPath(ref, req.body);
//	});
//
//	// Invokes a specific operation from the Submodel synchronously or asynchronously
//	server.Post(R"((/submodels/[-_.~+#\/\w]*))",
//		[this](const Request& req, Response& res) {
//		spdlog::warn("Method invoke synchronous operation not yet implementd!");
//		res.set_content("Method not yet implementd!", TXT_PLAIN);
//		// POST für Operations:
//		// Übergabeparameter (Operation Variables) als Biespiel in Postman
//		// collection in "BigInterface changes" Branch des C# SDK's zu finden
//		// Notiz: Ganze OperationVariables verschicken
//	});
//
//	// Retrieves the result of an asynchronously started operation
//	server.Get("/submodels/" + regex_idShort + R"(/submodel/submodelElements/(\w+)/invocationList/(\w+)/?)",
//		[this](const Request& req, Response& res)
//	{
//		spdlog::warn("Method GET Asynchronously started operations not yet implementd!");
//		res.set_content("Method not yet implementd!", TXT_PLAIN);
//	});
//}
//
//SubmodelElement * SubmodelRepositoryHttpHandler::getSubmodelElementByPathList(SubmodelRepositoryHttpHandler::pathList_t & pathList, Submodel & sm)
//{
//	if (pathList.empty())
//		return nullptr;
//
//	auto path = pathList.cbegin();
//
//	// Get first element from submodel
//	auto element = sm.getSubmodelElements().get(*path);
//	if (element == nullptr)
//		return nullptr;
//
//	for (path++; path != pathList.end(); ++path)
//	{
//		if (element->get_model_type() != ModelTypes::SubmodelElementCollection)
//			return nullptr;
//
//		auto collection = static_cast<SubmodelElementCollection*>(element);
//		element = collection->getSubmodelElements().get(*path);
//
//		if (element == nullptr)
//			return nullptr;
//	}
//
//	return element;
//}
//
//util::optional<api::SubmodelMetamodel> SubmodelRepositoryHttpHandler::getSubmodel(util::string_view idShort) {
//	submodelMutex.lock();
//	auto iter = submodels.find(idShort.to_string());
//	submodelMutex.unlock();
//	if (iter != submodels.end())
//		return { iter->second };
//	return {};
//}
//
//bool SubmodelRepositoryHttpHandler::submodelExists(Submodel &submodel) {
//	return submodelExists(submodel.getIdShort());
//}
//
//bool SubmodelRepositoryHttpHandler::submodelExists(util::string_view idShort)
//{
//	return getSubmodel(idShort).has_value();
//}
//
//ERROR_CODES SubmodelRepositoryHttpHandler::addSubmodelToServer(Submodel &submodel) {
//	bool ret = submodelExists(submodel);
//	if (ret)
//		return ERROR_CODES::ERR_ALREADY_EXISTS;
//
//	submodelMutex.lock();
//	auto result = submodels.emplace(submodel.getIdShort().to_string(), &submodel);
//	submodelMutex.unlock();
//	if (result.second)
//		return ERROR_CODES::ERR_OK;
//	else
//		return ERROR_CODES::ERR_ALREADY_EXISTS;
//}
//
//ERROR_CODES SubmodelRepositoryHttpHandler::removeSubmodelFromServer(Submodel & submodel)
//{
//	if (!submodelExists(submodel))
//		return ERROR_CODES::ERR_DOES_NOT_EXIST;
//
//	submodelMutex.lock();
//	auto iter = submodels.find(submodel.getIdShort().to_string());
//	submodels.erase(iter);
//	submodelMutex.unlock();
//	return ERROR_CODES::ERR_OK;
//}
//
//void SubmodelRepositoryHttpHandler::submodel_not_found(const util::string_view & idShort, Response& res) const
//{
//	spdlog::warn("Submodel {} not found!", idShort);
//	res.set_content("Submodel not found!", TXT_PLAIN);
//}