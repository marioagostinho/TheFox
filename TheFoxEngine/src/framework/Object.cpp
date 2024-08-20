#include "framework/Object.h"

namespace tf
{
	unsigned int Object::uniqueIDCounter = 0;
	unsigned int Object::GetNextAvaliableID()
	{
		return uniqueIDCounter++;
	}

	Object::Object()
		: m_IsPendingDestroy(false),
		m_UniqueID(GetNextAvaliableID())
	{
	}

	void Object::SetToDestroy()
	{
		onDestroy.Broadcast(this);
		m_IsPendingDestroy = true;
	}
}