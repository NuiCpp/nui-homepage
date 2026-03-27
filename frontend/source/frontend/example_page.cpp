#include <frontend/example_page.hpp>

#include <script-nui-components/select.hpp>
#include <script-nui-components/carousel.hpp>

#include <nui/frontend/api/console.hpp>
#include <nui/frontend/attributes.hpp>
#include <nui/frontend/elements.hpp>

using namespace std::string_literals;
using namespace ScriptNuiComponents;

MAKE_HTML_VALUE_ATTRIBUTE_RENAME(data_ribbon, "data-ribbon")

namespace NuiPage
{
    // #####################################################################################################################
    struct ExamplePage::Implementation
    {
        std::shared_ptr<Nui::Observed<int>> page;
        std::unique_ptr<Carousel> carousel;
    };
    // #####################################################################################################################
    ExamplePage::ExamplePage()
        : impl_{std::make_unique<Implementation>(Implementation{
              .page = std::make_shared<Nui::Observed<int>>(0),
              .carousel{},
          })}
    {
        impl_->carousel = std::make_unique<Carousel>(Carousel{
            impl_->page,
            [this](int page)
            {
                return renderPage(page);
            },
            20,
            5
        });
    }
    //---------------------------------------------------------------------------------------------------------------------
    Nui::ElementRenderer ExamplePage::renderPage(int page)
    {
        using namespace Nui;
        using namespace Nui::Elements;
        using namespace Nui::Attributes;
        using Nui::Elements::div; // because of the global div.

        // clang-format off
        return div{
            class_ = "example-page__card"
        }(
            "Page "s + std::to_string(page + 1)
        );
        // clang-format on
    }
    //---------------------------------------------------------------------------------------------------------------------
    ExamplePage::~ExamplePage() = default;
    //---------------------------------------------------------------------------------------------------------------------
    ExamplePage::ExamplePage(ExamplePage&&) = default;
    //---------------------------------------------------------------------------------------------------------------------
    ExamplePage& ExamplePage::operator=(ExamplePage&&) = default;
    //---------------------------------------------------------------------------------------------------------------------
    Nui::ElementRenderer ExamplePage::operator()()
    {
        using namespace Nui;
        using namespace Nui::Elements;
        using namespace Nui::Attributes;
        using Nui::Elements::div; // because of the global div.

        // clang-format off
        return div{
            class_ = "example-page"
        }(
            ScriptNuiComponents::select(
                SelectOptions<decltype(impl_->page), std::vector<int>>{
                    .activeOption = impl_->page,
                    .options = {
                        0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
                        10,11,12,13,14,15,16,17,18,19
                    },
                    .onChange = [this](int newPage, Nui::WebApi::MouseEvent)
                    {
                        *impl_->page = newPage;
                    },
                    .activeRenderer = [](std::weak_ptr<Nui::Observed<int>>& option) -> ElementRenderer
                    {
                        auto locked = option.lock();
                        if (!locked)
                            return div{class_ = "example-page__select-active"}("Example #?");
                        return div{class_ = "example-page__select-active"}(
                            observe(option),
                            [](int page) -> std::string {
                                return "Example #"s + std::to_string(page + 1);
                            }
                        );
                    },
                    .elementRenderer = [](int option) -> ElementRenderer
                    {
                        return div{class_ = "example-page__select-option"}("Example #"s + std::to_string(option + 1));
                    },
                    .makeId = []() -> std::string
                    {
                        static int counter = 0;
                        return "example-page-select-"s + std::to_string(counter++);
                    },
                    .dontUpdateValue = true
                }
            ),
            (*impl_->carousel)()
        );
        // clang-format on
    }
    // #####################################################################################################################
}