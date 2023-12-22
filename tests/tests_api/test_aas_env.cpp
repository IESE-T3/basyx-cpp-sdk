#include <gtest/gtest.h>

#include <basyx/api/aas_api.h>
#include <basyx/api/impl/aas_env_api.h>

#include <basyx/environment.h>

using namespace basyx;
using namespace basyx::api;

class TestAasEnv : public ::testing::Test
{
protected:
	Environment env;

	virtual void SetUp()
	{
	}
};

TEST_F(TestAasEnv, TestEnv)
{
	AssetInformation asset_inf_1{ AssetKind::Instance };
	AssetAdministrationShell aas_1{ "aas_1", Identifier::IRI("https://admin-shell.io/cpp#aas"), asset_inf_1 };

	AssetInformation asset_inf_2{ AssetKind::Instance };
	AssetAdministrationShell aas_2{ "aas_2", Identifier::IRI("https://admin-shell.io/cpp#aas"), asset_inf_2 };

	env.getAssetAdministrationShells().add(std::move(aas_1));
	env.getAssetAdministrationShells().add(std::move(aas_2));

	ASSERT_EQ(env.getAssetAdministrationShells().size(), 2);
	ASSERT_TRUE(env.getAssetAdministrationShells().hasEntry("aas_1"));
	ASSERT_TRUE(env.getAssetAdministrationShells().hasEntry("aas_2"));
}



TEST_F(TestAasEnv, TestApiConstructor)
{
	AasEnvApi envApi(this->env);

	ASSERT_EQ(envApi.getAssetAdministrationShells().size(), 0);
	ASSERT_EQ(envApi.getAssetAdministrationShell(Identifier::Custom("aas_1")), nullptr);
}

TEST_F(TestAasEnv, TestGet)
{
	AssetInformation asset_inf_1{ AssetKind::Instance };
	AssetAdministrationShell aas_1{ "aas_1", Identifier::IRI("https://admin-shell.io/cpp#aas_1"), asset_inf_1 };

	this->env.getAssetAdministrationShells().add(std::move(aas_1));

	AasEnvApi envApi(this->env);

	ASSERT_EQ(envApi.getAssetAdministrationShells().size(), 1);
	auto stored_aas = envApi.getAssetAdministrationShell(Identifier::IRI("https://admin-shell.io/cpp#aas_1"));
	ASSERT_NE(stored_aas, nullptr);
	ASSERT_EQ(stored_aas->getIdentification().getId(), "https://admin-shell.io/cpp#aas_1");
}

TEST_F(TestAasEnv, TestPut)
{
	AssetInformation asset_inf_1{ AssetKind::Instance };
	AssetAdministrationShell aas_1{ "aas_1", Identifier::IRI("https://admin-shell.io/cpp#aas_1"), asset_inf_1 };

	AssetInformation asset_inf_2{ AssetKind::Instance };
	AssetAdministrationShell aas_2{ "aas_2", Identifier::IRI("https://admin-shell.io/cpp#aas_2"), asset_inf_2 };

	AasEnvApi envApi(this->env);

	// Put a single AAS
	auto put_aas = envApi.addAssetAdministrationShell(aas_1);

	ASSERT_EQ(envApi.getAssetAdministrationShells().size(), 1);
	auto stored_aas = envApi.getAssetAdministrationShell(Identifier::IRI("https://admin-shell.io/cpp#aas_1"));
	ASSERT_EQ(put_aas, stored_aas);
	ASSERT_NE(stored_aas, nullptr);
	ASSERT_EQ(stored_aas->getIdentification().getId(), "https://admin-shell.io/cpp#aas_1");

	// Put the same AAS; expect nothing to happen
	auto no_put_aas = envApi.addAssetAdministrationShell(aas_1);
	ASSERT_EQ(envApi.getAssetAdministrationShells().size(), 1);
	ASSERT_EQ(no_put_aas, nullptr);

	// Put a second AAS
	auto put_aas_2 = envApi.addAssetAdministrationShell(aas_2);

	ASSERT_EQ(envApi.getAssetAdministrationShells().size(), 2);
	auto stored_aas_2 = envApi.getAssetAdministrationShell(Identifier::IRI("https://admin-shell.io/cpp#aas_2"));
	ASSERT_EQ(put_aas_2, stored_aas_2);
	ASSERT_NE(stored_aas_2, nullptr);
	ASSERT_EQ(stored_aas_2->getIdentification().getId(), "https://admin-shell.io/cpp#aas_2");
}
