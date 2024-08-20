#pragma once

#include <functional>
#include "framework/Core.h"

namespace tf
{
	class Object;

	template<typename... Args>
	class Delegate
	{
	public:
		template<typename ClassName>
		void BindAction(weak<Object> obj, void(ClassName::* callback)(Args...))
		{
			std::function<bool(Args...)> callbackFun = [obj, callback](Args... args)->bool
			{
				if (!obj.expired())
				{
					(static_cast<ClassName*>(obj.lock().get())->*callback)(args...);
					return true;
				}
				return false;
			}
		}

		void Broadcast(Args... args)
		{
			for (auto iter = m_Callbacks.begin(); iter != m_Callbacks.end();)
			{
				if ((*iter)(args...))
				{
					++iter;
				}
				else
				{
					iter = m_Callbacks.erase(iter);
				}
			}
		}

	private:
		list<std::function<bool(Args...)>> m_Callbacks;
	};
}