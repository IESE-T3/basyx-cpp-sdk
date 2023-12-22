#pragma once

#include <basyxpp-http/httplib/httplib.h>

#include <basyx/api/aas_api.h>

#include <basyx/util/string_view/string_view.hpp>

namespace basyx {
namespace http {

class HttpHandler
{
public:
private:
	std::string host;
	int port;
private:
	httplib::Server server;
	std::unique_ptr<basyx::api::AasInterface> api;
public:
	HttpHandler(util::string_view host, int port);
private:
	template<typename Handler>
	auto bind_front_handler(Handler && handler) {
		return [this, handler](const httplib::Request& req, httplib::Response& res) {
			((*this).*handler)(req, res);
		};
	}
private:
	void handle_get_aas(const httplib::Request& req, httplib::Response& res);
public:
	void run();
	void stop();
public:
	template<typename ApiImpl, typename ... Args>
	static std::unique_ptr<HttpHandler> make_http_handler(util::string_view host, int port, Args&&... args) 
	{
		auto handler = std::make_unique<HttpHandler>(host, port);
		handler->api = std::make_unique<ApiImpl>(std::forward<Args>(args)...);
		return handler;
	};
};

}
}


//#ifndef BASYX_C_SDK_2_0_HTTPHANDLER_H
//#define BASYX_C_SDK_2_0_HTTPHANDLER_H
//
//#include <basyxpp-http/httplib/httplib.h>
//
//#include <basyx/serialization/json/serializer.h>
//
//#include <basyx/api/status_code.h>
//#include <basyx/api/response.h>
//#include <basyx/api/output_modifier.h>
//
//#define TXT_PLAIN "text/plain"
//#define TXT_JSON "application/json"
//
//namespace basyx
//{
//
//enum ERROR_CODES
//{
//    ERR_OK = 1,
//    ERR_NOP = 0,
//    ERR_PORT_UNAVAILABLE = -1,
//    ERR_ALREADY_EXISTS = -2,
//    ERR_DOES_NOT_EXIST = -3,
//};
//
//class HttpHandler
//{
//private:
//    std::string ip;
//    uint16_t port;
//
//    int json_indent_level;
//protected:
//    api::OutputModifier regular_om{api::Level::Core, api::Content::Normal, api::Extent::WithoutBLOBValue};
//    httplib::Server server;
//public:
//    HttpHandler(std::string ip, uint16_t port, int json_intent_level);
//
//    /**
//        * This message needs to be implemented by all HTTPHandler's to register corresponding requests.
//        */
//    virtual void registerHandleRequests() = 0;
//
//    void run();
//
//    void stop();
//
//private:
//    ERROR_CODES listen();
//
//protected:
//    /**
//        * Log the actual message processing state.
//        * @param statusCode The StatusCode to log.
//        * @param request
//        */
//    void log_status(api::StatusCode statusCode, const httplib::Request & request);
//
//    /**
//        * Generate an empty response message with status information.
//        * @param statusCode of the interface, representing the requested entity.
//        * @param outgoingResponse The response message to be enriched.
//        */
//    void empty_response_message(api::StatusCode statusCode, httplib::Response & outgoingResponse);
//
//    /**
//        * Enriches the outgoing message with the status of the request and appends the serialized content of the requested object.
//        * @tparam T The type of the content to be serialized.
//        * @param interfaceResponse Response of the interface, representing the requested entity.
//        * @param outgoingResponse The response message to be enriched.
//        */
//    template<class T>
//    void response_message_with_content(basyx::api::Response<T> & interfaceResponse, httplib::Response & outgoingResponse)
//    {
//        auto status = interfaceResponse.getStatus();
//        if (status.success)
//        {
//            auto json = basyx::serialization::json::serialize(*interfaceResponse.getPayload());
//
//            outgoingResponse.set_content(json.dump(json_indent_level), TXT_JSON);
//            outgoingResponse.status = 200;
//        }
//        else
//        {
//            std::string status_message = api::StatusCode_::to_string(status.statusCode);
//            if (status.message)
//                status_message += std::string(" ") + std::string(status.message->data());
//
//            outgoingResponse.set_content(status_message, TXT_PLAIN);
//            outgoingResponse.status = static_cast<int>(status.statusCode);
//        }
//    }
//
//    /**
//        * Retrieves only the values from a json
//        * @param json the json to retrieve values from.
//        * @return A json-array, consisting of just values
//        */
//    nlohmann::json get_submodelElement_value_json(nlohmann::json & json);
//
//    /**
//        * Similar to response_message_with_content(), but only responding the associated values.
//        */
//    template<class T>
//    void response_message_with_content_values(basyx::api::Response <T> & interfaceResponse, httplib::Response & outgoingResponse)
//    {
//        auto status = interfaceResponse.getStatus();
//        if (status.success)
//        {
//            auto json = basyx::serialization::json::serialize(*interfaceResponse.getPayload());
//            auto value_json = get_submodelElement_value_json(json);
//
//            outgoingResponse.set_content(value_json.dump(json_indent_level), TXT_JSON);
//            outgoingResponse.status = 200;
//        }
//        else
//        {
//            std::string status_message = api::StatusCode_::to_string(status.statusCode);
//            if (status.message)
//                status_message += std::string(" ") + std::string(status.message->data());
//
//            outgoingResponse.set_content(status_message, TXT_PLAIN);
//            outgoingResponse.status = static_cast<int>(status.statusCode);
//        }
//    }
//};
//
//}
//
//#endif //BASYX_C_SDK_2_0_HTTPHANDLER_H
