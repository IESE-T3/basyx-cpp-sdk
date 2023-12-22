#include "aas_env_submodel_api.h"

#include <basyx/util/algorithm/string.hpp>

namespace basyx {
namespace api {


AasEnvSubmodel::submodel_element_list_t AasEnvSubmodel::getAllSubmodelElements()
{
	auto & elements = this->submodel->getSubmodelElements();
	
	submodel_element_list_t element_list;
	element_list.reserve(elements.size());

	for (const auto& element : elements) {
		element_list.push_back(element->copy<SubmodelElement>());
	};

	return element_list;
};

AasEnvSubmodel::submodel_element_list_t AasEnvSubmodel::getAllSubmodelElementsByPath(util::string_view path)
{
	submodel_element_list_t element_list;

	auto path_splits = util::algorithm::string::split(path, '/');

	if (path_splits.empty()) {
		return this->getAllSubmodelElements();
	};

	auto it = path_splits.begin();

	// Check for root element
	auto element = submodel->getSubmodelElements().get(*it);
	if (element == nullptr) {
		return {};
	};

	// Traverse recursively through submodel elements
	for (++it; it != path_splits.end(); ++it) {
		if (SubmodelElementHelper::IsSubmodelElementCollection(*element)) {
			auto coll = SubmodelElement::element_cast<SubmodelElementCollection>(element);
			element = coll->getSubmodelElements().get(*it);

			if (element == nullptr) {
				return {};
			};
		}
		else {
			return {};
		};
	}

	// Put found element(s) inside list
	if (SubmodelElementHelper::IsSubmodelElementCollection(*element)) {
		auto coll = SubmodelElement::element_cast<SubmodelElementCollection>(element);

		for (const auto& child : coll->getSubmodelElements()) {
			element_list.push_back(child->copy<SubmodelElement>());
		}

	}
	else {
		element_list.push_back(element->copy<SubmodelElement>());
	};

	return element_list;
};

void AasEnvSubmodel::updateSubmodel(const Submodel& submodel)
{
	
};

bool AasEnvSubmodel::addSubmodelElement(const SubmodelElement& element)
{
	auto& elements = this->submodel->getSubmodelElements();

	if (!elements.hasEntry(*element.getIdShort())) {
		elements.add(element.copy<SubmodelElement>());
		return true;
	};

	return false;
};

bool AasEnvSubmodel::addSubmodelElementByPath(const SubmodelElement& new_element, util::string_view path)
{
	auto path_splits = util::algorithm::string::split(path, '/');

	if (path_splits.empty()) {
		return addSubmodelElement(new_element);
	};

	auto it = path_splits.begin();

	// Check for root element
	auto element = submodel->getSubmodelElements().get(*it);
	if (element == nullptr) {
		return false;
	};

	// Traverse recursively through submodel elements
	for (++it; it != path_splits.end(); ++it) {
		if (SubmodelElementHelper::IsSubmodelElementCollection(*element)) {
			auto coll = SubmodelElement::element_cast<SubmodelElementCollection>(element);
			element = coll->getSubmodelElements().get(*it);

			if (element == nullptr) {
				return false;
			};
		}
		else {
			return false;
		};
	}

	// Put found element(s) inside list
	if (SubmodelElementHelper::IsSubmodelElementCollection(*element)) {
		auto coll = SubmodelElement::element_cast<SubmodelElementCollection>(element);

		coll->getSubmodelElements().add(new_element.copy<SubmodelElement>());

		return true;
	}

	return false;
};

bool AasEnvSubmodel::deleteSubmodelElementByPath(util::string_view path)
{
	auto path_splits = util::algorithm::string::split(path, '/');

	if (path_splits.empty()) {
		this->submodel->getSubmodelElements().clear();
		return true;
	};

	auto it = path_splits.begin();

	// We're at root level, delete from container
	if (path_splits.size() == 1) {
		return this->submodel->getSubmodelElements().remove(*it);
	};


	// Traverse recursively through submodel elements
	auto element = submodel->getSubmodelElements().get(*it);
	if (element == nullptr) {
		return false;
	};

	for (++it; it != path_splits.end() - 1; ++it) {
		if (SubmodelElementHelper::IsSubmodelElementCollection(*element)) {
			auto coll = SubmodelElement::element_cast<SubmodelElementCollection>(element);
			element = coll->getSubmodelElements().get(*it);

			if (element == nullptr) {
				return false;
			};
		}
		else {
			return false;
		};
	}

	// Remove target element from collection
	if (SubmodelElementHelper::IsSubmodelElementCollection(*element)) {
		auto coll = SubmodelElement::element_cast<SubmodelElementCollection>(element);

		return coll->getSubmodelElements().remove(*it);
	}

	return false;
};


}
}