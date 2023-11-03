#include <iostream>
#include <thread>
#include "apiChecker.h"
#include "webServer.h"
#include "vision.h"
#include "communicateWebServerAddress.h"

using namespace std;

thread ngrokThread;

void stopNgrokThread() {
	cout << "Attemping to stop ngrok." << endl;

	if (ngrokThread.joinable()) {
		ngrokThread.join();
		stopNgrok();
	}
}

int main() {
	const bool externalApiIsFunctional = runApiChecker();

	// If the API is not functional then we cannot continue.
	// The robot relies on the API for instructions.
	if (externalApiIsFunctional == false) {
		cout << "API is not online/functional. Exiting program." << endl;
		return -1;
	}

	// Start the web server controllers.
	struct mg_context* webServer = startWebServer();

	// ngrok is used to forward the server to the web.
	ngrokThread = thread(startNgrok);
	atexit(stopNgrokThread);

	runVision();

	// Perform exit operations.
	
	// Stop the web server.
	mg_stop(webServer);
	mg_exit_library();

	return EXIT_SUCCESS;
};