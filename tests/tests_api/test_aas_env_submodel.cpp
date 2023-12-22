#include <gtest/gtest.h>

#include <basyx/api/aas_api.h>
#include <basyx/api/impl/aas_env_api.h>

#include <basyx/environment.h>

using namespace basyx;
using namespace basyx::api;


class TestAasEnvSubmodelApi : public ::testing::Test
{
protected:
	Environment env;
	std::unique_ptr<AasEnvApi> aasEnvApi;

	virtual void SetUp()
	{
		AssetInformation asset_inf_1{ AssetKind::Instance };
		AssetAdministrationShell aas_1{ "aas_1", Identifier::IRI("https://admin-shell.io/cpp#aas"), asset_inf_1 };

		Submodel sm1{ "sm_1", Identifier::Custom("submodel_1") };
		sm1.getSubmodelElements().create<Property<int>>("prop_1",0);
		sm1.getSubmodelElements().create<SubmodelElementCollection>("coll_1", 
			Property<int>("sub_prop_1", 1),
			Property<int>("sub_prop_2", 2)
		);

		aas_1.getSubmodels().add(std::move(sm1));

		Submodel sm2{ "sm_2", Identifier::Custom("submodel_2") };
		aas_1.getSubmodels().add(std::move(sm2));

		env.getAssetAdministrationShells().add(std::move(aas_1));

		aasEnvApi = std::make_unique<AasEnvApi>(env);
	};
};

TEST_F(TestAasEnvSubmodelApi, Test_1)
{
	auto sm_0 = aasEnvApi->getSubmodel("aas_1", "sm_0");
	auto sm_1 = aasEnvApi->getSubmodel("aas_1", "sm_1");

	ASSERT_FALSE(sm_0);
	ASSERT_TRUE(sm_1);

	auto view_sm1 = sm_1->getSubmodel();
	ASSERT_EQ(view_sm1.getIdShort(), "sm_1");

	auto list = sm_1->getAllSubmodelElements();
	ASSERT_EQ(list.size(), 2);
}

TEST_F(TestAasEnvSubmodelApi, Test_getAllSubmodelElementsByPath)
{
	auto sm_1 = aasEnvApi->getSubmodel("aas_1", "sm_1");

	auto list = sm_1->getAllSubmodelElementsByPath("");
	ASSERT_EQ(list.size(), 2);
	
	list = sm_1->getAllSubmodelElementsByPath("/");
	ASSERT_EQ(list.size(), 2);
	
	list = sm_1->getAllSubmodelElementsByPath("/nil");
	ASSERT_EQ(list.size(), 0);
	
	list = sm_1->getAllSubmodelElementsByPath("/prop_1");
	ASSERT_EQ(list.size(), 1);
	
	list = sm_1->getAllSubmodelElementsByPath("/prop_1/nil");
	ASSERT_EQ(list.size(), 0);
	
	list = sm_1->getAllSubmodelElementsByPath("/coll_1/");
	ASSERT_EQ(list.size(), 2);
	
	list = sm_1->getAllSubmodelElementsByPath("/coll_1/sub_prop_1");
	ASSERT_EQ(list.size(), 1);
	
	list = sm_1->getAllSubmodelElementsByPath("/coll_1/sub_prop_1/nil");
	ASSERT_EQ(list.size(), 0);
}

TEST_F(TestAasEnvSubmodelApi, Test_addSubmodelElement)
{
	Property<int> new_prop("new_prop", 42);

	auto sm_1 = aasEnvApi->getSubmodel("aas_1", "sm_1");

	// Check pre-condition
	ASSERT_EQ(sm_1->getAllSubmodelElements().size(), 2);
	ASSERT_EQ(sm_1->getAllSubmodelElementsByPath("/coll_1").size(), 2);

	// Add at root
	ASSERT_TRUE(sm_1->addSubmodelElement(new_prop));
	ASSERT_EQ(sm_1->getAllSubmodelElementsByPath("new_prop").size(), 1);

	// Add with id already existing, fail
	ASSERT_FALSE(sm_1->addSubmodelElement(new_prop));
	ASSERT_EQ(sm_1->getAllSubmodelElementsByPath("new_prop").size(), 1);
};

