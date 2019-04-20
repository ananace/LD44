#include "Application.hpp"

Application* Application::s_singleton = nullptr;

Application::Application()
{
    s_singleton = this;
}

Application::~Application()
{
    if (s_singleton == this)
        s_singleton = nullptr;
}

Application& Application::getApplication()
{
    return *s_singleton;
}

void Application::run()
{
}
