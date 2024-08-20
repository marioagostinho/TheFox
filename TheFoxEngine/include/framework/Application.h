#pragma once

#include <SFML/Graphics.hpp>
#include "framework/Core.h"

namespace tf
{
    class World;

    class Application
    {
    public:
        Application(unsigned int windowWidth, 
            unsigned int windowHeight, 
            const std::string& title, 
            sf::Uint32 style,
            float targetFrameRate = 60.f);
        
        void Run();
        void QuitApplication();
        virtual void Tick(float deltaTime);
        virtual void Render();

        template<typename T>
        weak<T> LoadWorld();

        inline sf::Vector2u GetWindowSize() const { return m_Window.getSize(); };
        inline sf::RenderWindow& GetWindow() { return m_Window; }

    private:
        void TickInternal(float deltaTime);
        void RenderInternal();
        bool DispatchEvent(const sf::Event& event);

        // Window
        sf::RenderWindow m_Window;

        // Frames
        float m_TargetFrameRate;
        sf::Clock m_TickClock;

        // World
        shared<World> m_CurrentWorld;
        shared<World> m_PendingWorld;

        // Cleaning cycle
        sf::Clock m_CleanCycleClock;
        float m_CleanCycleInterval;
    };

    template<typename T>
    weak<T> Application::LoadWorld()
    {
        shared<T> newWorld(new T(this));
        m_PendingWorld = newWorld;
        return newWorld;
    }
}