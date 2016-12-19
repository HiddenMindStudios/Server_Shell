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
#include <vector>

#ifdef STRUCTURE_EXPORTS
#	define STRUCTURE_API __declspec(dllexport)
#else
#	define STRUCTURE_API __declspec(dllimport)
#endif

typedef std::vector<std::string> vstring;