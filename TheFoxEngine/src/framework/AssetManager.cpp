#include "framework/AssetManager.h"

namespace tf
{
	unique<AssetManager> AssetManager::m_AssetManager(nullptr);

	AssetManager::AssetManager()
		: m_RootDirectory()
	{
	}

	AssetManager& AssetManager::Get()
	{
		if (!m_AssetManager)
			m_AssetManager = unique<AssetManager>(new AssetManager);

		return *m_AssetManager;
	}

	void AssetManager::CleanCycle()
	{
		CleanUniqueReference(m_LoadedTextureMap);
	}

	shared<sf::Texture> AssetManager::LoadTexture(const std::string& path)
	{
		return LoadAsset(path, m_LoadedTextureMap);
	}


}