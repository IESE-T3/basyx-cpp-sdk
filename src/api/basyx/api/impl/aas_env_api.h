#pragma once

#include <basyx/environment.h>
#include <basyx/api/aas_api.h>

#include <basyx/api/impl/aas_env_submodel_api.h>

namespace basyx {
namespace api {

class AasEnvApi : public basyx::api::AasInterface
{
private:
	Environment & env;
public:
	AasEnvApi(Environment & env) : env(env) {};
public:
	std::vector<AssetAdministrationShell*> getAssetAdministrationShells() override
	{
		std::vector<AssetAdministrationShell*> aasList;

		for (const auto & entry : env.getAssetAdministrationShells())
			aasList.push_back(entry.get());

		return aasList;
	};

	AssetAdministrationShell* getAssetAdministrationShellByIdShort(util::string_view idShort) override
	{
		auto aas = env.getAssetAdministrationShells().get(idShort);
		if (aas)
			return aas;
		return nullptr;
	};

	AssetAdministrationShell* getAssetAdministrationShellById(util::string_view identifier) override
	{
		for (const auto & entry : env.getAssetAdministrationShells())
			if (entry->getId() == identifier)
				return entry.get();

		return nullptr;
	};

	AssetAdministrationShell * addAssetAdministrationShell(const AssetAdministrationShell & aas) override
	{
		for (const auto & entry : env.getAssetAdministrationShells())
			if (entry->getId() == aas.getId())
				return nullptr;

		return this->env.getAssetAdministrationShells().add(aas);
	};

	AssetAdministrationShell * updateAssetAdministrationShell(const AssetAdministrationShell & aas) override
	{
		return nullptr;
	};

	std::unique_ptr<SubmodelInterface> getSubmodel(util::string_view idShort_aas, util::string_view idShort_submodel) override
	{
		auto aas = env.getAssetAdministrationShells().get(idShort_aas);

		if (!aas)
			return nullptr;

		auto submodel = aas->getSubmodels().get(idShort_submodel);
		if (!submodel)
			return nullptr;

		return std::make_unique<AasEnvSubmodel>(submodel);
	};

	Reference putSubmodelReference(Reference & submodel) override
	{
		return Reference(submodel);
	};

	bool removeSubmodelReference(Reference & submodel) override
	{
		return false;
	};
};

}
}
