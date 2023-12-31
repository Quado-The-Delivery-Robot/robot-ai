#include <iostream>
#include <string>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include "apiChecker.h"
#include "data.h"

using namespace cpr;
using namespace std;
using json = nlohmann::json;

const int functionalCodeMin = 200;
const int functionalCodeMax = 299;
const string functionalStatus = "Functional.";

// Checks to confirm if the API is online and functional.
bool runApiChecker() {
    Response fetch = Get(Url{ apiUrl });
    json response = json::parse(fetch.text);
    
    // Check the status of the API. We want to return the status of the API which is either
    // 'true' or 'false'
    if (
        (fetch.status_code >= functionalCodeMin && fetch.status_code <= functionalCodeMax)
        && response["status"] == functionalStatus) {
        cout << "API is functional." << endl;
        return true;
    } else {
        cout << "API is not functional." << endl;
        return false;
    }
}