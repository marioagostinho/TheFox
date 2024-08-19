cmake_minimum_required(VERSION 3.28.0)

project(
	TheFox
	VERSION 1.0.0
	LANGUAGES C CXX
)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(THE_FOX_ENGINE_TARGET_NAME TheFoxEngine)
set(THE_FOX_GAME_TARGET_NAME TheFoxGame)

add_subdirectory(TheFoxEngine)
add_subdirectory(TheFoxGame)