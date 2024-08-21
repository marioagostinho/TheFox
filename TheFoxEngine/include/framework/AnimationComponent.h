#pragma once

#include <string>
#include "framework/ActorComponent.h"

namespace tf
{
	class Animation;

	class AnimationComponent : public ActorComponent
	{
	public:
		AnimationComponent(Actor* owningActor, 
			map<std::string, shared<Animation>> animations);

		virtual void Tick(float deltaTime) override;

		void PlayAnimation(const std::string& name);

	private:
		map<std::string, shared<Animation>> m_Animations;
		shared<Animation> m_CurrentAnimation;
	};
}