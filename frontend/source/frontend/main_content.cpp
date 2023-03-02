#include <frontend/main_content.hpp>

#include <frontend/cards/attribute_card.hpp>
#include <frontend/cards/conditional_rendering_card.hpp>
#include <frontend/cards/function_component_card.hpp>
#include <frontend/cards/list_card.hpp>
#include <frontend/cards/simple_reactive_card.hpp>

#include <nui/frontend/attributes.hpp>
#include <nui/frontend/elements.hpp>

namespace NuiPage
{
    // #####################################################################################################################
    struct MainContent::Implementation
    {
        std::shared_ptr<SimpleReactiveCard> card1 = std::make_shared<SimpleReactiveCard>();
        std::shared_ptr<FunctionComponentCard> card2 = std::make_shared<FunctionComponentCard>();
        std::shared_ptr<ConditionalRenderingCard> card3 = std::make_shared<ConditionalRenderingCard>();
        std::shared_ptr<AttributeCard> card4 = std::make_shared<AttributeCard>();
        std::shared_ptr<ListCard> card5 = std::make_shared<ListCard>();
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
                    "A C++ library for creating web-based user interfaces for Linux and Windows"
                )
            ),
            div{id = "subTitleControls"}(
                button{
                    id = "getStartedButton",
                    class_ = "btn btn-primary"
                }("Get Started")
            ),
            div{id = "mainText"}(
                "This page is written in C++ and CSS and rendered using the Nui library. "
                "Assisted by Bootstrap and CodeMirror. "
            ),
            div{id = "uiExampleWrap"}(
                figure{id = "uiExample"}(
                    img{
                        src = "./assets/example.png",
                        alt = "Example Image",
                        width = "400px",
                        height = "300px"
                    }(),
                    figcaption{}("An example of a user interface created with Nui")
                )
            ),
            div{id = "cardArea"}(
                (*impl_->card1)(),
                (*impl_->card2)(),
                (*impl_->card3)(),
                (*impl_->card4)(),
                (*impl_->card5)()
            )
        );
        // clang-format on
    }
    //---------------------------------------------------------------------------------------------------------------------
    // #####################################################################################################################
}