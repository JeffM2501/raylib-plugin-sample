#include "Plugins.h"
#include <windows.h>

#ifdef _WIN32
constexpr const char PluginExtension[] = ".dll";
#include <vector>
std::vector<HMODULE> LoadedPlugins;
#elif defined(__APPLE__)
constexpr const char PluginExtension[] = ".dylib";
# include <dlfcn.h>
std::vector<void*> LoadedPlugins;
#else
constexpr const char PluginExtension[] = ".so";
#  include <dlfcn.h>
std::vector<void*> LoadedPlugins;
#endif


bool IsPlugin(const std::string& extension)
{
	return extension == PluginExtension;
}

void LoadPlugin(const char* filename)
{
#ifdef _WIN32
	try
	{
		HMODULE libHandle = LoadLibrary(filename);

		if (libHandle)
		{
			bool (*init_plugin)(void);

			init_plugin = (bool(__cdecl*)(void))GetProcAddress(libHandle, "appStartPlugin");
			if (init_plugin == nullptr || !init_plugin())
			{
				FreeLibrary(libHandle);
				return;
			}
			LoadedPlugins.push_back(libHandle);
		}
	}
	catch (...)
	{
	}
	
#else
	void* hLib = dlopen(filename, RTLD_LAZY | RTLD_GLOBAL);

	if (hLib)
	{
		bool (*init_plugin)(void);
		*(void**)&init_plugin = dlsym(hLib, "appStartPlugin");
		if (init_plugin == nullptr || !init_plugin())
		{
			dlclose(hLib);
			return;
		}
		LoadedPlugins.push_back(hLib);
	}

#endif
}

void UnloadPlugins()
{
#ifdef _WIN32
	for (HMODULE libHandle : LoadedPlugins)
	{
		void (*shutdown_plugin)(void);
		shutdown_plugin = (void(__cdecl*)(void))GetProcAddress(libHandle, "appEndPlugin");
		if (shutdown_plugin != nullptr)
			shutdown_plugin();

		FreeLibrary(libHandle);
	}

	LoadedPlugins.clear();
#else
	for (void* hLib : LoadedPlugins)
	{
		void (*shutdown_plugin)(void);
		*(void**)&shutdown_plugin = dlsym(hLib, "appEndPlugin");
		if (shutdown_plugin != nullptr)
			shutdown_plugin();

		dlclose(hLib);
	}
	LoadedPlugins.clear();
#endif
}