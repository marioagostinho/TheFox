#pragma once

#include <framework/World.h>

namespace tf
{
	class MainLevel : public World
	{
	public:
		MainLevel(Application* owningApp);

		virtual void BeginPlay() override;
	};
}