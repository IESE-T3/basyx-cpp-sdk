#include <basyx/serialization/json/serializer.h>
#include <basyx/serialization/json/deserializer.h>

#include <string>
#include <fstream>
#include <iostream>

#include <basyx/enums/DataTypeDefinition.h>


using json_t = nlohmann::json;

int parse_json(std::string filename)
{
	try
	{
		std::ifstream ifs(filename);
		json_t input = json_t::parse(ifs);
		auto input_dump = input.dump(4);

		if (input.contains("assetAdministrationShells"))
		{
			auto & aas_json_in = input["assetAdministrationShells"];

			auto aas = basyx::serialization::json::deserialize_aas(aas_json_in[0]);
			auto aas_json_out = basyx::serialization::json::serialize(aas);

			auto output = json_t();
			output["assetAdministrationShells"] = json_t::array({ std::move(aas_json_out) });

			auto json_dump = output.dump(4);
			std::cout << json_dump;

			assert(input == output);

			return 0;
		}
		else if (input.contains("submodels")) {
			auto& sm_json_in = input["submodels"];

			auto sm = basyx::serialization::json::deserialize_submodel(sm_json_in[0]);
			auto sm_json_out = basyx::serialization::json::serialize(sm);

			auto output = json_t();
			output["submodels"] = json_t::array({ std::move(sm_json_out) });

			auto json_dump = output.dump(4);
			std::cout << json_dump;

			assert(input == output);

			return 0;
		};

		return -4;
	}
	catch (std::exception& e)
	{
		std::cout << e.what();
		return -3;
	};
};

int main(int argc, char* argv[]) 
{
	if (argc != 2)
		return -1;

	std::string filename = argv[1];

#ifdef _DEBUG
	filename = R"(C:\base\Projects\BaSyx\specs\test_set\MultiLanguageProperty\minimal.json)";
#endif

	return parse_json(filename);
};