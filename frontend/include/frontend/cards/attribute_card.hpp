#pragma once

#include <frontend/cards/basic_card.hpp>
#include <nui/event_system/observed_value.hpp>

namespace NuiPage
{
    class AttributeCard : public BasicCard
    {
      private:
        std::string source() const override;
        std::string header() const override;
        std::string description() const override;
        Nui::ElementRenderer render() override;

      private:
        Nui::Observed<std::string> inputText;
    };
}