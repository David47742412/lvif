#include "WsBookController.h"

using namespace api::v1;

void WsBookController::handleNewMessage(const WebSocketConnectionPtr &wsConnPtr, std::string &&message,
                                        const WebSocketMessageType &type) {
    try {
        if (type == WebSocketMessageType::Pong) return;

        Json::Reader reader;
        Json::Value body;
        bool transform = reader.parse(message, body);

        if (transform) {
            auto context = wsConnPtr->getContext<Subscriber>();
            switch (body["action"].asInt()) {
                case 1:
                    BookService::insert(body, context->userId, context->workspace, context->ip);
                    break;
                default:
                    break;
            }
        }

        _room.publish("book", BookService::find().toStyledString());
    } catch (const std::runtime_error &ex) {
        LOG_DEBUG << ex.what();
    }
}

void WsBookController::handleNewConnection(const HttpRequestPtr &req, const WebSocketConnectionPtr &wsConnPtr) {
    try {
        wsConnPtr->send(BookService::find().toStyledString());
        Subscriber subscriber;
        subscriber.userId = req->getParameter("user_id");
        subscriber.workspace = req->getHeader("User-Agent");
        subscriber.ip = req->getPeerAddr().toIp();
        subscriber.id = _room.subscribe("book",
                                        [wsConnPtr](const std::string &topic, const std::string &message) {
                                            wsConnPtr->send(message);
                                        });
        wsConnPtr->setContext(std::make_shared<Subscriber>(std::move(subscriber)));
    } catch (const std::runtime_error &ex) {
        LOG_DEBUG << ex.what();
    }
}

void WsBookController::handleConnectionClosed(const WebSocketConnectionPtr &wsConnPtr) {
    const auto &subscriber = wsConnPtr->getContextRef<Subscriber>();
    _room.unsubscribe("book", subscriber.id);
}
