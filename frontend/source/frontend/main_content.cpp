#include <frontend/main_content.hpp>

#include <ui5-sap-icons/icons/chain-link.hpp>
#include <ui5-sap-icons/icons/circle-task.hpp>
#include <ui5-sap-icons/icons/combine.hpp>
#include <ui5-sap-icons/icons/decision.hpp>
#include <ui5-sap-icons/icons/favorite.hpp>
#include <ui5-sap-icons/icons/grid.hpp>
#include <ui5-sap-icons/icons/puzzle.hpp>
#include <ui5-sap-icons/icons/refresh.hpp>
#include <ui5-sap-icons/icons/split.hpp>
#include <ui5-sap-icons/icons/technical-object.hpp>

#include <frontend/cards/attribute_card.hpp>
#include <frontend/cards/conditional_rendering_card.hpp>
#include <frontend/cards/function_component_card.hpp>
#include <frontend/cards/list_card.hpp>
#include <frontend/cards/simple_reactive_card.hpp>

#include <nui/frontend/api/json.hpp>
#include <nui/frontend/attributes.hpp>
#include <nui/frontend/elements.hpp>
#include <nui/frontend/utility/functions.hpp>
#include <nui/frontend/val.hpp>

#include <fmt/format.h>

namespace NuiPage
{
    namespace
    {
        std::string formatCount(int count)
        {
            if (count < 0)
                return "—";
            if (count >= 1000)
                return fmt::format("{:.1f}k", count / 1000.0);
            return fmt::format("{}", count);
        }
    }

    // #####################################################################################################################
    struct MainContent::Implementation
    {
        std::shared_ptr<SimpleReactiveCard> reactiveCard = std::make_shared<SimpleReactiveCard>();
        std::shared_ptr<FunctionComponentCard> componentsCard = std::make_shared<FunctionComponentCard>();
        std::shared_ptr<ConditionalRenderingCard> conditionalRenderingCard =
            std::make_shared<ConditionalRenderingCard>();
        std::shared_ptr<AttributeCard> attributesCard = std::make_shared<AttributeCard>();
        std::shared_ptr<ListCard> listsCard = std::make_shared<ListCard>();

        Nui::Observed<int> stars{-1};
        Nui::Observed<int> forks{-1};

        Nui::Observed<bool> shown{true};
    };
    // #####################################################################################################################
    MainContent::MainContent()
        : impl_{std::make_unique<Implementation>()}
    {
        auto* implPtr = impl_.get();

        // Use the browser's native fetch API (no backend required)
        Nui::val::global("fetch")(std::string{"https://api.github.com/repos/NuiCpp/Nui"})
            .call<Nui::val>(
                "then",
                Nui::bind(
                    [](Nui::val response) -> Nui::val
                    {
                        return response.call<Nui::val>("json");
                    },
                    std::placeholders::_1
                )
            )
            .call<void>(
                "then",
                Nui::bind(
                    [implPtr](Nui::val data)
                    {
                        implPtr->stars = data["stargazers_count"].as<int>();
                        implPtr->forks = data["forks_count"].as<int>();
                        implPtr->stars.eventContext().executeActiveEventsImmediately();
                    },
                    std::placeholders::_1
                )
            );
    }
    //---------------------------------------------------------------------------------------------------------------------
    void MainContent::show(bool show)
    {
        impl_->shown = show;
    }
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
        using Nui::Elements::div;
        using Nui::Elements::span;

