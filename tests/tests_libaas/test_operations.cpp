#include <gtest/gtest.h>

#include <basyx/submodelelement/operation.h>
#include <basyx/submodelelement/operationvariable.h>
#include <basyx/submodelelement/multilanguageproperty.h>

#include <type_traits>


using namespace basyx;

class OperationTest : public ::testing::Test {
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

TEST_F(OperationTest, OperationVariable)
{
	//auto var = OperationVariable::create<MultiLanguageProperty>("op_var", "mlp");
};

int measure_rpm(int a, int b)
{
	return a * b;
};

float measure_angle(int a, int b)
{
	return 100.0f;
};

TEST_F(OperationTest, Operation)
{
	Operation op{ "test_operation" };

	op.inputVariables() = {
		OperationVariable::Create<Property>("a", {"de", "Erste Eingangsbelegung für Umdrehungszahlmesser"}),
		OperationVariable::Create<Property>("b", {"de", "Zweite Eingangsbelegung für Umdrehungszahlmesser"}),
	};

	op.outputVariables() = {
		OperationVariable::Create<Property>("umdrehungszahl", {"de", "Gemessene Umdrehungszahl des Geräts"}),
		OperationVariable::Create<Property>("winkel", {"de", "Endwinkel des Geräts"}),
	};

	ASSERT_EQ(op.inputVariables().size(), 2);
	ASSERT_EQ(op.inputVariables().get(0)->getParent(), &op);

	// Assignment of the Operation's actual function through lambda
	op.setInvokable([] (
		const ElementContainer<SubmodelElement>& input, 
		ElementContainer<SubmodelElement>& inout,
		ElementContainer<SubmodelElement> & output) -> bool {
			// Extract input parameters from input list
			int a = input.get<Property>("a")->get_as<DataTypeDefinition::Int>();
			int b = input.get<Property>("b")->get_as<DataTypeDefinition::Int>();

			// Call the actual function
			auto rpm = measure_rpm(a, b);
			auto angle = measure_angle(a, b);

			// Set output variables
			output.get<Property>("umdrehungszahl")->assign(rpm);
			output.get<Property>("winkel")->assign(angle);

			// Return invokation result
			return true;
	});

	// Invoke the operation
	auto input = ElementContainer<SubmodelElement>{
		Property("a", 4), 
		Property("b", 2)
	};

	auto inout = ElementContainer<SubmodelElement>{};

	auto output = op.outputVariables();

	auto invoke_result = op.invoke(
		input,
		inout,
		output
	);

	ASSERT_EQ(invoke_result, true);

	ASSERT_EQ(output.get<Property>("umdrehungszahl")->get_as<DataTypeDefinition::Int>(), 4*2);
	ASSERT_EQ(output.get<Property>("winkel")->get_as<DataTypeDefinition::Float>(), 100.0f);
};
