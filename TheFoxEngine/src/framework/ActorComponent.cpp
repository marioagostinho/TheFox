#include "framework/Actor.h"
#include "framework/ActorComponent.h"

namespace tf
{
	ActorComponent::ActorComponent(Actor *owningActor)
		: m_OwningActor(owningActor),
		  m_BeganPlay(false),
		  m_TickEnabled(true)
	{
	}

	void ActorComponent::BeginPlayInternal()
	{
		if (!m_BeganPlay)
		{
			m_BeganPlay = true;
			BeginPlay();
		}
	}

	void ActorComponent::BeginPlay()
	{
	}

	void ActorComponent::TickInternal(float deltaTime)
	{
		if (!IsPendingDestroy() && m_TickEnabled)
		{
			Tick(deltaTime);
		}
	}

	void ActorComponent::Tick(float deltaTime)
	{
	}
}