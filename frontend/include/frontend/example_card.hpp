#pragma once

#include <nui/frontend/generator_typedefs.hpp>

#include <memory>

namespace NuiPage
{
    class ExampleCard
    {
      public:
        ExampleCard();
        ~ExampleCard();
        ExampleCard(const ExampleCard&) = delete;
        ExampleCard& operator=(const ExampleCard&) = delete;
        ExampleCard(ExampleCard&&);
        ExampleCard& operator=(ExampleCard&&);

        Nui::ElementRenderer operator()();

      private:
        struct Implementation;
        std::unique_ptr<Implementation> impl_;
    };
}