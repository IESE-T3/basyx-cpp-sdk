#include <gtest/gtest.h>

#include <basyx/key.h>
#include <basyx/langstringset.h>
#include <basyx/reference.h>
#include <basyx/environment.h>
#include <basyx/assetadministrationshell.h>
#include <basyx/asset/assetinformation.h>
#include <basyx/submodel.h>

#include <basyx/enums/DataTypeDefinition.h>

#include <basyx/qualifiable/qualifier.h>

#include <basyx/submodelelement/multilanguageproperty.h>
#include <basyx/submodelelement/property.h>
#include <basyx/submodelelement/range.h>
#include <basyx/submodelelement/submodelelementcollection.h>
#include <basyx/submodelelement/entity.h>
#include <basyx/submodel.h>

#include <basyx/versionRevisionType.h>

#include <type_traits>

#include <basyx/base/basyx_enum_base.h>

using namespace basyx;

class BaseTest : public ::testing::Test {
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

TEST_F(BaseTest, LangStringSet)
{
    basyx::langstring_t l { "de", "test" };
    basyx::langstringset_t ls;

    ASSERT_EQ(ls.size(), 0);

    ls.add("en", "test");
    ASSERT_EQ(ls.size(), 1);

    ls.add(std::move(l));

    auto en = ls.get("en");
    auto de = ls.get("de");
    auto pl = ls.get("pl");

    ASSERT_TRUE(en);
    ASSERT_TRUE(de);
    ASSERT_FALSE(pl);

    ASSERT_EQ(*en, "test");
    ASSERT_EQ(*de, "test");
}

TEST_F(BaseTest, Reference)
{
    Key key { KeyElements::Asset, "test" };

    Reference reference_1{ ReferenceTypes::ExternalReference, key };
    ASSERT_EQ(reference_1.size(), 1);

    Reference reference_2( ReferenceTypes::ModelReference, { KeyElements::AssetAdministrationShell, "test" });
    ASSERT_EQ(reference_2.size(), 1);
};

TEST_F(BaseTest, MultiLangProp)
{
    basyx::MultiLanguageProperty mlp { "multiLang" };

    mlp.setCategory("test");
    ASSERT_TRUE(mlp.getCategory());
    ASSERT_EQ(mlp.getCategory().value(), "test");

    mlp.setDescription({ { "en", "example" },
        { "de", "beispiel" } });

    auto& description = mlp.getDescription();

    ASSERT_TRUE(description);
    ASSERT_EQ(description->size(), 2);

    auto ls1 = description->get("en");
    auto ls2 = description->get("de");

    ASSERT_EQ(*ls1, "example");
    ASSERT_EQ(*ls2, "beispiel");

};

TEST_F(BaseTest, Enum)
{
	auto none = DataTypeDefinition_::from_string("NONE");
	ASSERT_EQ(none, DataTypeDefinition::INVALID);

	auto found = DataTypeDefinition_::from_string("xs:byte");
	ASSERT_EQ(found, DataTypeDefinition::Byte);

	std::string str = DataTypeDefinition_::to_string(DataTypeDefinition::Base64Binary);
	ASSERT_EQ(str, "xs:base64Binary");
};

TEST_F(BaseTest, HasKind)
{
    Submodel sm("test",Identifier("testId"));
    sm.setKind(ModelingKind::Template);

    HasKind has_kind = static_cast<HasKind>(sm);
    ASSERT_EQ(ModelingKind::Template, has_kind.getKind());
};

TEST_F(BaseTest, RangeTest)
{
    Range<uint32_t> p1 { "int_prop" };
    p1.set_min(1);
    p1.set_max(5);

    ASSERT_EQ(*p1.get_min(), 1);
    ASSERT_EQ(*p1.get_max(), 5);
    ASSERT_EQ(p1.get_value_type(), "unsignedInt");
};

TEST_F(BaseTest, SubmodelElement)
{
    std::unique_ptr<SubmodelElement> prop = std::make_unique<MultiLanguageProperty>("mlp");
}

TEST_F(BaseTest, SubmodelElementCollection)
{
    SubmodelElementCollection col { "col" };
    SubmodelElementCollection col2 { "col2" };

    MultiLanguageProperty mlp("test");

    Property i { "i" };
    i.assign(5);

    col.getSubmodelElements().add(i);

    i.assign(6);

    col.getSubmodelElements().add(std::move(i));
    col.getSubmodelElements().add(mlp);

    mlp.get_value().add("en", "test");

    col2.getSubmodelElements().add(mlp);

    col.getSubmodelElements().add(std::move(col2));
};

TEST_F(BaseTest, SubmodelElementCollection_2)
{
    SubmodelElementCollection col { "col" };

    Property i1 { "i1", 2 };
    Property i2 { "i2", 5 };

    col.getSubmodelElements().add(i1);
    col.getSubmodelElements().add(i2);

    auto r0 = col.getSubmodelElements().get("none");
    ASSERT_EQ(r0, nullptr);

    auto r1 = col.getSubmodelElements().get("i1");
    ASSERT_NE(r1, nullptr);

    auto r2 = col.getSubmodelElements().get<Property>("i2");
    ASSERT_NE(r2, nullptr);
    ASSERT_EQ(r2->get_as<DataTypeDefinition::Integer>(), 5);
};

TEST_F(BaseTest, SubmodelElementCollection_3)
{
    SubmodelElementCollection col1("col1",
        Property("i1", 2),
        Property("f2", 5.0f),
        MultiLanguageProperty("mlp", {
            { "de", "beispiel" },
            { "en", "example" },
            }));

    ASSERT_EQ(col1.size(), 3);

    // Check first property
    auto prop1 = col1.getSubmodelElements().get("i1");
    ASSERT_EQ(prop1->get_model_type(), ModelTypes::Property);
};

TEST_F(BaseTest, SubmodelElementCollection_CopyConstructor)
{
    SubmodelElementCollection col1("col1",
        Property("i1", 2),
        Property("f2", 5.0f),
        MultiLanguageProperty("mlp", {
            { "de", "beispiel" },
            { "en", "example" },
    }));

    SubmodelElementCollection col2 = col1;
    SubmodelElementCollection col3(col1);
    auto col4 = std::make_unique<SubmodelElementCollection>(col1);

    ASSERT_EQ(col1.size(), 3);
    ASSERT_EQ(col2.size(), 3);
    ASSERT_EQ(col3.size(), 3);
    ASSERT_EQ(col4->size(), 3);

    ASSERT_EQ(col1.getIdShort(), "col1");
    ASSERT_EQ(col2.getIdShort(), "col1");
    ASSERT_EQ(col3.getIdShort(), "col1");
    ASSERT_EQ(col4->getIdShort(), "col1");
};


TEST_F(BaseTest, Submodel)
{
	Submodel sm("sm", "test/sm_1");

    sm.getSubmodelElements().add(Property("p1", 2));
    sm.getSubmodelElements().add(Property("p2", 3));

    sm.setSemanticId({ ReferenceTypes::ModelReference, { KeyElements::Submodel, "custom_submodel" } });
}

TEST_F(BaseTest, SubmodelAddElements)
{
	using stringProp_t = Property;

   Submodel sm("sm1", Identifier("https://admin-shell.io/cpp#sm1"));
	sm.setCategory("test");
    sm.setSemanticId({ ReferenceTypes::ExternalReference, { KeyElements::Submodel, "0173-1#02-AAR972#002" } });
	sm.setAdministration({ "1.0", "v2" });

   Submodel sm2("sm2", Identifier("https://admin-shell.io/cpp#sm2"));

	sm.getSubmodelElements().add(Property("testProperty1", "Yay a value!"));
	sm.getSubmodelElements().add(Property("testProperty2", "Values and values! :O"));

	ASSERT_EQ(sm.getSubmodelElements().size(), 2);

	auto * elem_1 = sm.getSubmodelElements().get<stringProp_t>("testProperty1");
	ASSERT_TRUE(elem_1 != nullptr);
	ASSERT_EQ(elem_1->get_as<DataTypeDefinition::String>(), "Yay a value!");

	auto * elem_2 = sm.getSubmodelElements().get<stringProp_t>("testProperty2");
	ASSERT_TRUE(elem_2 != nullptr);
	ASSERT_EQ(elem_2->get_as<DataTypeDefinition::String>(), "Values and values! :O");
}

TEST_F(BaseTest, EntityTest)
{
	Entity entity{ "entity" };
}

TEST_F(BaseTest, QualifierTest)
{
	std::unique_ptr<QualifierBase> constraint_qualifier = std::make_unique<Qualifier<int>>("test", 5);

	ASSERT_EQ(constraint_qualifier->get_model_type(), ModelTypes::Qualifier);
}

TEST_F(BaseTest, AutoIdentifierTest)
{
	AssetAdministrationShell aas{ "aas", "https://admin-shell.io/aas", { AssetKind::Instance } };

	Submodel sm{ "sm", "test/sm1" };
}

TEST_F(BaseTest, AssetInfTest)
{
   Identifier id("test");
	AssetInformation assetInf{ AssetKind::Instance };

   assetInf.globalAssetId = id;
};

TEST_F(BaseTest, AssetAdministrationShell)
{
	AssetAdministrationShell aas("aas", "https://admin-shell.io/aas", { AssetKind::Instance });
	aas.getSubmodels().add(Submodel("sm", "test/sm_1"));
}

TEST_F(BaseTest, Environment)
{
	Environment env;

	env.getAssetAdministrationShells().add(
		AssetAdministrationShell("aas", "https://admin-shell.io/aas", AssetInformation{ AssetKind::Instance })
	);
}

TEST_F(BaseTest, AssetInfoInAas)
{
      Identifier id("cppTestAsset");
		AssetInformation assetinfo(basyx::AssetKind::Instance);
      assetinfo.globalAssetId  = id;

		auto assetInfo2 = assetinfo;
		AssetAdministrationShell aas("cppAas", "cppAas", assetinfo);
}
