#pragma once

#include <nui/frontend/generator_typedefs.hpp>

#include <memory>

namespace NuiPage
{
    class MainContent
    {
      public:
        MainContent();
        ~MainContent();
        MainContent(const MainContent&) = delete;
        MainContent& operator=(const MainContent&) = delete;
        MainContent(MainContent&&);
        MainContent& operator=(MainContent&&);

        Nui::ElementRenderer operator()();

      private:
        struct Implementation;
        std::unique_ptr<Implementation> impl_;
    };
}