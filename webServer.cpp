#include <iostream>
#include <CivetServer.h>
#include "webServer.h"
#include "startRouteRequestHandler.h"

using namespace std;

const char* serverOptions[] = {
    "document_root", "",
    "listening_ports", "2000",
    0
};

// Starts the local web server to allow for communcation between the robot and external API.
struct mg_context* startWebServer() {
    struct mg_context* server;

    mg_init_library(0);

    server = mg_start(NULL, 0, serverOptions);

    // Start route handlers.
    mg_set_request_handler(server, "/start", startRouteRequestHandler, nullptr);

    cout << "Started web server." << endl;

    return server;
}