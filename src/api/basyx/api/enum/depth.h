#ifndef BASYX_SUBMODEL_ENUMERATIONS_DEPTHENUM_H
#define BASYX_SUBMODEL_ENUMERATIONS_DEPTHENUM_H

#include <string>

namespace basyx {
namespace api {

enum class Depth {
    Recursive,
    NonRecursive,
};

class DepthEnum_
{
public:
    static Depth from_string(const std::string & name);
    static const char * to_string(Depth value);
};

}
}

#endif /* BASYX_SUBMODEL_ENUMERATIONS_DEPTHENUM_H */
