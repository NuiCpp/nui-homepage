#pragma once

#include <frontend/basic_card.hpp>

#include <nui/frontend/generator_typedefs.hpp>

#include <memory>

namespace NuiPage
{
    class SimpleReactiveCard : public BasicCard
    {
      public:
        SimpleReactiveCard();
        ~SimpleReactiveCard();
        SimpleReactiveCard(const SimpleReactiveCard&) = delete;
        SimpleReactiveCard& operator=(const SimpleReactiveCard&) = delete;
        SimpleReactiveCard(SimpleReactiveCard&&);
        SimpleReactiveCard& operator=(SimpleReactiveCard&&);

      private:
        struct Implementation;
        std::unique_ptr<Implementation> impl_;

        std::string source() const override;
        std::string header() const override;
        std::string description() const override;
        Nui::ElementRenderer render() const override;
    };
}