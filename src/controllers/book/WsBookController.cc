#include "WsBookController.h"

using namespace api::v1;

void WsBookController::handleNewMessage(const WebSocketConnectionPtr& wsConnPtr, std::string &&message, const WebSocketMessageType &type)
{
    // write your application logic here
}

void WsBookController::handleNewConnection(const HttpRequestPtr &req, const WebSocketConnectionPtr& wsConnPtr)
{
    LOG_DEBUG << "new user connected: " << wsConnPtr->connected();
}

void WsBookController::handleConnectionClosed(const WebSocketConnectionPtr& wsConnPtr)
{
    LOG_DEBUG << "user disconnected: " << wsConnPtr->connected();
}
