#include "framework/Core.h"
#include "framework/World.h"
#include "framework/AssetManager.h"
#include "framework/Application.h"

namespace tf
{
    Application::Application(unsigned int windowWidth, 
        unsigned int windowHeight, 
        const std::string& title, 
        sf::Uint32 style,
        float targetFrameRate)
        : m_Window(sf::VideoMode(windowWidth, windowHeight), title, style),
        m_TargetFrameRate(targetFrameRate),
        m_TickClock(),
        m_CurrentWorld(nullptr),
        m_CleanCycleClock(),
        m_CleanCycleInterval(2.f)
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

            // Frames
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
        // Tick
        Tick(deltaTime);

        if (m_CurrentWorld)
        {
            m_CurrentWorld->TickInternal(deltaTime);
        }

        // Clean cycle
        if (m_CleanCycleClock.getElapsedTime().asSeconds() >= m_CleanCycleInterval)
        {
            m_CleanCycleClock.restart();
            AssetManager::Get().CleanCycle();

            if (m_CurrentWorld)
            {
                m_CurrentWorld->CleanCycle();
            }
        }

        if (m_PendingWorld)
        {
            m_CurrentWorld = m_PendingWorld;
            m_CurrentWorld->BeginPlayInternal();
            m_PendingWorld = nullptr;
        }
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
        if (m_CurrentWorld)
        {
            m_CurrentWorld->Render(m_Window);
        }
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