#include <framework/AssetManager.h>

#include "config.h"
#include "level/MainLevel.h"
#include "gameFramework/GameApplication.h"

namespace
{
    const std::string APP_TITLE = "The Fox";
    const sf::Vector2f APP_RESOLUTION = { 1366, 768 };
    const float TARGET_FRAME_RATE = 60.f;
}

tf::Application* GetApplication()
{
    return new tf::GameApplication();
}

namespace tf
{
    GameApplication::GameApplication()
        : Application(APP_RESOLUTION.x, 
            APP_RESOLUTION.y, 
            APP_TITLE, 
            sf::Style::Titlebar || sf::Style::Close,
            TARGET_FRAME_RATE)
    {
        AssetManager::Get().SetAssetRootDirectory(GetResourceDir());
        weak<MainLevel> newWorld = LoadWorld<MainLevel>();
    }
}