#include <framework/Core.h>
#include <framework/Actor.h>
#include <framework/ActorComponent.h>
#include "level/MainLevel.h"

namespace tf
{
	MainLevel::MainLevel(Application* owningApp)
		: World(owningApp)
	{
	}

	void MainLevel::BeginPlay()
	{
		weak<Actor> newActor = SpawnActor<Actor>();
		weak<ActorComponent> newComponent = newActor.lock()->AttachToActor<ActorComponent>();
		newActor.lock()->SetActorLocation({ 500.f, 500.f });
	}
}