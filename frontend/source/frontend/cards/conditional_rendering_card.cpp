#include <frontend/cards/conditional_rendering_card.hpp>

#include <nui/frontend/attributes.hpp>
#include <nui/frontend/elements.hpp>
#include <nui/frontend/elements/nil.hpp>

namespace NuiPage
{
    // #####################################################################################################################
    struct ConditionalRenderingCard::Implementation
    {
        Nui::Observed<bool> contentSwitch{false};
    };
    // #####################################################################################################################
    ConditionalRenderingCard::ConditionalRenderingCard()
        : impl_{std::make_unique<Implementation>()}
    {}
    //---------------------------------------------------------------------------------------------------------------------
    ConditionalRenderingCard::~ConditionalRenderingCard() = default;
    //---------------------------------------------------------------------------------------------------------------------
    ConditionalRenderingCard::ConditionalRenderingCard(ConditionalRenderingCard&&) = default;
    //---------------------------------------------------------------------------------------------------------------------
    ConditionalRenderingCard& ConditionalRenderingCard::operator=(ConditionalRenderingCard&&) = default;
    //---------------------------------------------------------------------------------------------------------------------
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

        return div{}(
            // View updates depending on observed values here:
            observe(impl_->contentSwitch),
            [weak = weak_from_base<ConditionalRenderingCard>()]() -> Nui::ElementRenderer {
                auto self = weak.lock();
                if (!self)
                    return nil();

                const bool contentSwitch = *self->impl_->contentSwitch;

                if (!contentSwitch)
                {
                    return button{
                        onClick =
                            [weak = self->weak_from_base<ConditionalRenderingCard>()]() {
                                if (auto self = weak.lock(); self)
                                    self->impl_->contentSwitch = !*self->impl_->contentSwitch;
                            },
                        class_ = "btn btn-primary"}("Login");
                }
                else
                {
                    return button{
                        onClick =
                            [weak = self->weak_from_base<ConditionalRenderingCard>()]() {
                                if (auto self = weak.lock(); self)
                                    self->impl_->contentSwitch = !*self->impl_->contentSwitch;
                            },
                        class_ = "btn btn-primary"}("Logout");
                }
            });
    }
    // #####################################################################################################################
}