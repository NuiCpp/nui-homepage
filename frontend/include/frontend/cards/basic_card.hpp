#pragma once

#include <nui/frontend/element_renderer.hpp>

#include <memory>
#include <string>

namespace NuiPage
{
    class BasicCard : public std::enable_shared_from_this<BasicCard>
    {
      public:
        Nui::ElementRenderer operator()() const;

      protected:
        virtual std::string source() const = 0;
        virtual std::string header() const = 0;
        virtual std::string description() const = 0;
        virtual Nui::ElementRenderer render() const = 0;

        static std::string removeIndentation(std::string const& str);
    };
}