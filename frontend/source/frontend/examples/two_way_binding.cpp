#include <frontend/examples/two_way_binding.hpp>

#include <nui/frontend/attributes.hpp>
#include <nui/frontend/elements.hpp>

#include <fmt/format.h>

namespace NuiPage
{
    Nui::ElementRenderer TwoWayBinding::render()
    {
        using namespace Nui::Elements;
        using namespace Nui::Attributes;
        using Nui::Elements::div;

        // clang-format off
        return div{class_ = "two-way-binding"}(
            input{
                class_ = "form-control",
                type = "text",
                // value attribute is for intial value, value prop is dynamic
                "value"_prop = name_,
                onInput = [this](auto const& event) {
                    name_ = event["target"]["value"].template as<std::string>();
                },
            }(),
            div{class_ = "two-way-binding__preview"}(
                observe(name_).generate([](const std::string& n) -> std::string {
                    return fmt::format("Hello, {}!", n.empty() ? "world" : n);
                })
            )
        );
        // clang-format on
    }
}
