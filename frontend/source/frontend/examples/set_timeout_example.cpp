#include <frontend/examples/set_timeout_example.hpp>

#include <nui/frontend/attributes.hpp>
#include <nui/frontend/elements.hpp>
#include <nui/frontend/utility/functions.hpp>

#include <emscripten/val.h>

namespace NuiPage
{
    Nui::ElementRenderer SetTimeoutExample::render()
    {
        using namespace Nui::Elements;
        using namespace Nui::Attributes;
        using Nui::Elements::div;

        const auto onClickEvent = [this]()
        {
            status_ = "Waiting 1 seconds...";
            // Nui::bind wraps the C++ lambda into a JS-callable functor,
            // allowing it to be passed directly to window.setTimeout.
            Nui::val::global("setTimeout")(
                Nui::bind(
                    [this]()
                    {
                        status_ = "Hello from the future!";
                        // Dont forget to make ui udpates
                        status_.eventContext().executeActiveEventsImmediately();
                    }
                ),
                Nui::val{1000}
            );
        };

        // clang-format off
        return div{class_ = "set-timeout-example"}(
            div{class_ = "set-timeout-example__controls"}(
                button{
                    class_ = "script-nui-button",
                    "data-variant"_attr = "primary",
                    onClick = onClickEvent,
                }("Trigger (1s delay)"),
                button{
                    class_ = "script-nui-button",
                    "data-variant"_attr = "regular",
                    onClick = [this]() {
                        status_ = "Press the button.";
                    },
                }("Reset")
            ),
            div{class_ = "set-timeout-example__status"}(
                observe(status_).generate([](const std::string& s) { return s; })
            )
        );
        // clang-format on
    }
}
