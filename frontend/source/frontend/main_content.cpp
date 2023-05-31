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
        std::shared_ptr<SimpleReactiveCard> reactiveCard = std::make_shared<SimpleReactiveCard>();
        std::shared_ptr<FunctionComponentCard> componentsCard = std::make_shared<FunctionComponentCard>();
        std::shared_ptr<ConditionalRenderingCard> conditionalRenderingCard =
            std::make_shared<ConditionalRenderingCard>();
        std::shared_ptr<AttributeCard> attributesCard = std::make_shared<AttributeCard>();
        std::shared_ptr<ListCard> listsCard = std::make_shared<ListCard>();
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
                a{
                    id = "getStartedButton",
                    class_ = "btn btn-primary",
                    href = "https://nuicpp.github.io/nui-documentation/docs/getting_started/installation"
                }("Get Started")
            ),
            div{id = "mainText"}(
                "This page is written in C++ and CSS and rendered using the Nui library. "
                "Assisted by Bootstrap and CodeMirror. "
            ),
            div{id = "uiExampleWrap"}(
                figure{id = "uiExample"}(
                    img{
                        id = "uiExampleImage",
                        src = "./assets/example.png",
                        alt = "Example Image",
                        width = "400px",
                        height = "300px"
                    }(),
                    figcaption{}("An example of a user interface created with Nui")
                )
            ),
            div{id = "cardArea"}(
                (*impl_->reactiveCard)(),
                (*impl_->componentsCard)(),
                (*impl_->conditionalRenderingCard)(),
                (*impl_->attributesCard)(),
                (*impl_->listsCard)()
            )
        );
        // clang-format on
    }
    //---------------------------------------------------------------------------------------------------------------------
    // #####################################################################################################################
}