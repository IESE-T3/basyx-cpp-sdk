//#include "SubmodelHttpHandler.h"
//
//#include <basyx/implementation/submodel_metamodel.h>
//
//#include <spdlog/spdlog.h>
//
//using namespace basyx;
//using namespace basyx::api;
//
//using basyx::serialization::json::serialize;
//
//const std::string regex_seIdShortPath = R"((\w+(/\w+)?))";
//const std::string regex_IdShortPathToOperation = R"((\w+(/\w+)?))";
//const std::string regex_requestId = R"((\w+))";
//
//SubmodelHttpHandler::SubmodelHttpHandler(std::unique_ptr<api::SubmodelInterface> submodel, std::string ip, uint16_t port, int json_indent_level) :
//    HttpHandler(ip, port, json_indent_level)
//{
//    this->submodelInterface = std::move(submodel);
//}
//
//void SubmodelHttpHandler::registerHandleRequests()
//{
//    // Retrieves the entire Submodel
//    server.Get("/submodel/?",
//        [this](const httplib::Request& req, httplib::Response& res)
//    {
//        auto interface_response = submodelInterface->getSubmodel(regular_om);
//        this->log_status(interface_response.getStatus().statusCode, req);
//
//        this->response_message_with_content(interface_response, res);
//    });
//
//    // Retrieves the minimized version of a Submodel, i.e. only the values of SubmodelElements are serialized and returned
//    server.Get("/submodel/values/?",
//        [this](const httplib::Request& req, httplib::Response& res)
//    {
//        spdlog::warn("Method not yet implementd!");
//        res.set_content("Method not yet implementd!", TXT_PLAIN);
//
//        //    TODO: Implement ElementContainer serialization
//        //    auto interface_response = submodelInterface->getAllSubmodelElements(DepthEnum::NonRecursive, regular_om);
//        //    this->log_status(interface_response.getStatus().statusCode, req);
//        //
//        //    this->response_message_with_content_values(interface_response, res);
//    });
//
//    // Retrieves all Submodel-Elements from the Submodel
//    server.Get("/submodel/submodelElements/?",
//        [this](const httplib::Request& req, httplib::Response& res)
//    {
//        spdlog::warn("Method not yet implementd!");
//        res.set_content("Method not yet implementd!", TXT_PLAIN);
//
//        //    TODO: Implement ElementContainer serialization
//        //    auto interface_response = submodelInterface->getAllSubmodelElements(DepthEnum::NonRecursive, regular_om);
//        //    this->log_status(interface_response.getStatus().statusCode, req);
//        //
//        //    response_message_with_content(interface_response, res);
//    });
//
//    // Creates or updates a Submodel-Element at the Submodel
//    server.Put("/submodel/submodelElements/" + regex_seIdShortPath,
//        [this](const httplib::Request& req, httplib::Response& res)
//    {
//        Reference ref{ util::string_view{req.matches[1].str()} };
//
//        StatusCode status_code = submodelInterface->setSubmodelElementValueByPath(ref, req.body);
//        this->log_status(status_code, req);
//
//        empty_response_message(status_code, res);
//    });
//
//    // Retrieves a specific Submodel-Element from the Submodel
//    server.Get("/submodel/submodelElements/" + regex_seIdShortPath,
//        [this](const httplib::Request& req, httplib::Response& res)
//    {
//        Reference ref{ util::string_view{req.matches[1].str()} };
//
//        auto interface_response = submodelInterface->getSubmodelElementByPath(ref, regular_om);
//        this->log_status(interface_response.getStatus().statusCode, req);
//
//        response_message_with_content(interface_response, res);
//    });
//
//    // Deletes a specific Submodel-Element from the Submodel
//    server.Delete("/submodel/submodelElements/" + regex_seIdShortPath,
//        [this](const httplib::Request& req, httplib::Response& res)
//    {
//        Reference ref{ util::string_view{req.matches[1].str()} };
//
//        StatusCode status_code = submodelInterface->deleteSubmodelElementByPath(ref);
//        this->log_status(status_code, req);
//
//        empty_response_message(status_code, res);
//    });
//
//    // Retrieves the value of a specific Submodel-Element from the Submodel
//    server.Get("/submodel/submodelElements/" + regex_seIdShortPath + "/value/?",
//        [this](const httplib::Request& req, httplib::Response& res)
//    {
//        Reference ref{ util::string_view{req.matches[1].str()} };
//
//        auto interface_response = submodelInterface->getSubmodelElementByPath(ref, regular_om);
//        this->log_status(interface_response.getStatus().statusCode, req);
//
//        response_message_with_content_values(interface_response, res);
//    });
//
//    // Updates the Submodel-Element's value
//    server.Put("/submodel/submodelElements/" + regex_seIdShortPath + "/value/?",
//        [this](const httplib::Request& req, httplib::Response& res)
//    {
//        Reference ref{ util::string_view{req.matches[1].str()} };
//
//        StatusCode status_code = submodelInterface->setSubmodelElementValueByPath(ref, req.body);
//        this->log_status(status_code, req);
//
//        empty_response_message(status_code, res);
//    });
//
//    // Invokes a specific operation from the Submodel synchronously or asynchronously
//    server.Post("/submodel/submodelElements" + regex_IdShortPathToOperation + "/invoke/?",
//        [this](const httplib::Request& req, httplib::Response& res)
//    {
//        spdlog::warn("Method not yet implementd!");
//        res.set_content("Method not yet implementd!", TXT_PLAIN);
//    });
//
//    // Retrieves the result of an asynchronously started operation
//    server.Get("/submodel/submodelElements" + regex_IdShortPathToOperation + "/invocationList/" + regex_requestId,
//        [this](const httplib::Request& req, httplib::Response& res)
//    {
//        spdlog::warn("Method not yet implementd!");
//        res.set_content("Method not yet implementd!", TXT_PLAIN);
//    });
//}
