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
    Nui::ElementRenderer SimpleReactiveCard::operator()()
    {
        using namespace Nui;
        using namespace Nui::Elements;
        using namespace Nui::Attributes;
        using Nui::Elements::span;
        using Nui::Elements::div; // because of the global div.

        thread_local Observed<int> counter = 0;

        // clang-format off
        return div{
            class_ = "card"
        }(
            // source
            div{
                class_ = "card-source"
            }(
                ""
            ),
            // what the source generates
            div{
                class_ = "card-content",
                id = "simpleReactiveCardContent"
            }(
                button{
                    onClick = []{ ++counter; },
                    class_ = "btn btn-primary"
                }("Increment Counter"),
                button{
                    onClick = []{ counter = 0; },
                    class_ = "btn btn-primary"
                }("Clear Counter"),
                div{}(
                    span{}("Counter: "), 
                    span{}(counter)
                )
            )
        );
        // clang-format on
    }
    //---------------------------------------------------------------------------------------------------------------------
    // #####################################################################################################################
}