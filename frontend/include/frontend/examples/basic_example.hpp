#pragma once

#include <nui/frontend/element_renderer.hpp>
#include <nui/event_system/observed_value.hpp>

#include <string>

namespace NuiPage
{
    class BasicExample
    {
      public:
        Nui::ElementRenderer operator()();
        BasicExample() = default;
        virtual ~BasicExample() = default;
        BasicExample(const BasicExample&) = delete;
        BasicExample& operator=(const BasicExample&) = delete;
        BasicExample(BasicExample&&) = default;
        BasicExample& operator=(BasicExample&&) = default;

      public:
        virtual std::string heading() const = 0;
        virtual std::string explanation() const;

      protected:
        virtual std::string editorContentHeader() const = 0;
        virtual std::string editorContentSource() const = 0;
        virtual Nui::ElementRenderer render() = 0;

      private:
        static bool isMobile();
        static std::string preconditionContent(std::string content);

        Nui::Observed<int> activeTab_{1};
    };
}
