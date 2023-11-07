#pragma once

#include <drogon/WebSocketController.h>
#include <fmt/format.h>
#include <drogon/PubSubService.h>
#include <src/service/book/book-service.hxx>

using namespace drogon;

namespace api::v1 {
    class WsBookController : public drogon::WebSocketController<WsBookController> {
    public:
        void handleNewMessage(const WebSocketConnectionPtr &,
                              std::string &&,
                              const WebSocketMessageType &) override;

        void handleNewConnection(const HttpRequestPtr &,
                                 const WebSocketConnectionPtr &) override;

        void handleConnectionClosed(const WebSocketConnectionPtr &) override;

        WS_PATH_LIST_BEGIN
            // list path definitions here;
            WS_PATH_ADD("/api/v1/book", "api::v1::JwtFilter");
        WS_PATH_LIST_END

    private:
        PubSubService <std::string> _room;
        struct Subscriber {
            std::string userId;
            std::string roomName;
            std::string workspace;
            std::string ip;
            drogon::SubscriberID id;
        };
    };
}