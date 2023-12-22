#include "depth.h"

#include <array>
#include <algorithm>
#include <memory>
#include <string>

using namespace basyx::api;

using enum_pair_t = std::pair<const char*, Depth>;

static const std::array<enum_pair_t, 2> string_to_enum = 
{
    std::make_pair("Recursive",  Depth::Recursive),
    std::make_pair("NonRecursive", Depth::NonRecursive),
};

Depth DepthEnum_::from_string(const std::string & name)
{
    auto pair = std::find_if(string_to_enum.begin(), string_to_enum.end(), 
		[&name](const enum_pair_t & pair) {
			return !name.compare(pair.first);
	});

    return pair->second;
}

const char * DepthEnum_::to_string(Depth value)
{
    auto pair = std::find_if(string_to_enum.begin(), string_to_enum.end(), 
		[value](const enum_pair_t & pair) {
			return value == pair.second;
	});

    return pair->first;
}

