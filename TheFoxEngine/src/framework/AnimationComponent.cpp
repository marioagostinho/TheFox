#include "framework/Animation.h"
#include "framework/Actor.h"
#include "framework/AnimationComponent.h"

namespace tf
{
	AnimationComponent::AnimationComponent(Actor* owningActor, 
		map<std::string, shared<Animation>> animations)
		: ActorComponent(owningActor),
		m_Animations(animations),
		m_CurrentAnimation()
	{
	}

	void AnimationComponent::Tick(float deltaTime)
	{
		if (m_CurrentAnimation != nullptr)
		{
			m_CurrentAnimation->PlayAnimation(deltaTime);
		}
	}

	void AnimationComponent::PlayAnimation(const std::string& name)
	{
		if (m_Animations.empty() || m_CurrentAnimation == m_Animations[name])
			return;

		m_CurrentAnimation = m_Animations[name];
		m_CurrentAnimation->StopAnimation();
		m_CurrentAnimation->SetSprite(GetActor()->GetSprite());
	}
}