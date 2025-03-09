#pragma once

#ifdef __unix__ 
#define OS_Windows 0
#include <unistd.h>

#elif defined(_WIN32) || defined(WIN32)
#define OS_Windows 1
#include <io.h>
#include <process.h>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")  // ³sµ² Winsock ¨ç¦¡®w
#endif

#include <iostream>
#include "modbus.h"
#include "settxt.h"

using namespace std;

modbus_t* ctx;
modbus_mapping_t* mb_mapping;

string deviceRTU;
string slaveID;

