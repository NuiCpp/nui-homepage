#pragma once

#include <frontend/cards/basic_card.hpp>

#include <memory>

namespace NuiPage
{
    class ConditionalRenderingCard : public BasicCard
    {
      public:
        ConditionalRenderingCard();
        ~ConditionalRenderingCard();
        ConditionalRenderingCard(ConditionalRenderingCard const&) = delete;
        ConditionalRenderingCard& operator=(ConditionalRenderingCard const&) = delete;
        ConditionalRenderingCard(ConditionalRenderingCard&&);
        ConditionalRenderingCard& operator=(ConditionalRenderingCard&&);

      private:
        std::string source() const override;
        std::string header() const override;
        std::string description() const override;
        Nui::ElementRenderer render() const override;

      private:
        struct Implementation;
        std::unique_ptr<Implementation> impl_;
    };
}