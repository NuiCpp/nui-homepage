#include <frontend/main_content.hpp>

#include <frontend/function_component_card.hpp>
#include <frontend/simple_reactive_card.hpp>

#include <nui/frontend/attributes.hpp>
#include <nui/frontend/elements.hpp>

namespace NuiPage
{
    // #####################################################################################################################
    struct MainContent::Implementation
    {
        std::shared_ptr<SimpleReactiveCard> card1 = std::make_shared<SimpleReactiveCard>();
        std::shared_ptr<FunctionComponentCard> card2 = std::make_shared<FunctionComponentCard>();
    };
    // #####################################################################################################################
    MainContent::MainContent()
        : impl_{std::make_unique<Implementation>()}
    {}
    //---------------------------------------------------------------------------------------------------------------------
    MainContent::~MainContent() = default;
    //---------------------------------------------------------------------------------------------------------------------
    MainContent::MainContent(MainContent&&) = default;
    //---------------------------------------------------------------------------------------------------------------------
    MainContent& MainContent::operator=(MainContent&&) = default;
    //---------------------------------------------------------------------------------------------------------------------
    Nui::ElementRenderer MainContent::operator()()
    {
        using namespace Nui;
        using namespace Nui::Elements;
        using namespace Nui::Attributes;
        using Nui::Elements::div; // because of the global div.

        // clang-format off
        return div{id = "pageContent"}(
            div{id = "titleBox"}(
                div{id = "pageTitle"}(
                    "Nui WebView Library"
                ),
                div{id = "pageSubtitle"}(
                    "A C++ library for creating web-based user interfaces"
                )
            ),
            div{id = "subTitleControls"}(
                button{
                    id = "getStartedButton",
                    class_ = "btn btn-primary"
                }("Get Started")
            ),
            div{id = "cardArea"}(
                (*impl_->card1)(),
                (*impl_->card2)()
            )
        );
        // clang-format on
    }
    //---------------------------------------------------------------------------------------------------------------------
    // #####################################################################################################################
}