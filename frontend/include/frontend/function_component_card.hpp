#pragma once

#include "basic_card.hpp"

namespace NuiPage
{
    class FunctionComponentCard : public BasicCard
    {
      private:
        std::string source() const override;
        std::string header() const override;
        std::string description() const override;
        Nui::ElementRenderer render() const override;
    };
}