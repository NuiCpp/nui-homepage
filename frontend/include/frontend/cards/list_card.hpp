#pragma once

#include <frontend/cards/basic_card.hpp>

#include <nui/frontend/generator_typedefs.hpp>

#include <memory>

namespace NuiPage
{
    class ListCard : public BasicCard
    {
      public:
        ListCard();
        ~ListCard();
        ListCard(const ListCard&) = delete;
        ListCard& operator=(const ListCard&) = delete;
        ListCard(ListCard&&);
        ListCard& operator=(ListCard&&);

      private:
        struct Implementation;
        std::unique_ptr<Implementation> impl_;

        std::string source() const override;
        std::string header() const override;
        std::string description() const override;
        Nui::ElementRenderer render() const override;
    };
}