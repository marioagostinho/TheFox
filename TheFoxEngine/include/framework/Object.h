#pragma once

#include "framework/Core.h"
#include "framework/Delegate.hpp"

namespace tf
{
	class Object : public std::enable_shared_from_this<Object>
	{
	public:
		Object();

		inline bool IsPendingDestroy() const { return m_IsPendingDestroy; }
		inline unsigned int GetUniqueID() const { return m_UniqueID; }

		virtual void SetToDestroy();

		inline weak<Object> GetWeakRef() { return weak_from_this(); }
		inline weak<const Object> GetWeakRef() const { return weak_from_this(); };

		Delegate<Object*> onDestroy;

	private:
		bool m_IsPendingDestroy;
		unsigned int m_UniqueID;

		static unsigned int uniqueIDCounter;
		static unsigned int GetNextAvaliableID();
	};
}