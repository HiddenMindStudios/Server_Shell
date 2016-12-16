#pragma once
#include "stdafx.h"
#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>
#include <string>
#include <exception>

#include <sstream>
#include <time.h>
#include <stdio.h>
#include <errno.h>
#include <signal.h>
#include <assert.h>

#ifdef CONTROL_EXPORTS
#	define CONTROL_API __declspec(dllexport)
#else
#	define CONTROL_API __declspec(dllimport)
#endif

typedef unsigned int uint32;
