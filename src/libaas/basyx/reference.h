#pragma once

#include <basyx/key.h>

#include <basyx/util/optional/optional.hpp>

#include <basyx/referable.h>

#include <basyx/base/token.h>
#include <basyx/serialization/base/serialization.h>

#include <basyx/enums/ReferenceTypes.h>

#include <initializer_list>
#include <vector>
#include <string>

namespace basyx
{
	
class Reference
{
public:
	using keyList_t = std::vector<Key>;
public:
	ReferenceTypes type = ReferenceTypes::ModelReference;
private:
	std::unique_ptr<Reference> referredSemanticId;
	keyList_t keys;
private:
	Reference() = default;

public:
	Reference(basyx::base::Token<basyx::serialization::priv::Deserializer> t);
	Reference(ReferenceTypes type_, Key key_) : type(type_), keys{ std::move(key_) } {};

	Reference(const Referable & referable);

public:
	Reference(const Reference &);
	Reference& operator=(const Reference &);

	Reference(Reference &&) noexcept = default;
	Reference& operator=(Reference &&) noexcept = default;
//public:
//	Reference& operator=(std::initializer_list<Key> init_list);
public:
   void add(Key k) { keys.emplace_back(std::move(k)); }
public:
	const Key& get_key(std::size_t index = 0) const { return keys[index]; };
	const std::size_t size() const { return keys.size(); };
public:
	const Reference * const get_referred_semantic_id() const { return referredSemanticId.get(); };
	void set_referred_semantic_id(Reference ref) { this->referredSemanticId = std::make_unique<Reference>(std::move(ref)); };
public:
	static Reference make_external_reference(std::initializer_list<Key> keys);
	static Reference make_model_reference(std::initializer_list<Key> keys);
};

};
