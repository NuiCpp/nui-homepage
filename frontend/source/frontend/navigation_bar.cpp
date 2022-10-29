#include <frontend/navigation_bar.hpp>

#include <nui/frontend/attributes.hpp>
#include <nui/frontend/elements.hpp>

namespace NuiPage
{
    // #####################################################################################################################
    struct NavigationBar::Implementation
    {};
    // #####################################################################################################################
    NavigationBar::NavigationBar()
        : impl_{std::make_unique<Implementation>()}
    {}
    //---------------------------------------------------------------------------------------------------------------------
    NavigationBar::~NavigationBar() = default;
    //---------------------------------------------------------------------------------------------------------------------
    NavigationBar::NavigationBar(NavigationBar&&) = default;
    //---------------------------------------------------------------------------------------------------------------------
    NavigationBar& NavigationBar::operator=(NavigationBar&&) = default;
    //---------------------------------------------------------------------------------------------------------------------
    Nui::ElementRenderer NavigationBar::operator()()
    {
        using namespace Nui;
        using namespace Nui::Elements;
        using namespace Nui::Attributes;
        using Nui::Elements::div; // because of the global div.

        // clang-format off
        return div{id = "navBar"}(
            // Icon Area In Corner
            div{}(
                img{id = "navMainIcon", src = ""}(
                    
                )
            )
        );
        // clang-format on
    }
    // #####################################################################################################################
}