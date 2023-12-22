//#include <gtest/gtest.h>
//
//#include <basyx/api/aas_interface.h>
//#include <basyx/api/submodel_interface.h>
//#include <basyx/implementation/submodel_metamodel.h>
//#include <basyx/implementation/aas_metamodel.h>
//
//#include <basyx/submodelelement/range.h>
//#include <basyx/environment.h>
//
//using namespace basyx;
//using namespace api;
//
//class TestAasMetamodel : public ::testing::Test
//{
//protected:
//  OutputModifier om;
//  Environment env;
//
//  AssetInformation information{AssetKind::Instance};
//  AssetAdministrationShell assetAdministrationShell{"aas", Identifier::IRI("https://admin-shell.io/cpp#aas"), information};
//
//  std::unique_ptr<AASInterface> aas;
//  virtual void SetUp()
//  {
//    assetAdministrationShell.setSecurity(8);
//
//    aas = std::unique_ptr<AASMetamodel>(new AASMetamodel(&assetAdministrationShell));
//  }
//};
//
//TEST_F(TestAasMetamodel, TestGetAssetAdministration)
//{
//  auto response = aas->getAssetAdministrationShell(om);
//
//  ASSERT_TRUE(response.getStatus().success);
//  ASSERT_EQ(response.getStatus().statusCode, StatusCode::Success);
//
//  ASSERT_EQ(response.getPayload()->getIdShort(), "aas");
//}
//
//TEST_F(TestAasMetamodel, TestPutAssetAdministrationShell_NewShell)
//{
//  auto id = Identifier::IRI("https://admin-shell.io/cpp#aas1");
//  AssetInformation information{AssetKind::Instance};
//  AssetAdministrationShell aas1("aas1", id, information);
//
//  auto response = aas->putAssetAdministrationShell(aas1);
//
//  ASSERT_TRUE(response.getStatus().success);
//  ASSERT_EQ(response.getStatus().statusCode, StatusCode::Success);
//
//  ASSERT_EQ(response.getPayload()->getIdShort(), "aas1");
//}
//
//TEST_F(TestAasMetamodel, TestPutAssetAdministrationShell_ReplaceShell)
//{
//  auto id = Identifier::IRI("https://admin-shell.io/cpp#aas1");
//  AssetInformation information{AssetKind::Instance};
//  AssetAdministrationShell aas1("aas", id, information);
//
//  // put new aas
//  auto response = aas->putAssetAdministrationShell(aas1);
//
//  // should've been successful
//  ASSERT_TRUE(response.getStatus().success);
//  ASSERT_EQ(response.getStatus().statusCode, StatusCode::Success);
//  ASSERT_EQ(response.getPayload()->getIdShort(), "aas");
//
//  // Check if new aas is placed right
//  auto response_replaced = aas->getAssetAdministrationShell(om);
//
//  ASSERT_TRUE(response_replaced.getStatus().success);
//  ASSERT_EQ(response_replaced.getStatus().statusCode, StatusCode::Success);
//  ASSERT_EQ(response_replaced.getPayload()->getIdShort(), "aas");
//}
//
//TEST_F(TestAasMetamodel, TestPatchAssetAdministrationShell)
//{
//  // Build testing patch AAS
//  auto id = Identifier::IRI("https://admin-shell.io/cpp#aas");
//  AssetAdministrationShell shell{"aas", id, AssetInformation(AssetKind::Type)};
//
//  auto response = aas->patchAssetAdministrationShell(shell);
//
//  ASSERT_TRUE(response.getStatus().success);
//  ASSERT_EQ(response.getStatus().statusCode, StatusCode::Success);
//  //Check if old security is still set, to exclude that aas is overwritten completely
//  ASSERT_EQ(response.getPayload()->getSecurity(), 8);
//
//  // now add more patch values
//  Submodel sm{"sm1", "https://admin-shell.io/cpp#sm1"};
//  shell.getSubmodels().add(sm);
//
//  shell.setSecurity(4);
//
//  Reference derivedFrom("DerivedFrom");
//  shell.setDerivedFrom(derivedFrom);
//
//  AdministrativeInformation assetInformation("v2.0");
//  shell.setAdministration(assetInformation);
//
//  langstringset_t description("DE", "Beschreibung");
//  shell.setDescription(description);
//
//  shell.setCategory("Cat 5");
//
//  langstringset_t display_name("DE", "Die neue AAS");
//  shell.setDisplayname(display_name);
//
//  std::unique_ptr<Referable> range = std::unique_ptr<Range<int>>(new Range<int>{"range"});
//  shell.setParent(range.get());
//
//  // patch again
//  auto response_2 = aas->patchAssetAdministrationShell(shell);
//
//  // and check if everything is patched
//  ASSERT_TRUE(response_2.getStatus().success);
//  ASSERT_EQ(response_2.getStatus().statusCode, StatusCode::Success);
//
//  ASSERT_EQ(response_2.getPayload()->getSecurity(), 4);
//
//  ASSERT_EQ(response_2.getPayload()->getDerivedFrom()->get_key(0).get_value(), "DerivedFrom");
//
//  ASSERT_EQ(response_2.getPayload()->getAdministration().value().get_version(), "v2.0");
//
//  ASSERT_EQ(response_2.getPayload()->getDescription().value().get("DE"), "Beschreibung");
//
//  ASSERT_EQ(response_2.getPayload()->getCategory(), "Cat 5");
//
//  ASSERT_EQ(response_2.getPayload()->getDisplayname().value().get("DE"), "Die neue AAS");
//
//  ASSERT_EQ(response_2.getPayload()->getParent()->getIdShort(), "range");
//}
//
//TEST_F(TestAasMetamodel, TestPutSubmodelReference)
//{
//
//}
//
//TEST_F(TestAasMetamodel, TestRemoveSubmodelReference)
//{
//
//}
//
