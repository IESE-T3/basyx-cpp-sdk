#ifndef BASYX_SUBMODEL_ENUMERATIONS_IDENTIFIABLEELEMENTS_H
#define BASYX_SUBMODEL_ENUMERATIONS_IDENTIFIABLEELEMENTS_H

#include <basyx/base/basyx_enum_base.h>

namespace basyx {

enum class DataTypeDefinition {
    INVALID,
    AnyURI,
    Base64Binary,
    Boolean,
    Byte,
    Date,
    DateTime,
    Decimal,
    Double,
    Duration,
    Float,
    GDay,
    GMonth,
    GMonthDay,
    GYear,
    GYearMonth,
    HexBinary,
    Int,
    Integer,
    Long,
    NegativeInteger,
    NonNegativeInteger,
    NonPositiveInteger,
    PositiveInteger,
    Short,
    String,
    Time,
    UnsignedByte,
    UnsignedInt,
    UnsignedLong,
    UnsignedShort,
};

using DataTypeDefinition_ = basyx::basyx_enum_base<DataTypeDefinition, 30>;

}

#endif /* BASYX_SUBMODEL_ENUMERATIONS_IDENTIFIABLEELEMENTS_H */
