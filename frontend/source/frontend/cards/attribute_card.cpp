#include <frontend/cards/attribute_card.hpp>

#include <nui/frontend/attributes.hpp>
#include <nui/frontend/elements.hpp>
#include <nui/frontend/api/keyboard_event.hpp>

#include <fmt/format.h>

namespace NuiPage
{
    // #####################################################################################################################
    std::string AttributeCard::source() const
    {
        return removeIndentation(R"(
            // Header:
            Nui::Observed<std::string> inputText;

            // Source:
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
                    observe(inputText).generate([this](){
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
    Nui::ElementRenderer AttributeCard::render()
    {
        using namespace Nui;
        using namespace Nui::Elements;
        using namespace Nui::Attributes;
        using Nui::Elements::div; // there is a global symbol named div
        using Nui::Elements::span;
        using Nui::Elements::label;
        using Nui::Attributes::title;

        // clang-format off
        return div{
            style = fmt::format(
                "display: {}; flex-direction: {}",
                "flex", "column"
            )
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
                "value"_prop = inputText,
                onInput = [this](Nui::WebApi::KeyboardEvent event) {
                    inputText = event.target()["value"].template as<std::string>();
                }
            }(),
            span{
                // Attributes can be observed values:
                title = inputText
            }(
                // Text content or attributes can use this expression to generate more complex
                // values from observed values:
                observe(inputText).generate([this](){
                    return "Characters: " + std::to_string(inputText.size());
                })
            )
        );
        // clang-format on
    }
    // #####################################################################################################################
}