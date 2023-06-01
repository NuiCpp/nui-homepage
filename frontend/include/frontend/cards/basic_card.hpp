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

        template <class Derived>
        std::shared_ptr<Derived const> shared_from_base() const
        {
            return std::static_pointer_cast<Derived const>(shared_from_this());
        }
        template <class Derived>
        std::weak_ptr<Derived const> weak_from_base() const
        {
            return std::weak_ptr<Derived const>(shared_from_base<Derived>());
        }
        template <class Derived>
        std::shared_ptr<Derived> shared_from_base()
        {
            return std::static_pointer_cast<Derived>(shared_from_this());
        }
        template <class Derived>
        std::weak_ptr<Derived> weak_from_base()
        {
            return std::weak_ptr<Derived>(shared_from_base<Derived>());
        }

      protected:
        virtual std::string source() const = 0;
        virtual std::string header() const = 0;
        virtual std::string description() const = 0;
        virtual Nui::ElementRenderer render() const = 0;

        static std::string removeIndentation(std::string const& str);
    };
}