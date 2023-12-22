#include <algorithm>
#include <memory>
#include <string>
#include <array>

#include <basyx/enums/ReferenceTypes.h>

namespace basyx {

using enum_pair_t = std::pair<const char*, ReferenceTypes>;

static const std::array<enum_pair_t, 2> string_to_enum = {
    std::make_pair("ExternalReference", ReferenceTypes::ExternalReference),
    std::make_pair("ModelReference", ReferenceTypes::ModelReference),
};

ReferenceTypes ReferenceTypes_::from_string(util::string_view name) {
    auto pair = std::find_if(string_to_enum.begin(), string_to_enum.end(),
        [&name](const enum_pair_t& pair) {
            return !name.compare(pair.first);
        });
    return pair->second;
}

const char* ReferenceTypes_::to_string(ReferenceTypes value) {
    auto pair = std::find_if(string_to_enum.begin(), string_to_enum.end(),
        [value](const enum_pair_t& pair) {
            return value == pair.second;
        });
    return pair->first;
}

}
