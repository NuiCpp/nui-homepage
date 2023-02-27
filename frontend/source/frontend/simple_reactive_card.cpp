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

        std::shared_ptr<Observed<int>> counter = std::make_shared<Observed<int>>(0);

        // clang-format off
        return div{
            class_ = "card"
        }(
            // source
            Nui::Dom::reference([](auto&& weakElementPtr){
                auto element = weakElementPtr.lock();
                if (!element)
                    return;

                emscripten::val::global("setupCardFlyin")(element->val());
            }),
            div{
                class_ = "card-source"
            }(
                Nui::Dom::reference([](auto&& weakElementPtr){
                    auto element = weakElementPtr.lock();
                    if (!element)
                        return;

                    auto source = removeIndentation(R"(
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

                    emscripten::val::global("createCodeMirror")(element->val(), emscripten::val{source}, emscripten::val{true});
                })
            ),
            // what the source generates
            div{
                class_ = "card-content",
                id = "simpleReactiveCardContent"
            }(
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
            )
        );
        // clang-format on
    }
    //---------------------------------------------------------------------------------------------------------------------
    // #####################################################################################################################
}