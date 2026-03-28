#include <frontend/navigation_bar.hpp>

#include <nui/frontend/attributes.hpp>
#include <nui/frontend/elements.hpp>

namespace NuiPage
{
    constexpr auto dataBsToggle = Nui::Attributes::AttributeFactory("data-bs-toggle");
    constexpr auto ariaLabel = Nui::Attributes::AttributeFactory("aria-label");
    constexpr auto ariaExpanded = Nui::Attributes::AttributeFactory("aria-expanded");

    // #####################################################################################################################
    struct NavigationBar::Implementation
    {
        Nui::Observed<bool> menuOpen{false};
    };
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
        using Nui::Elements::div;
        using Nui::Elements::span;

        // clang-format off
        return nav{id = "navBar"}(
            // Brand
            div{class_ = "nav__brand"}(
                a{class_ = "nav__logo", href = "#"}(
                    span{class_ = "nav__logo-accent"}("Nui"),
                    span{class_ = "nav__logo-sub"}("C++")
                )
            ),

            // Burger button — visible only on mobile via CSS
            button{
                class_ = "nav__burger",
                ariaLabel = "Toggle navigation",
                ariaExpanded = observe(impl_->menuOpen).generate([](bool open) {
                    return open ? std::string{"true"} : std::string{"false"};
                }),
                onClick = [this]() {
                    impl_->menuOpen = !impl_->menuOpen.value();
                },
            }(
                span{class_ = "nav__burger-bar"}(),
                span{class_ = "nav__burger-bar"}(),
                span{class_ = "nav__burger-bar"}()
            ),

            // Links — hidden on mobile until burger is pressed
            div{
                class_ = observe(impl_->menuOpen).generate([](bool open) {
                    return open ? std::string{"nav__menu nav__menu--open"} : std::string{"nav__menu"};
                }),
            }(
                div{class_ = "dropdown nav__item"}(
                    a{
                        class_ = "nav__link dropdown-toggle",
                        href = "#",
                        dataBsToggle = "dropdown",
                        role = "button",
                    }("Documentation"),
                    ul{class_ = "dropdown-menu dropdown-menu-color nav__dropdown"}(
                        li{}(
                            a{
                                class_ = "dropdown-item nav__dropdown-item",
                                href = "https://github.com/NuiCpp/Nui",
                            }("GitHub Readme")
                        ),
                        li{}(
                            a{
                                class_ = "dropdown-item nav__dropdown-item",
                                href = "https://nuicpp.github.io/nui-documentation/",
                            }("Documentation")
                        ),
                        li{}(
                            a{
                                class_ = "dropdown-item nav__dropdown-item",
                                href = "https://nuicpp.github.io/nui-documentation/docs/doxygen/",
                            }("Doxygen")
                        )
                    )
                ),
                a{class_ = "nav__link nav__item", href = "#about"}("About"),
                a{class_ = "nav__link nav__item", href = "#examples"}("Examples")
            )
        );
        // clang-format on
    }
    // #####################################################################################################################
}
