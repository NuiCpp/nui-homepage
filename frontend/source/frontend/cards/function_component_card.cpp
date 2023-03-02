#include <frontend/cards/function_component_card.hpp>

#include <nui/frontend/attributes.hpp>
#include <nui/frontend/elements.hpp>

#include <fmt/format.h>

namespace NuiPage
{
    // #####################################################################################################################
    struct PrettyBoxArgs
    {
        int width;
        int height;
        std::string textContent;
    };
    //---------------------------------------------------------------------------------------------------------------------
    auto prettyBox(PrettyBoxArgs const& args)
    {
        using namespace Nui;
        using namespace Nui::Elements;
        using namespace Nui::Attributes;
        using Nui::Elements::div; // there is a global symbol named div

        // clang-format off
        return div{
            style = Style{
                "width"_style = fmt::format("{}px", args.width),
                "height"_style = fmt::format("{}px", args.height),
                "background-color"_style = "#a1232b",
                "border"_style = "1px solid black",
            }
        }(args.textContent);
        // clang-format on
    }
    // #####################################################################################################################
    std::string FunctionComponentCard::source() const
    {
        return removeIndentation(R"(
            struct PrettyBoxArgs
            {
                int width;
                int height;
                Observed<std::string>& textContent;
            };

            // Component:
            auto prettyBox(PrettyBoxArgs const& args) /* -> Nui::ElementRenderer */
            {
                // clang-format off
                return div{
                    style = Style{
                        "width"_style = fmt::format("{}px", args.width),
                        "height"_style = fmt::format("{}px", args.height),
                        "background-color"_style = "#a1232b",
                        "border"_style = "1px solid black",
                    }
                }(args.textContent);
                // clang-format on
            }

            // Somewhere else:
            div{}(
                prettyBox({
                    .width = 200, 
                    .height = 80, 
                    .textContent = "Hello World!"
                })
            )
        )");
    }
    //---------------------------------------------------------------------------------------------------------------------
    std::string FunctionComponentCard::header() const
    {
        return "Components as Functions";
    }
    //---------------------------------------------------------------------------------------------------------------------
    std::string FunctionComponentCard::description() const
    {
        return "Elements can be compounded as Components via simple functions or function objects.";
    }
    //---------------------------------------------------------------------------------------------------------------------
    Nui::ElementRenderer FunctionComponentCard::render() const
    {
        return Nui::Elements::fragment(prettyBox({.width = 200, .height = 80, .textContent = "Hello World!"}));
    }
    // #####################################################################################################################
}