#include <gtest/gtest.h>

#include <basyx/submodelelement/property.h>

using namespace basyx;

class PropertyTest : public ::testing::Test {
protected:
    // Test settings

    // Test variables

    virtual void SetUp()
    {
    }

    virtual void TearDown()
    {
    }
};


TEST_F(PropertyTest, PropertyType)
{
    Property prop{ "test" };

    prop.assign(1);
    ASSERT_EQ(prop.get_value_type(), DataTypeDefinition::Integer);
    ASSERT_EQ(prop.get_as<DataTypeDefinition::Int>(), 1);

    prop.assign(12.34f);
    prop.assign(20.0);

    prop.assign("test");

    Property prop2{ "test", 1.0f };
    ASSERT_EQ(prop2.get_value_type(), DataTypeDefinition::Float);
    ASSERT_EQ(prop2.get_as<DataTypeDefinition::Float>(), 1.0f);

    Property prop3{ "test", "1.0f" };
    ASSERT_EQ(prop3.get_value_type(), DataTypeDefinition::String);
    ASSERT_EQ(prop3.get_as<DataTypeDefinition::String>(), "1.0f");

    Property prop4{ "test", util::string_view("1.0f") };
    ASSERT_EQ(prop4.get_value_type(), DataTypeDefinition::String);
    ASSERT_EQ(prop4.get_as<DataTypeDefinition::String>(), "1.0f");

    Property prop5{ "test", std::string("1.0f") };
    ASSERT_EQ(prop5.get_value_type(), DataTypeDefinition::String);
    ASSERT_EQ(prop5.get_as<DataTypeDefinition::String>(), "1.0f");
}