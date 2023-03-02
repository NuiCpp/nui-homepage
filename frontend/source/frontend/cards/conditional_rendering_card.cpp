#include <frontend/cards/conditional_rendering_card.hpp>

#include <nui/frontend/attributes.hpp>
#include <nui/frontend/elements.hpp>

namespace NuiPage
{
    // #####################################################################################################################
    std::string ConditionalRenderingCard::source() const
    {
        return removeIndentation(R"(
            thread_local Observed<bool> contentSwitch{false};

            return div{}(
                // View updates depending on observed values here:
                observe(showContent),

                // Function returning a renderer is called on initial rendering and on value updates:
                []() -> Nui::ElementRenderer {
                    if (!contentSwitch)
                    {
                        return button{onClick = []() {
                            contentSwitch = !contentSwitch;
                        }}("Login")
                    }
                    else
                    {
                        return button{onClick = []() {
                            contentSwitch = !contentSwitch;
                        }}("Logout")
                    }
             });
        )");
    }
    //---------------------------------------------------------------------------------------------------------------------
    std::string ConditionalRenderingCard::header() const
    {
        return "Conditional Rendering";
    }
    //---------------------------------------------------------------------------------------------------------------------
    std::string ConditionalRenderingCard::description() const
    {
        return "This card demonstrates how to use the conditional rendering feature of NUI. "
               "Any logic can be used to determine which elements are rendered because of the functional nature of "
               "nui. ";
    }
    //---------------------------------------------------------------------------------------------------------------------
    Nui::ElementRenderer ConditionalRenderingCard::render() const
    {
        using namespace Nui;
        using namespace Nui::Elements;
        using namespace Nui::Attributes;
        using Nui::Elements::div; // there is a global symbol named div

        thread_local Observed<bool> contentSwitch{false};

        return div{}(
            // View updates depending on observed values here:
            observe(contentSwitch),
            []() -> Nui::ElementRenderer {
                if (!*contentSwitch)
                {
                    return button{
                        onClick =
                            []() {
                                contentSwitch = !*contentSwitch;
                            },
                        class_ = "btn btn-primary"}("Login");
                }
                else
                {
                    return button{
                        onClick =
                            []() {
                                contentSwitch = !*contentSwitch;
                            },
                        class_ = "btn btn-primary"}("Logout");
                }
            });
    }
    // #####################################################################################################################
}