#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "redirectLogs.h"

FILE* file = NULL;
const char* filename = "log.txt";
const char* mode = "w";

bool redirectLogs() {
    errno_t err = freopen_s(&file, filename, mode, stdout);

    if (err == 0) {
        return true;
    }
    else {
        return false;
    }
}

void stopRedirectingLogs() {
    fclose(file);
}