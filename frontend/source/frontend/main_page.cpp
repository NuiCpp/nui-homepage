#include <frontend/main_page.hpp>

#include <frontend/navigation_bar.hpp>

#include <nui/frontend/api/console.hpp>
#include <nui/frontend/attributes.hpp>
#include <nui/frontend/elements.hpp>
#include <nui/frontend/utility/fragment_listener.hpp>

using namespace std::string_literals;

namespace NuiPage
{
    // #####################################################################################################################
    struct MainPage::Implementation
    {
        NavigationBar navBar;

        Nui::Observed<std::string> fragment;
    };
    // #####################################################################################################################
    MainPage::MainPage()
        : impl_{std::make_unique<Implementation>()}
    {
        Nui::listenToFragmentChanges(impl_->fragment);
    }
    //---------------------------------------------------------------------------------------------------------------------
    MainPage::~MainPage() = default;
    //---------------------------------------------------------------------------------------------------------------------
    MainPage::MainPage(MainPage&&) = default;
    //---------------------------------------------------------------------------------------------------------------------
    MainPage& MainPage::operator=(MainPage&&) = default;
    //---------------------------------------------------------------------------------------------------------------------
    Nui::ElementRenderer MainPage::render()
    {
        using namespace Nui;
        using namespace Nui::Elements;
        using namespace Nui::Attributes;
        using Nui::Elements::div; // because of the global div.

        // clang-format off
        return body{}(
            impl_->navBar(),
            // "Nui.Router" so to speak
            div{
                id = "mainPageContent"
            }(
                switch_(impl_->fragment)(
                    Elements::default_()(fragment(
                        "Hi"
                    )),
                    case_("")(fragment(
                        "Page"
                    )),
                    case_("about")(fragment(
                        "About" 
                    ))
                )
            )
        );
        // clang-format on
    }
    // #####################################################################################################################
}