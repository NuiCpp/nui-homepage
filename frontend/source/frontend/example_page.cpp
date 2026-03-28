#include <frontend/example_page.hpp>
#include <frontend/examples/basic_example.hpp>
#include <frontend/examples/button_counter.hpp>
#include <frontend/examples/text_counter.hpp>

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
        std::vector<std::unique_ptr<BasicExample>> examples;
    };
    // #####################################################################################################################
    ExamplePage::ExamplePage()
        : impl_{std::make_unique<Implementation>(Implementation{
              .page = std::make_shared<Nui::Observed<int>>(0),
          })}
    {
        impl_->examples.push_back(std::make_unique<ButtonCounter>());
        impl_->examples.push_back(std::make_unique<TextCounter>());

        impl_->carousel = std::make_unique<Carousel>(Carousel{
            impl_->page,
            [this](int page)
            {
                return renderPage(page);
            },
            static_cast<int>(impl_->examples.size()),
            std::min(5, static_cast<int>(impl_->examples.size())),
            CarouselControlsPosition::Bottom
        });
    }
    //---------------------------------------------------------------------------------------------------------------------
    Nui::ElementRenderer ExamplePage::renderPage(int page)
    {
        using namespace Nui::Elements;
        using namespace Nui::Attributes;
        using Nui::Elements::div;

        if (page < 0 || page >= static_cast<int>(impl_->examples.size()))
            return div{class_ = "example-page__card"}();

        return (*impl_->examples[page])();
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
        using Nui::Elements::div;

        std::vector<int> options;
        for (int i = 0; i < static_cast<int>(impl_->examples.size()); ++i)
            options.push_back(i);

        // clang-format off
        return div{class_ = "example-page"}(
            ScriptNuiComponents::select(
                SelectOptions<decltype(impl_->page), std::vector<int>>{
                    .activeOption = impl_->page,
                    .options = std::move(options),
                    .onChange = [this](int newPage, Nui::WebApi::MouseEvent)
                    {
                        *impl_->page = newPage;
                    },
                    .activeRenderer = [this](std::weak_ptr<Nui::Observed<int>>& option) -> ElementRenderer
                    {
                        auto locked = option.lock();
                        if (!locked)
                            return div{class_ = "example-page__select-active"}("Example #?");
                        return div{class_ = "example-page__select-active"}(
                            observe(option),
                            [this](int page) -> std::string {
                                if (page < 0 || page >= static_cast<int>(impl_->examples.size()))
                                    return "Example #?";
                                return fmt::format("Example #{}: {}", page + 1, impl_->examples[page]->heading());
                            }
                        );
                    },
                    .elementRenderer = [this](int option) -> ElementRenderer
                    {
                        return div{class_ = "example-page__select-option"}(
                            [this](int page) -> std::string {
                                if (page < 0 || page >= static_cast<int>(impl_->examples.size()))
                                    return "Example #?";
                                return fmt::format("Example #{}: {}", page + 1, impl_->examples[page]->heading());
                            }(option)
                        );
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
