#include <iostream>
#include <string>
#include <cstdio>
#include <chrono>
#include <thread>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include "startNgrok.h"

using namespace cpr;
using namespace std;
using json = nlohmann::json;

const int functionalCodeMin = 200;
const int functionalCodeMax = 299;

FILE* startNgrokProcess() {
    const char* ngrokCommand = "ngrok --config ngrokConfig.yml start --all";
    FILE* ngrokProcess = _popen(ngrokCommand, "r");
    return ngrokProcess;
}

// Starts ngrok.
FILE* startNgrok() {
    FILE* ngrokProcess = startNgrokProcess();

    // Wait until ngrok has started.
    while (true) {
        Response fetch = Get(Url{ "http://localhost:4040/api/tunnels" });

        if (fetch.status_code >= functionalCodeMin && fetch.status_code <= functionalCodeMax) {
            json response = json::parse(fetch.text)["tunnels"][0];

            if (response["public_url"] != nullptr) {
                break;
            }
        }

        // Delay so that we dont overload the program.
        this_thread::sleep_for(chrono::milliseconds(100));
    }

    // Get the url.
    Response fetch = Get(Url{ "http://localhost:4040/api/tunnels" });
    json response = json::parse(fetch.text)["tunnels"][0];

    cout << "Public ngrok url: " << response["public_url"] << endl;

    return ngrokProcess;
}

// Stops ngrok.
void stopNgrok(FILE* ngrokProcess) {
    if (ngrokProcess == nullptr) {
        return;
    }

    _pclose(ngrokProcess);
}