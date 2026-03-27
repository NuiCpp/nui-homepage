#pragma once

#include <nui/frontend/element_renderer.hpp>

#include <memory>

namespace NuiPage
{
    class ExamplePage
    {
      public:
        ExamplePage();
        ~ExamplePage();
        ExamplePage(const ExamplePage&) = delete;
        ExamplePage& operator=(const ExamplePage&) = delete;
        ExamplePage(ExamplePage&&);
        ExamplePage& operator=(ExamplePage&&);

        Nui::ElementRenderer operator()();

      private:
        Nui::ElementRenderer renderPage(int page);

      private:
        struct Implementation;
        std::unique_ptr<Implementation> impl_;
    };
}