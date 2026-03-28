#include <frontend/page_frame.hpp>

#include <frontend/about.hpp>
#include <frontend/main_content.hpp>
#include <frontend/navigation_bar.hpp>
#include <frontend/example_page.hpp>

#include <nui/frontend/api/console.hpp>
#include <nui/frontend/attributes.hpp>
#include <nui/frontend/elements.hpp>
#include <nui/frontend/utility/fragment_listener.hpp>
#include <nui/frontend/utility/stabilize.hpp>
#include <nui/event_system/listen.hpp>

#include <fmt/format.h>

using namespace std::string_literals;

MAKE_HTML_VALUE_ATTRIBUTE_RENAME(data_ribbon, "data-ribbon")

namespace NuiPage
{
    // #####################################################################################################################
    struct PageFrame::Implementation
    {
        NavigationBar navBar;
        MainContent mainContent;
        AboutPage aboutPage;
        ExamplePage examples;

        Nui::Observed<std::string> fragment{""};
        Nui::ListenRemover<decltype(fragment)> listenRemover;
    };
    // #####################################################################################################################
    PageFrame::PageFrame()
        : impl_{std::make_unique<Implementation>()}
    {
        Nui::listenToFragmentChanges(impl_->fragment);

        impl_->listenRemover = Nui::smartListen(
            impl_->fragment,
            [this](const std::string& frag)
            {
                // trim whitespace from frag:
                std::string_view fragView = frag;
                while (!fragView.empty() && std::isspace(fragView.front()))
                    fragView.remove_prefix(1);
                while (!fragView.empty() && std::isspace(fragView.back()))
                    fragView.remove_suffix(1);

                impl_->mainContent.show(fragView.empty() || fragView == "home");
                impl_->aboutPage.show(fragView == "about");
                impl_->examples.show(fragView == "examples");

                Nui::globalEventContext.executeActiveEventsImmediately();
            }
        );
    }
    //---------------------------------------------------------------------------------------------------------------------
    PageFrame::~PageFrame() = default;
    //---------------------------------------------------------------------------------------------------------------------
    PageFrame::PageFrame(PageFrame&&) = default;
    //---------------------------------------------------------------------------------------------------------------------
    PageFrame& PageFrame::operator=(PageFrame&&) = default;
    //---------------------------------------------------------------------------------------------------------------------
    Nui::ElementRenderer PageFrame::render()
    {
        using namespace Nui;
        using namespace Nui::Elements;
        using namespace Nui::Attributes;
        using Nui::Elements::div; // because of the global div.

        // clang-format off
        return body{}(
            impl_->navBar(),
            div{
                id = "pageFrameContent"
            }(
                impl_->mainContent(),
                impl_->aboutPage(),
                impl_->examples()
            ),
            a{
                class_ = Nui::observe(impl_->fragment).generate([](const std::string& frag) -> std::string {
                    return frag == "examples"
                        ? "github-fork-ribbon github-fork-ribbon--hidden"
                        : "github-fork-ribbon";
                }),
                href = "https://github.com/NuiCpp/Nui",
                data_ribbon = "Fork me on GitHub",
                Nui::Attributes::title = "Fork me on GitHub"
            }("Fork me on GitHub")
        );
        // clang-format on
    }
    // #####################################################################################################################
}