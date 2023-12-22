#include "property.h"


namespace basyx
{
//	
//void Property_v2::assign(int i){
//};
//
//void Property_v2::assign(float f) {
//}
//

void Property::assign(util::string_view sv)
{
	this->value = std::make_unique<property_value_impl<DataTypeDefinition::String>>(sv.to_string());
}

std::string Property::get_value_string() const { 
	if(this->has_value())
		return this->value->get_value_string(); 

	return "";
};



};