#pragma once

#include <nui/frontend/element_renderer.hpp>

#include <memory>

namespace NuiPage
{
    class PageFrame
    {
      public:
        PageFrame();
        ~PageFrame();
        PageFrame(const PageFrame&) = delete;
        PageFrame& operator=(const PageFrame&) = delete;
        PageFrame(PageFrame&&);
        PageFrame& operator=(PageFrame&&);

        Nui::ElementRenderer render();

      private:
        struct Implementation;
        std::unique_ptr<Implementation> impl_;
    };
}