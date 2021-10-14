#pragma once

#include <string>

void LoadPlugin(const char* filename);
void UnloadPlugins();

void CallAPIFrameCallbacks(float time);

bool IsPlugin(const std::string& extension);