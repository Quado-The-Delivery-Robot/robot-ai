#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <atomic>

#ifdef _WIN32
#include <windows.h>
#else
#include <sys/types.h>
#include <unistd.h>
#endif

#include "communicateWebServerAddress.h"

using namespace std;

const char* ngrokCommand = "C:\\Users\\mredm\\source\\repos\\Quado-The-Delivery-Robot\\quado\\ngrok.exe http 2000 2>ngrok_error.txt";
atomic<int> ngrokPID = 0;

// Starts running ngrok.
void startNgrok() {
    // Execute the Ngrok command and capture the output
    std::string commandOutput;
    FILE* pipe = _popen(ngrokCommand, "r");
    if (!pipe) {
        return;  // Indicate an error
    }

    char buffer[128];
    while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
        commandOutput += buffer;
    }

    _pclose(pipe);

    // Parse the Ngrok output to extract the tunnel address
    size_t addressStart = commandOutput.find("Forwarding                    http://");
    if (addressStart != std::string::npos) {
        size_t addressEnd = commandOutput.find(" ->", addressStart);

        cout << commandOutput.substr(addressStart, addressEnd - addressStart) << endl;

        if (addressEnd != std::string::npos) {
            // Extract the PID from the command output (if available)
            size_t pidStart = commandOutput.find("pid ", addressStart);
            if (pidStart != std::string::npos) {
                ngrokPID.store(std::stoi(commandOutput.substr(pidStart + 4, addressStart - pidStart - 4)));
            }
        }
    }
}

// Stops the ngrok server.
void stopNgrok() {
#ifdef _WIN32
    TerminateProcess(OpenProcess(PROCESS_TERMINATE, FALSE, ngrokPID.load()), 0);
#else
    kill(ngrokPID.load(), SIGTERM);
#endif
}