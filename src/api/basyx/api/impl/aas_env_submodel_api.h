#pragma once

#include <basyx/submodel.h>
#include <basyx/api/submodel_api.h>

namespace basyx {
namespace api {

class AasEnvSubmodel : public basyx::api::SubmodelInterface
{
private:
	Submodel * submodel;
public:
	AasEnvSubmodel(Submodel* sm) : submodel{ sm } {};
public:
	Submodel getSubmodel() override { return *submodel; };

	submodel_element_list_t getAllSubmodelElements() override;
	submodel_element_list_t getAllSubmodelElementsByPath(util::string_view path) override;

	void updateSubmodel(const Submodel& submodel) override;

	bool addSubmodelElement(const SubmodelElement& element) override;
	bool addSubmodelElementByPath(const SubmodelElement& element, util::string_view path) override;
	void setSubmodelElementValueByPath() override {};
	bool deleteSubmodelElementByPath(util::string_view path) override;

	void invokeOperationSync() override {};
	void invokeOperationAsync() override {};
	void getOperationAsyncResult() override {};
};

}
}
