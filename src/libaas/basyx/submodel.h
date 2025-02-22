#pragma once

#include <basyx/util/optional/optional.hpp>

#include <basyx/identifiable.h>
#include <basyx/haskind.h>
#include <basyx/hassemantics.h>
#include <basyx/submodelelement/submodelelement.h>

#include <basyx/base/token.h>

#include <basyx/serialization/base/serialization.h>

#include <basyx/serialization/serializable.h>

#include <basyx/base/elementcontainer.h>

#include <basyx/semantics/hasDataSpecification.h>
#include <basyx/qualifiable/qualifiable.h>

#include <initializer_list>
#include <vector>
#include <string>

namespace basyx
{

using namespace basyx::base;
using namespace basyx::serialization::priv;
	
class Submodel : 
	public Identifiable,
	public HasKind, 
	public HasSemantics,
	private ModelType<ModelTypes::Submodel>,
	private Identifiable::Copyable<Submodel>
{
private:
	ElementContainer<SubmodelElement> submodelElements;
public:
	Submodel(util::string_view idShort, util::string_view identifier) : Identifiable(idShort, Identifier(identifier)) {};
public:
   Submodel(const Submodel &sm) : Identifiable(*sm.getIdShort(), sm.getId()) {
      this->submodelElements.append(sm.getSubmodelElements());
   };

	Submodel& operator=(const Submodel& sm) = default;

	Submodel(Submodel&&) = default;
	Submodel& operator=(Submodel&&) = default;

	Submodel& operator+=(const Submodel& sm) {
		this->getSubmodelElements().append(sm.getSubmodelElements());
		return *this;
	}
public:
	const ElementContainer<SubmodelElement>& getSubmodelElements() const { return this->submodelElements; };
	ElementContainer<SubmodelElement>& getSubmodelElements() { return this->submodelElements; };
	void setSubmodelElements(ElementContainer<SubmodelElement> elements) { this->submodelElements = std::move(elements); };

   // Identifiable - special purpose
   void setId(Token<Deserializer> t, Identifier id) {
      this->Identifiable::setId(id);
   }
};

};
