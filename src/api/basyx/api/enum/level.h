#ifndef BASYX_SUBMODEL_ENUMERATIONS_LEVEL_H
#define BASYX_SUBMODEL_ENUMERATIONS_LEVEL_H

#include <string>

namespace basyx {
namespace api {

enum class Level {
    Deep,
    Core,
};

class Level_
{
public:
    static Level from_string(const std::string & name);
    static const char * to_string(Level value);
};


}
}

#endif /* BASYX_SUBMODEL_ENUMERATIONS_LEVEL_H */