        // clang-format off
        return div{
            id = "pageContent",
            style = observe(impl_->shown).generate([](bool shown) {
                return fmt::format(
                    "display: {};",
                    shown ? "flex" : "none"
                );
            })
        }(
            div{id = "titleBox"}(
                div{id = "pageTitle"}(
                    "Nui WebView Library"
                ),
                div{id = "pageSubtitle"}(
                    "A C++ library for creating web-based user interfaces for Linux, Windows and MacOS."
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
                "Assisted by Bootstrap and CodeMirror."
            ),

            // ── GitHub stats bar ──────────────────────────────────────────────
            div{id = "statsBar"}(
                a{
                    class_ = "stats-item",
                    href = "https://github.com/NuiCpp/Nui/stargazers",
                    "target"_attr = "_blank",
                    "rel"_attr = "noopener noreferrer"
                }(
                    span{class_ = "stats-icon", style = "fill: gold;"}(Ui5Icons::favorite()),
                    span{class_ = "stats-count"}(
                        observe(impl_->stars).generate([](int s) -> std::string {
                            return formatCount(s);
                        })
                    ),
                    span{class_ = "stats-unit"}("stars")
                ),
                div{class_ = "stats-divider"}(),
                a{
                    class_ = "stats-item",
                    href = "https://github.com/NuiCpp/Nui/network/members",
                    "target"_attr = "_blank",
                    "rel"_attr = "noopener noreferrer"
                }(
                    span{class_ = "stats-icon"}(Ui5Icons::split()),
                    span{class_ = "stats-count"}(
                        observe(impl_->forks).generate([](int f) -> std::string {
                            return formatCount(f);
                        })
                    ),
                    span{class_ = "stats-unit"}("forks")
                ),
                div{class_ = "stats-divider"}(),
                a{
                    class_ = "stats-item stats-item--github",
                    href = "https://github.com/NuiCpp/Nui",
                    "target"_attr = "_blank",
                    "rel"_attr = "noopener noreferrer"
                }(
                    span{class_ = "stats-icon"}(Ui5Icons::chain_link()),
                    span{class_ = "stats-unit"}("View on GitHub")
                )
            ),

            // ── Why Nui? feature grid ─────────────────────────────────────────
            div{id = "whyNui"}(
                div{class_ = "why-nui__header"}("Why Nui?"),
                div{class_ = "why-nui__grid"}(
                    div{class_ = "why-nui__feature"}(
                        span{class_ = "why-nui__icon"}(Ui5Icons::combine()),
                        div{class_ = "why-nui__title"}("Reactive by Design"),
                        div{class_ = "why-nui__desc"}(
                            "Nui::Observed<T> gives you fine-grained UI reactivity "
                            "from standard C++ - no virtual DOM diff needed. "
                            "Highly performant algorithms keep updates minimal. "
                        )
                    ),
                    div{class_ = "why-nui__feature"}(
                        span{class_ = "why-nui__icon"}(Ui5Icons::grid()),
                        div{class_ = "why-nui__title"}("Cross-Platform"),
                        div{class_ = "why-nui__desc"}(
                            "Renders natively on Linux on MacOS via WebKit and Windows via WebView2. "
                            "One codebase, three platforms."
                        )
                    ),
                    div{class_ = "why-nui__feature"}(
                        span{class_ = "why-nui__icon"}(Ui5Icons::puzzle()),
                        div{class_ = "why-nui__title"}("Pure C++"),
                        div{class_ = "why-nui__desc"}(
                            "Very little to no JavaScript required. Leverage the full C++ standard library "
                            "and your existing codebase directly in your UI."
                        )
                    ),
                    div{class_ = "why-nui__feature"}(
                        span{class_ = "why-nui__icon"}(Ui5Icons::decision()),
                        div{class_ = "why-nui__title"}("CMake Integration"),
                        div{class_ = "why-nui__desc"}(
                            "Drop Nui into any CMake project with a single "
                            "FetchContent_Declare call. No extra tooling. "
                            "Provided project template gets you up and running."
                        )
                    ),
                    div{class_ = "why-nui__feature"}(
                        span{class_ = "why-nui__icon"}(Ui5Icons::circle_task()),
                        div{class_ = "why-nui__title"}("Full C++ Ecosystem"),
                        div{class_ = "why-nui__desc"}(
                            "STL, Boost, or any C++ library works directly in your UI code "
                            "- no bridging boilerplate required."
                        )
                    ),
                    div{class_ = "why-nui__feature"}(
                        span{class_ = "why-nui__icon"}(Ui5Icons::technical_object()),
                        div{class_ = "why-nui__title"}("Leverage Web Components"),
                        div{class_ = "why-nui__desc"}(
                            "Vanilla compatible WebComponents can be used directly in your Nui UI. "
                            "CSS Frameworks work out of the box."
                        )
                    )
                )
            ),

            // ── Screenshot showcase ───────────────────────────────────────────
            div{id = "uiExampleWrap"}(
                figure{class_ = "ui-example"}(
                    img{
                        class_ = "ui-example-image",
                        src = "./assets/example.png",
                        alt = "Example Image",
                        width = "400px",
                        height = "300px"
                    }(),
                    figcaption{}("An example of a user interface created with Nui")
                ),
                figure{class_ = "ui-example"}(
                    img{
                        class_ = "ui-example-image",
                        src = "https://camo.githubusercontent.com/11e7081a9be872e63e5fff1b244a8b1d18118c82c6a8a64cc38b03f3dc770895/68747470733a2f2f73332e672e73342e6d6567612e696f2f6a67656d6b69623461356674653335726b747435777872776b7734656a6b347962656d6b662f6e75692d7363702f696d616765732f6e75692d736674702d73657373696f6e2e706e67",
                        alt = "nui-sftp screenshot",
                        width = "500px",
                        height = "300px"
                    }(),
                    figcaption{}("nui-sftp created using Nui")
                )
            ),

            // ── Feature cards ─────────────────────────────────────────────────
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
