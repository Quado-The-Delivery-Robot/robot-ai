#pragma once

#ifndef HEADER_CONTROLLERS_SOFTWARE_WEBSERVER
#define HEADER_CONTROLLERS_SOFTWARE_WEBSERVER

#include <CivetServer.h>

struct mg_context* startWebServer();

#endif