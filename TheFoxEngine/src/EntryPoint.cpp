#include "EntryPoint.h"
#include "framework/Application.h"

int main()
{
    tf::Application *app = GetApplication();
    app->Run();

    delete app;
}