#pragma once

#include <string>

#include <basyx/util/optional/optional.hpp>

#include <basyx/langstringset.h>

#include <basyx/enums/KeyElements.h>
#include <basyx/enums/KeyType.h>

namespace basyx
{

class Key
{
public:
	KeyElements type;
	std::string value;
public:
	Key(KeyElements type, util::string_view value) : type(type), value(value.to_string()) {};

	Key(const Key&) = default;
	Key& operator=(const Key&) = default;

	Key(Key&&) noexcept = default;
	Key& operator=(Key&&) noexcept = default;

	~Key() = default;
};

};
