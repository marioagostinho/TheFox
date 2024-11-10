#include <framework/Core.h>
#include "player/Player.h"

#include "level/MainLevel.h"

namespace tf
{
	MainLevel::MainLevel(Application* owningApp)
		: World(owningApp)
	{
	}

	void MainLevel::BeginPlay()
	{
		World::BeginPlay();

		weak<Player> player = SpawnActor<Player>();
		player.lock()->SetActorLocation({ 500.f, 500.f });
	}
}