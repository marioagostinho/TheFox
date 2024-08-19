#include "config.h"
#include "gameFramework/GameApplication.h"

tf::Application* GetApplication()
{
    return new tf::GameApplication();
}

namespace tf
{
    GameApplication::GameApplication()
        : Application(1366, 768, "The Fox", sf::Style::Titlebar || sf::Style::Close)
    {
    }
}