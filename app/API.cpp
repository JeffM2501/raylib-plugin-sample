#include "API.h"

#include <vector>
#include <algorithm>

std::vector<appApi_FrameCallback> FrameCallbacks;

extern void AddItem(const char* texture, Vector2 pos);
extern unsigned int GetItemCount();

APP_API const char* appApi_GetResourceDir()
{
	return "../../";
}

// add an item to the drawing
APP_API void appApi_AddItem(const char* texture, Vector2 pos)
{
	AddItem(texture, pos);
}

APP_API unsigned int appApi_GetItemCount()
{
	return GetItemCount();
}

APP_API void appApi_AddFrameCallback(appApi_FrameCallback callback)
{
	FrameCallbacks.push_back(callback);
}

void CallAPIFrameCallbacks(float time)
{
	for (appApi_FrameCallback cb : FrameCallbacks)
	{
		cb(time);
	}
}