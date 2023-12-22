#pragma once

#include <basyx/enums/ModelingKind.h>

namespace basyx
{
class HasKind
{
private:
   ModelingKind kind = ModelingKind::None;
public:
   void setKind(ModelingKind kind) { this->kind = kind; }
   const ModelingKind getKind() const { return kind; }
};

};
