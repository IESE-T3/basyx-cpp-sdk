#pragma once

#include <basyx/assetadministrationshell.h>
#include <basyx/submodel.h>

namespace basyx {
namespace api {

class SubmodelInterface
{
public:
	using submodel_element_list_t = std::vector<std::unique_ptr<SubmodelElement>>;
public:
	virtual ~SubmodelInterface() = default;
public:
	virtual Submodel getSubmodel() = 0;

	virtual submodel_element_list_t getAllSubmodelElements() = 0;
	virtual submodel_element_list_t getAllSubmodelElementsByPath(util::string_view path) = 0;

	virtual void updateSubmodel(const Submodel & submodel) = 0;

	virtual bool addSubmodelElement(const SubmodelElement& element) = 0;
	virtual bool addSubmodelElementByPath(const SubmodelElement& element, util::string_view path) = 0;

	virtual void setSubmodelElementValueByPath() = 0;
	virtual bool deleteSubmodelElementByPath(util::string_view path) = 0;

	virtual void invokeOperationSync() = 0;
	virtual void invokeOperationAsync() = 0;
	
	virtual void getOperationAsyncResult() = 0;
};

class SubmodelApi
{
private:
public:
public:
	struct submodel_api_impl_t
	{
	};

	std::unique_ptr<submodel_api_impl_t> impl;
};




}
}
