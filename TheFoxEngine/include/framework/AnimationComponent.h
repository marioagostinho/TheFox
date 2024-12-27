#pragma once

#include <string>
#include "framework/ActorComponent.h"

namespace tf
{
	class Animation;

	class AnimationComponent : public ActorComponent
	{
	public:
		AnimationComponent(Actor* owningActor, map<std::string, shared<Animation>> animations = map<std::string, shared<Animation>>());

		virtual void Tick(float deltaTime) override;

		void PlayAnimationByName(const std::string& name);
		const std::string GetCurrentAnimationName();

	protected:
		map<std::string, shared<Animation>> m_Animations;

	private:
		shared<Animation> m_CurrentAnimation;
	};
}