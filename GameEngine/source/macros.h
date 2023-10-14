#pragma once

#include <iostream>
#include <sstream>
#ifdef _WIN32
#include <Windows.h>
#endif

#define GE_VERSION_MAJOR 1
#define GE_VERSION_MINOR 0
#define GE_VERSION_PATCH 0

#define GE_VERSION_STR "Alpha-1.0"

#define DEFAULT_TEXT "Error"

// Print functions will ignored in release build to maximize the performance.
//#ifdef NCONSOLE
// if release:
//#ifdef _WIN32
//#define printError(anything)
//#define printFatalError(anything)\
//{\
//std::stringstream ss;\
//ss << anything;\
//MessageBoxA(NULL, ss.str().c_str(), "Fatal Error", MB_ICONERROR | MB_OK);\
//}
//#define printInfo(anything)
//#define printErrorW(anything)
//#define printFatalErrorW(anything)\
//{\
//std::stringstream ss;\
//ss << anything;\
//MessageBoxA(NULL, ss.str().c_str(), "Fatal Error", MB_ICONERROR | MB_OK);\
//}
//#define printInfoW(anything)
//#else
//#define printError(anything)
//#define printFatalError(anything)
//#define printInfo(anything)
//#define printErrorW(anything)
//#define printFatalErrorW(anything)
//#define printInfoW(anything)
//#endif
//#else
//// if debug:
//#define printError(anything) std::cout << "[ERROR]       " << anything << std::endl
//#define printFatalError(anything) std::cout << "[FATAL-ERROR] " << anything << std::endl;
//#define printInfo(anything) std::cout << "[INFO]        " << anything << std::endl
//#define printErrorW(anything) std::wcout << "[ERROR]       " << anything << std::endl
//#define printFatalErrorW(anything) std::wcout << "[FATAL-ERROR] " << anything << std::endl;
//#define printInfoW(anything) std::wcout << "[INFO]        " << anything << std::endl
//#endif

#ifdef __APPLE__
#define PATH_SDL <SDL2/SDL.h>
#define PATH_SDL_IMAGE <SDL2_image/SDL_image.h>
#define PATH_SDL_TTF <SDL2_ttf/SDL_ttf.h>
#define PATH_SDL_MIXER <SDL2_mixer/SDL_mixer.h>

#define PATH_DEFAULT_FONT "/System/Library/Fonts/Helvetica.ttc"
#elif defined(_WIN32)
#define PATH_SDL <SDL.h>
#define PATH_SDL_IMAGE <SDL_image.h>
#define PATH_SDL_TTF <SDL_ttf.h>
#define PATH_SDL_MIXER <SDL_mixer.h>

#define PATH_DEFAULT_FONT "/Windows/Fonts/arial.ttf"
#else
#error "Unsupported OS"
#endif
