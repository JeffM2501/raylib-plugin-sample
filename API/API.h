#pragma once

#include "raylib.h"

#ifdef _WIN32
#ifdef INSIDE_APP
	// if we are inside the app, we want to export this function
#define APP_API __declspec( dllexport )
#else
	// if we are not inside the app (thus in a plug-in) we want to import this function
#define APP_API __declspec( dllimport )
#endif
// ensure that entry points are not name mangled
#define APP_PLUGIN_CALL extern "C" __declspec( dllexport )

#else
#ifdef __clang__
#define APP_API __attribute__((visibility("default")))
#define APP_PLUGIN_CALL extern "C" __attribute__((visibility("default")))
#else
#define APP_API
#define APP_PLUGIN_CALL extern "C"
#endif
#endif

// entry and exit function names

typedef void (*appApi_FrameCallback)(float frameTime);

// add an item to the drawing
APP_API void appApi_AddItem(const char* texture, Vector2 pos);

APP_API const char* appApi_GetResourceDir();

APP_API unsigned int appApi_GetItemCount();

APP_API void appApi_AddFrameCallback(appApi_FrameCallback callback);