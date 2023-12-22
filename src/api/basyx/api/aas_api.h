#pragma once

#include <basyx/assetadministrationshell.h>

#include <basyx/api/submodel_api.h>

namespace basyx {
namespace api {

class AasInterface
{
public:
	virtual ~AasInterface() = default;
public:
	virtual std::vector<AssetAdministrationShell*> getAssetAdministrationShells() = 0;
	virtual AssetAdministrationShell* getAssetAdministrationShellByIdShort(util::string_view idShort) = 0;
	virtual AssetAdministrationShell* getAssetAdministrationShellById(util::string_view idShort) = 0;
	virtual AssetAdministrationShell* addAssetAdministrationShell(const AssetAdministrationShell & aas) = 0;
	virtual AssetAdministrationShell* updateAssetAdministrationShell(const AssetAdministrationShell & aas) = 0;

	virtual std::unique_ptr<SubmodelInterface> getSubmodel(util::string_view idShort_aas, util::string_view idShort_submodel) = 0;

	virtual Reference putSubmodelReference(Reference & submodel) = 0;
	virtual bool removeSubmodelReference(Reference & submodel) = 0;
};

}
}
