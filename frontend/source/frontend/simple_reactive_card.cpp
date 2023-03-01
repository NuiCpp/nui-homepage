#include <frontend/simple_reactive_card.hpp>

#include <nui/frontend/attributes.hpp>
#include <nui/frontend/elements.hpp>

namespace NuiPage
{
    // #####################################################################################################################
    struct SimpleReactiveCard::Implementation
    {};
    //---------------------------------------------------------------------------------------------------------------------
    SimpleReactiveCard::SimpleReactiveCard()
        : impl_(std::make_unique<Implementation>())
    {}
    //---------------------------------------------------------------------------------------------------------------------
    SimpleReactiveCard::~SimpleReactiveCard() = default;
    //---------------------------------------------------------------------------------------------------------------------
    SimpleReactiveCard::SimpleReactiveCard(SimpleReactiveCard&&) = default;
    //---------------------------------------------------------------------------------------------------------------------
    SimpleReactiveCard& SimpleReactiveCard::operator=(SimpleReactiveCard&&) = default;
    //---------------------------------------------------------------------------------------------------------------------
    std::string SimpleReactiveCard::source() const
    {
        return removeIndentation(R"(
            thread_local Observed<int> counter = 0;

            div{}(
                button{
                    onClick = []{ ++counter; }
                }("Increment"),
                button{
                    onClick = []{ counter = 0; }
                }("Clear"),
                div{}(
                    span{}("Counter: "), 
                    span{}(counter)
                )
            )
        )");
    }
    //---------------------------------------------------------------------------------------------------------------------
    std::string SimpleReactiveCard::header() const
    {
        return "View Updates Reactively";
    }
    //---------------------------------------------------------------------------------------------------------------------
    std::string SimpleReactiveCard::description() const
    {
        return "The Nui library allows you to create reactive views."
               "This means that when the data changes, the view will automatically update."
               "This is done by using the Observed class."
               "The Observed class is a wrapper around a value that allows you to observe changes to the value.";
    }
    //---------------------------------------------------------------------------------------------------------------------
    Nui::ElementRenderer SimpleReactiveCard::render() const
    {
        using namespace Nui;
        using namespace Nui::Elements;
        using namespace Nui::Attributes;
        using Nui::Elements::span;
        using Nui::Elements::div; // because of the global div.

        std::shared_ptr<Observed<int>> counter = std::make_shared<Observed<int>>(0);

        // clang-format off
        return fragment(
            button{
                onClick = [counter]{ ++*counter; },
                class_ = "btn btn-primary"
            }("Increment"),
            button{
                onClick = [counter]{ *counter = 0; },
                class_ = "btn btn-primary"
            }("Clear"),
            div{}(
                span{}("Counter: "), 
                span{}(*counter)
            )
        );
        // clang-format on
    }
    // #####################################################################################################################
}