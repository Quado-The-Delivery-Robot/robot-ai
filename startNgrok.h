#pragma once

#ifndef HEADER_STARTUP_STARTNGROK
#define HEADER_STARTUP_STARTNGROK

#include <iostream>
#include <string>
#include <cstdio>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>

using namespace cpr;
using namespace std;
using json = nlohmann::json;

FILE* startNgrok();

void stopNgrok(FILE* ngrokProcess);

#endif