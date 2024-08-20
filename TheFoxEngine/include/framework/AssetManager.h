#pragma once

#include <SFML/Graphics.hpp>
#include "framework/Core.h"

namespace tf
{
	class AssetManager
	{
	public:
		static AssetManager& Get();

		void CleanCycle();
		inline void SetAssetRootDirectory(const std::string& path) { }

		shared<sf::Texture> LoadTexture(const std::string& path);

	protected:
		AssetManager();

	private:
		static unique<AssetManager> m_AssetManager;

		template<typename T>
		shared<T> LoadAsset(const std::string& path, dictionary<std::string, shared<T>>& container);
		template<typename T>
		void CleanUniqueReference(dictionary<std::string, shared<T>>& container);

		dictionary<std::string, shared<sf::Texture>> m_LoadedTextureMap;
		std::string m_RootDirectory;
	};

	template<typename T>
	shared<T> AssetManager::LoadAsset(const std::string& path, dictionary<std::string, shared<T>>& container)
	{
		auto found = container.find(path);

		if (found != container.end())
			return found->second;

		shared<T> newAsset(new T);

		if (newAsset->loadFromFile(m_RootDirectory + path))
		{
			container.insert({ path, newAsset });
			return newAsset;
		}

		return shared<T>(nullptr);
	}

	template<typename T>
	void AssetManager::CleanUniqueReference(dictionary<std::string, shared<T>>& container)
	{
		for (auto iter = container.begin(); iter != container.end();)
		{
			if (iter->second.unique())
			{
				iter = container.erase(iter);
			}
			else
			{
				++iter;
			}
		}
	}
}