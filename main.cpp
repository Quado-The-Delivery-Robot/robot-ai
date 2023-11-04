#include <iostream>
#include <cstdio>
#include "apiChecker.h"
#include "webServer.h"
#include "vision.h"
#include "startNgrok.h"
#include "redirectLogs.h"

using namespace std;

int main() {
	const bool logsRedirected = redirectLogs();

	if (!logsRedirected) {
		cout << "Failed to redirect logs." << endl;
		return EXIT_FAILURE;
	}

	const bool externalApiIsFunctional = runApiChecker();

	// If the API is not functional then we cannot continue.
	// The robot relies on the API for instructions.
	if (!externalApiIsFunctional) {
		cout << "API is not online/functional. Exiting program." << endl;
		return EXIT_FAILURE;
	}

	// Start the web server controllers.
	struct mg_context* webServer = startWebServer();

	// ngrok is used to forward the server to the web.
	FILE* ngrokProcess = startNgrok();

	// Start the robot vision.
	runVision();

	// Perform exit operations.
	
	// Stop ngrok.
	stopNgrok(ngrokProcess);

	// Stop the web server.
	mg_stop(webServer);
	mg_exit_library();

	// Stop redirecting logs.
	stopRedirectingLogs();

	return EXIT_SUCCESS;
};