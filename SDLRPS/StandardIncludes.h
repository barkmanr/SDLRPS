#ifndef STANDARD_INCLUDES_H
#define STANDARD_INCLUDES_H

#define SDL_MAIN_HANDLED

#define NATIVE_XRES 1920
#define NATIVE_YRES 1080

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <cinttypes>
#include <stdio.h>
#include <thread>
#include <map>
#include <SDL.h>
#include <sstream>
#include <SDL_pixels.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <algorithm>
#include <glm/glm.hpp>


#include "Singleton.h"
#include "BasicStructs.h"
using namespace std;


#ifdef _WIN32

#include <Windows.h>
#include <direct.h>
#define M_ASSERT(_cond, _msg) \
	if (!(_cond)) {OutputDebugStringA(_msg); abort();}
#define GetCurrentDir _getcwd

#else
#include <unistd.h>
#define GetCurrentDir getcwd

#endif

#endif STANDARD_INCLUDES_H


