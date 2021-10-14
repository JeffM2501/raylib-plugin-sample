#include "API.h"

// plugin A
APP_PLUGIN_CALL bool appStartPlugin()
{
	appApi_AddItem("monkey.png", Vector2{10,100});
	return true;
}

APP_PLUGIN_CALL void appEndPlugin()
{
	// Called on cleanup
}