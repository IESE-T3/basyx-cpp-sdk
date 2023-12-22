#pragma once

#include <basyx/base/elementcontainer.h>
#include <basyx/asset/assetinformation.h>
#include <basyx/base/token.h>

#include <basyx/serialization/base/serialization.h>

#include <basyx/submodel.h>
#include <basyx/reference.h>
#include <basyx/identifiable.h>
#include <basyx/semantics/hasDataSpecification.h>

#include <basyx/util/optional/optional.hpp>

namespace basyx
{

using namespace basyx::base;
using namespace basyx::serialization::priv;

// ToDo: replace placeholders
using Security = int;

class AssetAdministrationShell :
	public Identifiable,
	public HasDataSpecification,
	private ModelType<ModelTypes::AssetAdministrationShell>,
	private Identifiable::Copyable<AssetAdministrationShell>
{
public:
	util::optional<Security> security;
	util::optional<Reference> derivedFrom;
	ElementContainer<Submodel> submodels;
	AssetInformation assetInformation;
public:
	using ModelType::get_model_type;
public:
	AssetAdministrationShell(util::string_view idShort, util::string_view id, AssetInformation assetInformation)
		: Identifiable(idShort, Identifier(id)), assetInformation(std::move(assetInformation)) {};
public:
	//AssetAdministrationShell(const AssetAdministrationShell& aas) :
	//	Identifiable(*aas.getIdShort(), aas.getId()),
	//	assetInformation(aas.assetInformation) 
	//{
	//	this->submodels.append(aas.getSubmodels());

	//	if (aas.getSecurity())
	//		this->security = aas.getSecurity();

	//	if (aas.derivedFrom)
	//		this->derivedFrom = aas.derivedFrom;
	//}

	AssetAdministrationShell(const AssetAdministrationShell& aas) = default;
	AssetAdministrationShell& operator=(const AssetAdministrationShell& aas) = default;

	AssetAdministrationShell(AssetAdministrationShell&&) = default;
	AssetAdministrationShell& operator=(AssetAdministrationShell&&) = default;
public:
	const util::optional<Security>& getSecurity() const { return security; };
	void setSecurity(Security security) { this->security = std::move(security); };

	const ElementContainer<Submodel>& getSubmodels() const { return this->submodels; };
	ElementContainer<Submodel>& getSubmodels() { return this->submodels; };
	void setSubmodels(ElementContainer<Submodel> submodels) { this->submodels = std::move(submodels); };

	// Identifiable - special purpose
	void setId(Token<Deserializer> t, Identifier id) {
		this->Identifiable::setId(id);
	}
};

};
