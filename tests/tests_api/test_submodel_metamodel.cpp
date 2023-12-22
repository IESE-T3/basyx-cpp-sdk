//#include <gtest/gtest.h>
//
//#include <basyx/api/submodel_interface.h>
//#include <basyx/implementation/submodel_metamodel.h>
//
//#include <basyx/submodelelement/range.h>
//#include <basyx/submodelelement/blob.h>
//
//using namespace basyx;
//using namespace api;
//
//class TestSubmodelMetamodel : public ::testing::Test
//{
//protected:
//  OutputModifier om;
//
//  std::unique_ptr<SubmodelInterface> sm;
//
//  Submodel submodel{"sm", Identifier::IRI("https://admin-shell.io/cpp#sm")};
//
//  Range<int> range{std::string{"range"}};
//  Blob blob{"blob", "image/gif"};
//  virtual void SetUp()
//  {
//    // Add some submodelElements
//    range.set_max(5);
//    range.set_max(55);
//    submodel.getSubmodelElements().add(range);
//
//    submodel.getSubmodelElements().add(blob);
//
//
//    sm = std::unique_ptr<SubmodelMetamodel>(new SubmodelMetamodel(&submodel));
//  }
//};
//
//
//TEST_F(TestSubmodelMetamodel, TestGetSubmodel)
//{
//  auto response = sm->getSubmodel(om);
//  ASSERT_TRUE(response.getStatus().success);
//  ASSERT_EQ(response.getStatus().statusCode, StatusCode::Success);
//  ASSERT_EQ(std::string("sm"), response.getPayload()->getIdShort().to_string());
//}
//
//TEST_F(TestSubmodelMetamodel, TestGetAllSubmodelElements)
//{
//  auto response = sm->getAllSubmodelElements(Depth::NonRecursive, om);
//
//  ASSERT_TRUE(response.getStatus().success);
//  ASSERT_EQ(response.getStatus().statusCode, StatusCode::Success);
//
//  ASSERT_EQ(response.getPayload()->size(), 2);
//}
//
//TEST_F(TestSubmodelMetamodel, TestGetAllSubmodelElementsByParentPathAndSemanticId)
//{
//  //TODO
//}
//
//TEST_F(TestSubmodelMetamodel, TestGetAllSubmodelElementsBySemanticId)
//{
//  //TODO
//}
//
//TEST_F(TestSubmodelMetamodel, TestGetSubmodelElementByPath)
//{
//  //TODO
//  Reference path{"range"};
//  auto response = sm->getSubmodelElementByPath(path, om);
//}
//
//TEST_F(TestSubmodelMetamodel, TestPutSubmodelElementByPath)
//{
//  //TODO
//}
//
//TEST_F(TestSubmodelMetamodel, TestSetSubmodelElementValueByPath)
//{
//  //TODO
//}
//
//TEST_F(TestSubmodelMetamodel, TestDeleteSubmodelElementByPath)
//{
//  //TODO
//}
//
//TEST_F(TestSubmodelMetamodel, TestInvokeOperationSync)
//{
//  //TODO
//}
//
//TEST_F(TestSubmodelMetamodel, TestInvokeOperationAsync)
//{
//  //TODO
//}
//
//TEST_F(TestSubmodelMetamodel, TestGetOperationAsyncResult)
//{
//  //TODO
//}
