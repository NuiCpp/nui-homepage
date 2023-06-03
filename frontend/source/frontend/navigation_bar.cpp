#include <frontend/navigation_bar.hpp>

#include <nui/frontend/attributes.hpp>
#include <nui/frontend/elements.hpp>

namespace NuiPage
{
    constexpr auto dataBsToggle = Nui::Attributes::AttributeFactory("data-bs-toggle");

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
        using Nui::Elements::span;

        // clang-format off
        return div{id = "navBar"}(
            // Icon Area In Corner
            div{
                id = "navIconArea"
            }(
                //img{id = "navMainIcon", src = ""}(),
                a{id = "navIconText", href = "#"}("Nui")
            ),
            div{
                id = "navLinks"
            }(
                div{
                    class_ = "dropdown"
                }(
                    a {
                        class_ = "dropdown-toggle",
                        href = "#",
                        dataBsToggle = "dropdown",
                        role = "button"
                    }("Documentation"),
                    ul {
                        class_ = "dropdown-menu dropdown-menu-color"
                    }(
                        li{}(
                            a {
                                class_ = "dropdown-item",
                                href = "https://github.com/NuiCpp/Nui"
                            }("Github Readme"),
                            a {
                                class_ = "dropdown-item",
                                // TODO: new domain
                                href = "https://nuicpp.github.io/nui-documentation/"
                            }("Documentation"),
                            a {
                                class_ = "dropdown-item",
                                href = "https://nuicpp.github.io/nui-documentation/docs/doxygen/"
                            }("Doxygen")
                        )
                    )
                ),
                a{
                    href = "#about"
                }(
                    "About"
                )
            )
        );
        // clang-format on
    }
    // #####################################################################################################################
}