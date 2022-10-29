#pragma once

#include <nui/frontend/generator_typedefs.hpp>

#include <memory>

namespace NuiPage
{
    class MainPage
    {
      public:
        MainPage();
        ~MainPage();
        MainPage(const MainPage&) = delete;
        MainPage& operator=(const MainPage&) = delete;
        MainPage(MainPage&&);
        MainPage& operator=(MainPage&&);

        Nui::ElementRenderer render();

      private:
        struct Implementation;
        std::unique_ptr<Implementation> impl_;
    };
}