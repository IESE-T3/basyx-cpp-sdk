//#ifndef BASYX_http_HTTPHANDLER_H
//#define BASYX_http_HTTPHANDLER_H
//
//#include <basyxpp-http/httplib/httplib.h>
//#include <basyxpp-http/HttpHandler.h>
//
//#include <basyx/submodel.h>
//
//#include <basyx/util/string_view/string_view.hpp>
//#include <basyx/util/algorithm/string.hpp>
//
//#include <string>
//#include <unordered_map>
//#include <mutex>
//#include <basyx/api/submodel_interface.h>
//#include <basyx/implementation/submodel_metamodel.h>
//
//namespace basyx {
//namespace http {
//
//class SubmodelRepositoryHttpHandler : public HttpHandler
//{
//public:
//	using pathList_t = util::algorithm::string::splitList_t<char>;
//private:
//	std::unordered_map<std::string, basyx::Submodel*> submodels;
//	std::mutex submodelMutex;
//public:
//	SubmodelElement * getSubmodelElementByPathList(pathList_t & pathList, Submodel & sm);
//
//public:
//  void registerHandleRequests() override;
//	SubmodelRepositoryHttpHandler(std::string ip, uint16_t port, int json_intend_level = 4);
//	~SubmodelRepositoryHttpHandler() = default;
//
//public:
//  util::optional<api::SubmodelMetamodel> getSubmodel(util::string_view idShort);
//
//	bool submodelExists(Submodel & submodel);
//	bool submodelExists(util::string_view idShort);
//
//	ERROR_CODES addSubmodelToServer(Submodel & submodel);
//	ERROR_CODES removeSubmodelFromServer(Submodel & submodel);
//
//private:
//  void submodel_not_found(const util::string_view & idShort, httplib::Response& res) const;
//};
//
//}
//}
//
//
//
//#endif // BASYX_http_HTTPHANDLER_H
