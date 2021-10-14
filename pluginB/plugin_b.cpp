#include "API.h"

float x = 0;

void FrameCallback(float time)
{
	x += time * 100;

	DrawText("I was made by plugin B", int(x), 20, 20, RED);
}

// plugin b
APP_PLUGIN_CALL bool appStartPlugin()
{
	appApi_AddItem("parrot.png", Vector2{300,300});
	appApi_AddFrameCallback(&FrameCallback);

	return true;
}

APP_PLUGIN_CALL void appEndPlugin()
{
	// Called on cleanup
}