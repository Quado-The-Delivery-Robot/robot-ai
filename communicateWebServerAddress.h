#pragma once

#ifndef HEADER_STARTUP_COMMUNICATEWEBSERVERADDRESS
#define HEADER_STARTUP_COMMUNICATEWEBSERVERADDRESS

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstdio>
#include <atomic>

#ifdef _WIN32
#include <windows.h>
#else
#include <sys/types.h>
#include <unistd.h>
#endif

using namespace std;

void startNgrok();

void stopNgrok();

#endif