#include "framework/Application.h"

namespace tf
{
    Application::Application(unsigned int windowWidth, 
        unsigned int windowHeight, 
        const std::string& title, 
        sf::Uint32 style)
        : m_Window(sf::VideoMode(windowWidth, windowHeight), title, style),
        m_TargetFrameRate(60.f),
        m_TickClock()
    {
    }

    void Application::Run()
    {
        m_TickClock.restart();

        float accumulatedTime = 0.f;
        float targetDeltaTime = 1.f / m_TargetFrameRate;

        while (m_Window.isOpen())
        {
            // Window
            sf::Event windowEvent;

            while (m_Window.pollEvent(windowEvent))
            {
                if (windowEvent.type == sf::Event::EventType::Closed)
                {
                    QuitApplication();
                }
                else
                {
                    DispatchEvent(windowEvent);
                }
            }

            // Franes
            float frameDeltaTime = m_TickClock.restart().asSeconds();
            accumulatedTime += frameDeltaTime;

            while (accumulatedTime > targetDeltaTime)
            {
                accumulatedTime -= targetDeltaTime;

                TickInternal(targetDeltaTime);
                RenderInternal();
            }
        }
    }

    void Application::TickInternal(float deltaTime)
    {
        Tick(deltaTime);
    }

    void Application::Tick(float deltaTime)
    {
    }

    void Application::RenderInternal()
    {
        m_Window.clear();
        Render();
        m_Window.display();
    }

    void Application::Render()
    {
    }

    bool Application::DispatchEvent(const sf::Event& event)
    {
        return false;
    }

    void Application::QuitApplication()
    {
        m_Window.close();
    }
}