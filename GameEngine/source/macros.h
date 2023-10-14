#pragma once

#define GE_VERSION_MAJOR 1
#define GE_VERSION_MINOR 0
#define GE_VERSION_PATCH 0

#define GE_VERSION_STR "Alpha-1.0"

#define DEFAULT_TEXT "Error"

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
