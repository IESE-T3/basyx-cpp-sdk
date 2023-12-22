#ifndef BASYX_SUBMODEL_ENUMERATIONS_CONTENT_H
#define BASYX_SUBMODEL_ENUMERATIONS_CONTENT_H

#include <string>

namespace basyx {
namespace api {

enum class Content {
    Normal,
    Value,
    Reference,
    Path,
};

class Content_
{
public:
    static Content from_string(const std::string & name);
    static const char * to_string(Content value);
};


}
}

#endif /* BASYX_SUBMODEL_ENUMERATIONS_CONTENT_H */
