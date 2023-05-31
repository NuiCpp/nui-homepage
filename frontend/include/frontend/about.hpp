#pragma once

#include <nui/frontend/element_renderer.hpp>

namespace NuiPage
{
    class AboutPage
    {
      public:
        AboutPage();
        ~AboutPage();
        AboutPage(const AboutPage&) = delete;
        AboutPage& operator=(const AboutPage&) = delete;
        AboutPage(AboutPage&&);
        AboutPage& operator=(AboutPage&&);

        Nui::ElementRenderer operator()();

      private:
        struct Implementation;
        std::unique_ptr<Implementation> impl_;
    };
}