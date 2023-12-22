#include "reference.h"

#include <basyx/serialization/private/deserializer_priv.h>

namespace basyx
{


Reference::Reference(basyx::base::Token<serialization::priv::Deserializer> t) {}

//basyx::Reference::Reference(util::string_view str)
//	: Reference(Key{ str })
//{
//}
//
Reference::Reference(const Referable& referable)
{

}

//Reference& Reference::operator=(std::initializer_list<Key> init_list)
//{
//	this->keys = Reference::keyList_t{ init_list };
//	return *this;
//};

Reference::Reference(const Reference& ref)
	: type(ref.type)
	, keys(ref.keys)
{
	if (ref.referredSemanticId) {
		this->referredSemanticId = std::make_unique<Reference>(*ref.get_referred_semantic_id());
	};
};

Reference& Reference::operator=(const Reference& ref)
{
	this->keys = ref.keys;
	if (ref.referredSemanticId) {
		this->referredSemanticId = std::make_unique<Reference>(*ref.get_referred_semantic_id());
	};
	return *this;
};

Reference Reference::make_external_reference(std::initializer_list<Key> keys)
{
	Reference ref;
	ref.type = ReferenceTypes::ExternalReference;
	ref.keys = keys;
	return ref;
};

Reference Reference::make_model_reference(std::initializer_list<Key> keys)
{
	Reference ref;
	ref.type = ReferenceTypes::ModelReference;
	ref.keys = keys;
	return ref;
};


};