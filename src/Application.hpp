#pragma once

class Application
{
public:
    Application();
    Application(const Application&) = delete;
    ~Application();

    Application& operator=(const Application&) = delete;

    static Application& getApplication();

    void run();

private:
    static Application* s_singleton;
};
