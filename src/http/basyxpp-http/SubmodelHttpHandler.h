//#ifndef BASYX_C_SDK_2_0_SUBMODELHTTPHANDLER_H
//#define BASYX_C_SDK_2_0_SUBMODELHTTPHANDLER_H
//
//
//#include <string>
//#include <basyx/api/submodel_interface.h>
//#include <basyxpp-http/httplib/httplib.h>
//#include "HttpHandler.h"
//
//namespace basyx
//{
//
//class SubmodelHttpHandler : public HttpHandler
//{
//private:
//  std::unique_ptr<basyx::api::SubmodelInterface> submodelInterface;
//
//public:
//  SubmodelHttpHandler(std::unique_ptr<api::SubmodelInterface> submodel, std::string ip, uint16_t port, int json_indent_level = 4);
//
//  ~SubmodelHttpHandler() = default;
//
//  void registerHandleRequests() override;
//
//};
//
//}
//
//#endif //BASYX_C_SDK_2_0_SUBMODELHTTPHANDLER_H
