#pragma once

#include <string>

std::string GetResourceDir()
{
#ifdef NDEBUG //release build
	return "assets/";
#else
	return "C:/Users/mario/Desktop/cpp/TheFox/TheFoxGame/assets/";
#endif
}
