#pragma once

#include "framework/Object.h"

namespace tf
{
	class Actor;

	class ActorComponent : public Object
	{
	public:
		ActorComponent(Actor* owningActor);

		void BeginPlayInternal();
		virtual void BeginPlay();

		void TickInternal(float deltaTime);
		virtual void Tick(float deltaTime);

		inline const bool IsTickEnabled() const { return m_TickEnabled; }
		inline void SetTickEnabled(bool ticking) { m_TickEnabled = ticking; }

		inline Actor* GetActor() { return m_OwningActor; }
		inline const Actor* GetActor() const { return m_OwningActor; }

	private:
		Actor* m_OwningActor;
		bool m_BeganPlay;
		bool m_TickEnabled;
	};
}