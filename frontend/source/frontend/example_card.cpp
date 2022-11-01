#include <frontend/example_card.hpp>

#include <nui/frontend/attributes.hpp>
#include <nui/frontend/elements.hpp>

namespace NuiPage
{
    // #####################################################################################################################
    struct ExampleCard::Implementation
    {};
    //---------------------------------------------------------------------------------------------------------------------
    ExampleCard::ExampleCard()
        : impl_(std::make_unique<Implementation>())
    {}
    //---------------------------------------------------------------------------------------------------------------------
    ExampleCard::~ExampleCard() = default;
    //---------------------------------------------------------------------------------------------------------------------
    ExampleCard::ExampleCard(ExampleCard&&) = default;
    //---------------------------------------------------------------------------------------------------------------------
    ExampleCard& ExampleCard::operator=(ExampleCard&&) = default;
    //---------------------------------------------------------------------------------------------------------------------
    Nui::ElementRenderer ExampleCard::operator()()
    {
        using namespace Nui;
        using namespace Nui::Elements;
        using namespace Nui::Attributes;
        using Nui::Elements::div; // because of the global div.

        // clang-format off
        return div{}(
            "ExampleCard"
        );
        // clang-format on
    }
    //---------------------------------------------------------------------------------------------------------------------
    // #####################################################################################################################
}