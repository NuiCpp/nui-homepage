#include <frontend/examples/button_counter.hpp>

#include <nui/frontend/attributes.hpp>
#include <nui/frontend/elements.hpp>

namespace NuiPage
{
    Nui::ElementRenderer ButtonCounter::render()
    {
        using namespace Nui::Elements;
        using namespace Nui::Attributes;
        using Nui::Elements::div;

        const auto buttonTextMaker = [](int count) -> std::string
        {
            return "Times clicked: " + std::to_string(count);
        };

        return div{
            class_ = "button-counter",
        }(
            button{
                class_ = "btn btn-primary",
                onClick =
                    [this]()
                {
                    timesClicked++;
                },
            }("Click me!"),
            div{
                class_ = "button-counter__count",
            }(observe(timesClicked).generate(buttonTextMaker))
        );
    }
}