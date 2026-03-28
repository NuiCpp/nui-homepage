#include <frontend/examples/text_counter.hpp>

#include <nui/frontend/attributes.hpp>
#include <nui/frontend/elements.hpp>

namespace NuiPage
{
    Nui::ElementRenderer TextCounter::render()
    {
        using namespace Nui::Elements;
        using namespace Nui::Attributes;
        using Nui::Elements::div;

        // clang-format off
        return div{class_ = "text-counter"}(
            input{
                class_ = "form-control",
                type = "text",
                placeHolder = "Type something...",
                onInput = [this](auto const& event) {
                    text_ = event["target"]["value"].template as<std::string>();
                },
            }(),
            div{class_ = "text-counter__count"}(
                observe(text_).generate([](const std::string& t) -> std::string {
                    return "Characters: " + std::to_string(t.size());
                })
            )
        );
        // clang-format on
    }
}
