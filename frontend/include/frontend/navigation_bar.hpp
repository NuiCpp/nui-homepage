#pragma once

#include <nui/frontend/element_renderer.hpp>

#include <memory>

namespace NuiPage
{
    class NavigationBar
    {
      public:
        NavigationBar();
        ~NavigationBar();
        NavigationBar(const NavigationBar&) = delete;
        NavigationBar& operator=(const NavigationBar&) = delete;
        NavigationBar(NavigationBar&&);
        NavigationBar& operator=(NavigationBar&&);

        Nui::ElementRenderer operator()();

      private:
        struct Implementation;
        std::unique_ptr<Implementation> impl_;
    };
}