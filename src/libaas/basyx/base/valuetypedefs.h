#ifndef VALUETYPEDEFS_H
#define VALUETYPEDEFS_H

#pragma once

#include <cstdint>
#include <string>

#include <basyx/util/string_view/string_view.hpp>

#include <basyx/enums/DataTypeDefinition.h>

namespace basyx {
namespace detail
{

	template<DataTypeDefinition DataType> 
	struct data_type_def_map {};

	template<> struct data_type_def_map<DataTypeDefinition::AnyURI> { using type_t = std::string; };
	template<> struct data_type_def_map<DataTypeDefinition::Int> { using type_t = int; };
	template<> struct data_type_def_map<DataTypeDefinition::Integer> { using type_t = int; };
	template<> struct data_type_def_map<DataTypeDefinition::Float> { using type_t = float; };
	template<> struct data_type_def_map<DataTypeDefinition::Double> { using type_t = double; };
	template<> struct data_type_def_map<DataTypeDefinition::String> { using type_t = std::string; };
	template<> struct data_type_def_map<DataTypeDefinition::Byte> { using type_t = char; };
	template<> struct data_type_def_map<DataTypeDefinition::UnsignedByte> { using type_t = unsigned char; };

	template<typename T>
	struct data_type_def_map_base_type {};

	template<> struct data_type_def_map_base_type<int> { static constexpr DataTypeDefinition dataType = DataTypeDefinition::Integer; };
	template<> struct data_type_def_map_base_type<float> { static constexpr DataTypeDefinition dataType = DataTypeDefinition::Float; };
	template<> struct data_type_def_map_base_type<double> { static constexpr DataTypeDefinition dataType = DataTypeDefinition::Double; };
	template<> struct data_type_def_map_base_type<std::string> { static constexpr DataTypeDefinition dataType = DataTypeDefinition::String; };


	enum datatypes {
		Boolean = 0,
		Byte,
		UnsignedByte,
		Short,
		UnsignedShort,
		Integer,
		UnsignedInteger,
		Long,
		UnsignedLong,
		Float,
		Double,
		String,
	};

	util::string_view toString(const datatypes valuetype);

	template<typename T> struct data_type_def {
		datatypes value_type;
	};

	template<> struct data_type_def<int8_t> { static constexpr datatypes value_type = Byte; };
	template<> struct data_type_def<char> { static constexpr datatypes value_type = Byte; };
	template<> struct data_type_def<uint8_t> { static constexpr datatypes value_type = UnsignedByte; };
	template<> struct data_type_def<int16_t> { static constexpr datatypes value_type = Short; };
	template<> struct data_type_def<uint16_t> { static constexpr datatypes value_type = UnsignedShort; };
	template<> struct data_type_def<int32_t> { static constexpr datatypes value_type = Integer; };
	template<> struct data_type_def<uint32_t> { static constexpr datatypes value_type = UnsignedInteger; };
	template<> struct data_type_def<int64_t> { static constexpr datatypes value_type = Long; };
	template<> struct data_type_def<uint64_t> { static constexpr datatypes value_type = UnsignedLong; };
	template<> struct data_type_def<float> { static constexpr datatypes value_type = Float; };
	template<> struct data_type_def<double> { static constexpr datatypes value_type = Double; };
	template<> struct data_type_def<bool> { static constexpr datatypes value_type = Boolean; };
	template<> struct data_type_def<std::string> { static constexpr datatypes value_type = String; };

	template<typename T> struct data_type_map { using value_type_t = T; };
	template<> struct data_type_map<std::string> { using value_type_t = std::string; };
	template<> struct data_type_map<const char*> { using value_type_t = std::string; };
	template<> struct data_type_map<util::string_view> { using value_type_t = std::string; };

};
}

#endif // VALUETYPEDEFS_H
