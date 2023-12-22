#pragma once

#include <basyx/api/level.h>
#include <basyx/api/content.h>
#include <basyx/api/extent.h>

namespace basyx {
namespace api {


struct OutputModifier
{
    Level level = Level::Deep;
    Content content = Content::Normal;
    Extent extent = Extent::WithoutBLOBValue;

    OutputModifier() {};

    OutputModifier(Level level, Content content, Extent extent)
    {
        level = level;
        content = content;
        extent = extent;
    }
};


}
}