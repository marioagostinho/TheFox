add_library(${THE_FOX_ENGINE_TARGET_NAME} STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include/EntryPoint.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/EntryPoint.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/include/framework/Application.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/framework/Application.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/include/framework/Core.h

    ${CMAKE_CURRENT_SOURCE_DIR}/include/framework/Math.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/framework/Math.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/include/framework/Delegate.hpp

    ${CMAKE_CURRENT_SOURCE_DIR}/include/framework/AssetManager.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/framework/AssetManager.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/include/framework/InputManager.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/framework/InputManager.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/include/framework/Object.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/framework/Object.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/include/framework/World.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/framework/World.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/include/framework/Actor.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/framework/Actor.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/include/framework/Character.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/framework/Character.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/include/framework/ActorComponent.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/framework/ActorComponent.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/include/framework/Animation.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/framework/Animation.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/include/framework/AnimationComponent.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/framework/AnimationComponent.cpp
)

target_include_directories(${THE_FOX_ENGINE_TARGET_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include/
)

include(FetchContent)

# SFML
set(SFML_LIB_NAME SFML)

FetchContent_Declare(
    ${SFML_LIB_NAME}
    GIT_REPOSITORY https://github.com/SFML/SFML
    GIT_TAG 2.5.1
    GIT_SHALLOW FALSE
)

FetchContent_MakeAvailable(${SFML_LIB_NAME})

target_link_libraries(${THE_FOX_ENGINE_TARGET_NAME} PUBLIC sfml-graphics)
target_link_libraries(${THE_FOX_ENGINE_TARGET_NAME} PUBLIC sfml-window)
target_link_libraries(${THE_FOX_ENGINE_TARGET_NAME} PUBLIC sfml-system)
target_link_libraries(${THE_FOX_ENGINE_TARGET_NAME} PUBLIC sfml-audio)

function(CopyLibToTarget LIB_NAME TARGET_NAME)
	add_custom_command(TARGET ${TARGET_NAME}
	POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_if_different
	$<TARGET_FILE:${LIB_NAME}>
	$<TARGET_FILE_DIR:${TARGET_NAME}>
	)
endfunction()

CopyLibToTarget(sfml-graphics ${THE_FOX_ENGINE_TARGET_NAME})
CopyLibToTarget(sfml-window ${THE_FOX_ENGINE_TARGET_NAME})
CopyLibToTarget(sfml-system ${THE_FOX_ENGINE_TARGET_NAME})
CopyLibToTarget(sfml-audio ${THE_FOX_ENGINE_TARGET_NAME})