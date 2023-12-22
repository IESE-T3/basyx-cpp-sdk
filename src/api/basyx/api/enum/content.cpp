#include "content.h"

#include <array>
#include <algorithm>
#include <memory>
#include <string>

using namespace basyx::api;

using enum_pair_t = std::pair<const char*, Content>;

static const std::array<enum_pair_t, 4> string_to_enum = 
{
    std::make_pair("Normal",  Content::Normal),
    std::make_pair("Value", Content::Value),
    std::make_pair("Reference", Content::Reference),
    std::make_pair("Path", Content::Path),
};

Content Content_::from_string(const std::string & name)
{
    auto pair = std::find_if(string_to_enum.begin(), string_to_enum.end(), 
		[&name](const enum_pair_t & pair) {
			return !name.compare(pair.first);
	});

    return pair->second;
}

const char * Content_::to_string(Content value)
{
    auto pair = std::find_if(string_to_enum.begin(), string_to_enum.end(), 
		[value](const enum_pair_t & pair) {
			return value == pair.second;
	});

    return pair->first;
}

