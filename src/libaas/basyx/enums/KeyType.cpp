#include "KeyType.h"

#include <array>
#include <algorithm>
#include <memory>
#include <string>

using namespace basyx;

using enum_pair_t = std::pair<const char*, KeyType>;

static const std::array<enum_pair_t, 5> string_to_enum = 
{
    std::make_pair("IdShort",  KeyType::IdShort),
    std::make_pair("FragementId", KeyType::FragmentId),
    std::make_pair("Custom", KeyType::Custom),
    std::make_pair("IRDI", KeyType::IRDI),
    std::make_pair("IRI", KeyType::IRI),
};

KeyType KeyType_::from_string(util::string_view name)
{
    auto pair = std::find_if(string_to_enum.begin(), string_to_enum.end(), 
		[name](const enum_pair_t & pair) {
			return !name.compare(pair.first);
	});

    return pair->second;
}

const char * KeyType_::to_string(KeyType value)
{
    auto pair = std::find_if(string_to_enum.begin(), string_to_enum.end(), 
		[value](const enum_pair_t & pair) {
			return value == pair.second;
	});

    return pair->first;
}