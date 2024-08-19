#pragma once

#include <SFML/Graphics.hpp>

namespace tf
{
    class Application
    {
    public:
        Application(unsigned int windowWidth, unsigned int windowHeight, const std::string& title, sf::Uint32 style);
        void Run();


        inline sf::Vector2u GetWindowSize() const { return m_Window.getSize(); };
        inline sf::RenderWindow& GetWindow() { return m_Window; }

        virtual void Tick(float deltaTime);
        virtual void Render();
        void QuitApplication();

    private:
        void TickInternal(float deltaTime);
        void RenderInternal();
        bool DispatchEvent(const sf::Event& event);

        // Window
        sf::RenderWindow m_Window;

        // Frames
        float m_TargetFrameRate;
        sf::Clock m_TickClock;
    };
}