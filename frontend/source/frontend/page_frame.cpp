#include <frontend/page_frame.hpp>

#include <frontend/main_content.hpp>
#include <frontend/navigation_bar.hpp>

#include <nui/frontend/api/console.hpp>
#include <nui/frontend/attributes.hpp>
#include <nui/frontend/elements.hpp>
#include <nui/frontend/utility/fragment_listener.hpp>

using namespace std::string_literals;

namespace NuiPage
{
    // #####################################################################################################################
    struct PageFrame::Implementation
    {
        NavigationBar navBar;
        MainContent mainContent;

        Nui::Observed<std::string> fragment;
    };
    // #####################################################################################################################
    PageFrame::PageFrame()
        : impl_{std::make_unique<Implementation>()}
    {
        Nui::listenToFragmentChanges(impl_->fragment);
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
            // "Nui.Router" so to speak
            div{
                id = "pageFrameContent"
            }(
                switch_(impl_->fragment)(
                    Elements::default_()(div{}(
                        "Hi"
                    )),
                    case_("")(div{}(
                        impl_->mainContent()
                    )),
                    case_("about")(div{}(
                        "About" 
                    ))
                )
            )
        );
        // clang-format on
    }
    // #####################################################################################################################
}