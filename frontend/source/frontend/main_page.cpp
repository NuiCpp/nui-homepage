#include <frontend/main_page.hpp>

#include <frontend/navigation_bar.hpp>

#include <nui/frontend/elements.hpp>

namespace NuiPage
{
    // #####################################################################################################################
    struct MainPage::Implementation
    {
        NavigationBar navBar;
    };
    // #####################################################################################################################
    MainPage::MainPage()
        : impl_{std::make_unique<Implementation>()}
    {}
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
        using Nui::Elements::div; // because of the global div.

        // clang-format off
        return body{}(
            impl_->navBar()
        );
        // clang-format on
    }
    // #####################################################################################################################
}