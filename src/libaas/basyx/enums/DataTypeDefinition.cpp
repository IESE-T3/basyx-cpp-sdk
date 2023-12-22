#include <basyx/enums/DataTypeDefinition.h>

#include <array>
#include <algorithm>
#include <memory>

using namespace basyx;

template<>
const DataTypeDefinition_::enum_array_t DataTypeDefinition_::string_to_enum =
{
	std::make_pair("xs:anyURI", DataTypeDefinition::AnyURI),
	std::make_pair("xs:base64Binary", DataTypeDefinition::Base64Binary),
	std::make_pair("xs:boolean", DataTypeDefinition::Boolean),
	std::make_pair("xs:byte", DataTypeDefinition::Byte),
	std::make_pair("xs:date", DataTypeDefinition::Date),
	std::make_pair("xs:dateTime", DataTypeDefinition::DateTime),
	std::make_pair("xs:decimal", DataTypeDefinition::Decimal),
	std::make_pair("xs:double", DataTypeDefinition::Double),
	std::make_pair("xs:duration", DataTypeDefinition::Duration),
	std::make_pair("xs:float", DataTypeDefinition::Float),
	std::make_pair("xs:gDay", DataTypeDefinition::GDay),
	std::make_pair("xs:gMonth", DataTypeDefinition::GMonth),
	std::make_pair("xs:gMonthDay", DataTypeDefinition::GMonthDay),
	std::make_pair("xs:gYear", DataTypeDefinition::GYear),
	std::make_pair("xs:gYearMonth", DataTypeDefinition::GYearMonth),
	std::make_pair("xs:hexBinary", DataTypeDefinition::HexBinary),
	std::make_pair("xs:int", DataTypeDefinition::Int),
	std::make_pair("xs:integer", DataTypeDefinition::Integer),
	std::make_pair("xs:long", DataTypeDefinition::Long),
	std::make_pair("xs:negativeInteger", DataTypeDefinition::NegativeInteger),
	std::make_pair("xs:nonNegativeInteger", DataTypeDefinition::NonNegativeInteger),
	std::make_pair("xs:nonPositiveInteger", DataTypeDefinition::NonPositiveInteger),
	std::make_pair("xs:positiveInteger", DataTypeDefinition::PositiveInteger),
	std::make_pair("xs:short", DataTypeDefinition::Short),
	std::make_pair("xs:string", DataTypeDefinition::String),
	std::make_pair("xs:time", DataTypeDefinition::Time),
	std::make_pair("xs:unsignedByte", DataTypeDefinition::UnsignedByte),
	std::make_pair("xs:unsignedInt", DataTypeDefinition::UnsignedInt),
	std::make_pair("xs:unsignedLong", DataTypeDefinition::UnsignedLong),
	std::make_pair("xs:unsignedShort", DataTypeDefinition::UnsignedShort),
};