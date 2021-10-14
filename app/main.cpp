#include "raylib.h"
#include "API.h"
#include "Plugins.h"

#include <vector>
#include <string>

struct Item
{
	Vector2 pos = { 0 };
	Texture2D texture = { 0 };
};

std::vector<Item> Items;

void AddItem(const char* texture, Vector2 pos)
{
	std::string realPath = "../../resources/";
	realPath += texture;

	Items.emplace_back(Item{ pos,LoadTexture(realPath.c_str()) });
}

unsigned int GetItemCount()
{
	return static_cast<unsigned int>(Items.size());
}

// can't be called by the API
void SecretFunction(float x)
{
	DrawText("I was drawn by main", int(x), 780, 20, GREEN);
}

void LoadPlugins()
{
	int count = 0;
	char** files = GetDirectoryFiles("./", &count);
	for (int i = 0; i < count; i++)
	{
		const char* file = files[i];

		const char* ext = GetFileExtension(file);
		if (ext != nullptr && IsPlugin(ext))
			LoadPlugin(file);
	}
}

int main(int argc, char* argv[])
{
	SetConfigFlags(FLAG_VSYNC_HINT);
	InitWindow(1280, 800, "Plugin Test");

	SetTargetFPS(144);
	LoadPlugins();

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(RAYWHITE);

		for (Item& item : Items)
		{
			DrawTexture(item.texture, int(item.pos.x), int(item.pos.y), WHITE);
		}

		CallAPIFrameCallbacks(GetFrameTime());
		SecretFunction(0);
		DrawFPS(0, 0);
		EndDrawing();
	}

	UnloadPlugins();
	CloseWindow();

	return 0;
}