TEST_F(TestAasEnvSubmodelApi, Test_addSubmodelElementByPath)
{
	auto sm_1 = aasEnvApi->getSubmodel("aas_1", "sm_1");

	Property<int> new_prop("new_prop", 42);

	// Check pre-condition
	ASSERT_EQ(sm_1->getAllSubmodelElements().size(), 2);
	ASSERT_EQ(sm_1->getAllSubmodelElementsByPath("/coll_1").size(), 2);

	// Add at root
	ASSERT_TRUE(sm_1->addSubmodelElementByPath(new_prop, "/"));
	ASSERT_EQ(sm_1->getAllSubmodelElements().size(), 3);
	ASSERT_EQ(sm_1->getAllSubmodelElementsByPath("new_prop").size(), 1);

	// Add at root with id already existing, fail
	ASSERT_FALSE(sm_1->addSubmodelElementByPath(new_prop, "/"));
	ASSERT_EQ(sm_1->getAllSubmodelElements().size(), 3);
	ASSERT_EQ(sm_1->getAllSubmodelElementsByPath("new_prop").size(), 1);

	// Add at non existing element, fail
	ASSERT_FALSE(sm_1->addSubmodelElementByPath(new_prop, "/nil/"));
	ASSERT_EQ(sm_1->getAllSubmodelElements().size(), 3);

	// Add in collection, pass
	ASSERT_TRUE(sm_1->addSubmodelElementByPath(new_prop, "/coll_1"));
	ASSERT_EQ(sm_1->getAllSubmodelElementsByPath("/coll_1").size(), 3);
	ASSERT_EQ(sm_1->getAllSubmodelElementsByPath("/coll_1/new_prop").size(), 1);

	// Add under non-collection element, fail
	ASSERT_FALSE(sm_1->addSubmodelElementByPath(new_prop, "/prop_1/"));
};

TEST_F(TestAasEnvSubmodelApi, Test_deleteSubmodelElementByPath)
{
	auto sm_1 = aasEnvApi->getSubmodel("aas_1", "sm_1");

	// Check pre-condition
	ASSERT_EQ(sm_1->getAllSubmodelElements().size(), 2);
	ASSERT_EQ(sm_1->getAllSubmodelElementsByPath("/coll_1").size(), 2);

	// Delete non-existant, no-op
	ASSERT_FALSE(sm_1->deleteSubmodelElementByPath("/nil"));
	ASSERT_EQ(sm_1->getAllSubmodelElements().size(), 2);
	ASSERT_EQ(sm_1->getAllSubmodelElementsByPath("/coll_1").size(), 2);

	// Delete element, pass
	ASSERT_TRUE(sm_1->deleteSubmodelElementByPath("/prop_1"));
	ASSERT_EQ(sm_1->getAllSubmodelElements().size(), 1);

	// Delete same element again, no-op
	ASSERT_FALSE(sm_1->deleteSubmodelElementByPath("/prop_1"));
	ASSERT_EQ(sm_1->getAllSubmodelElements().size(), 1);

	// Delete sub-element, pass
	ASSERT_TRUE(sm_1->deleteSubmodelElementByPath("/coll_1/sub_prop_1"));
	ASSERT_EQ(sm_1->getAllSubmodelElements().size(), 1);
	ASSERT_EQ(sm_1->getAllSubmodelElementsByPath("/coll_1").size(), 1);
};

TEST_F(TestAasEnvSubmodelApi, Test_deleteSubmodelElementByPath_2)
{
	auto sm_1 = aasEnvApi->getSubmodel("aas_1", "sm_1");

	// Check pre-condition
	ASSERT_EQ(sm_1->getAllSubmodelElements().size(), 2);
	ASSERT_EQ(sm_1->getAllSubmodelElementsByPath("/coll_1").size(), 2);

	// Delete first element, pass
	ASSERT_TRUE(sm_1->deleteSubmodelElementByPath("/"));
	ASSERT_EQ(sm_1->getAllSubmodelElements().size(), 0);
};