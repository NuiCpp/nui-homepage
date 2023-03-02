#include <frontend/cards/attribute_card.hpp>

#include <nui/frontend/attributes.hpp>
#include <nui/frontend/elements.hpp>

namespace NuiPage
{
    // #####################################################################################################################
    std::string AttributeCard::source() const
    {
        return removeIndentation(R"(
            thread_local Observed<std::string> inputText = "Type Here!";

            return div{}(
                label{
                    for_ = "attributeInput",
                    class_ = "form-label" // <- bootstrap
                }(
                    // Text content can be observed values:
                    inputText
                ),
                input{
                    id = "attributeInput",
                    class_ = "form-control",
                    type = "text",
                    value = inputText,
                    onInput = [](auto const& event) {
                        inputText = event["target"]["value"].template as<std::string>();
                    }
                }(),
                span{
                    // Attributes can be observed values:
                    title = inputText
                }(
                    // Text content or attributes can use this expression to generate
                    //  more complex values from observed values:
                    observe(inputText).generate([](){
                        return "Characters: " + std::to_string(inputText.size());
                    })
                )
            );
        )");
    }
    //---------------------------------------------------------------------------------------------------------------------
    std::string AttributeCard::header() const
    {
        return "Attributes";
    }
    //---------------------------------------------------------------------------------------------------------------------
    std::string AttributeCard::description() const
    {
        return "This card demonstrates how to use the attribute feature of NUI. "
               "Any attribute can be observed and will be updated when the value changes. ";
    }
    //---------------------------------------------------------------------------------------------------------------------
    Nui::ElementRenderer AttributeCard::render() const
    {
        using namespace Nui;
        using namespace Nui::Elements;
        using namespace Nui::Attributes;
        using Nui::Elements::div; // there is a global symbol named div
        using Nui::Elements::span;
        using Nui::Elements::label;
        using Nui::Attributes::title;

        thread_local Observed<std::string> inputText = "Type Here!";

        // clang-format off
        return div{
            style = Style{
                "display"_style = "flex",
                "flex-direction"_style = "column"
            }
        }(
            label{
                for_ = "attributeInput",
                class_ = "form-label"
            }(
                // Text content can be observed values:
                inputText
            ),
            input{
                id = "attributeInput",
                class_ = "form-control",
                type = "text",
                value = inputText,
                onInput = [](auto const& event) {
                    inputText = event["target"]["value"].template as<std::string>();
                }
            }(),
            span{
                // Attributes can be observed values:
                title = inputText
            }(
                // Text content or attributes can use this expression to generate more complex
                // values from observed values:
                observe(inputText).generate([](){
                    return "Characters: " + std::to_string(inputText.size());
                })
            )
        );
        // clang-format on
    }
    // #####################################################################################################################
}