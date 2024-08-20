#include <framework/Core.h>
#include <framework/Actor.h>
#include "level/MainLevel.h"

namespace tf
{
	MainLevel::MainLevel(Application* owningApp)
		: World(owningApp)
	{
	}

	void MainLevel::BeginPlay()
	{
		weak<Actor> newActor = SpawnActor<Actor>("fox.png");
		newActor.lock()->SetActorLocation({ 500.f, 500.f });
	}
}