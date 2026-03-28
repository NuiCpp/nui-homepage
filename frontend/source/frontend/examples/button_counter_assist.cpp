#include <frontend/examples/button_counter.hpp>

namespace NuiPage
{
    std::string ButtonCounter::heading() const
    {
        return "Button Counter";
    }

    std::string ButtonCounter::editorContentHeader() const
    {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc23-extensions"
        return
        {
#embed "../../../include/frontend/examples/button_counter.hpp"
        };
#pragma clang diagnostic pop
    }

    std::string ButtonCounter::editorContentSource() const
    {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc23-extensions"
        return
        {
#embed "button_counter.cpp"
        };
#pragma clang diagnostic pop
    }

    std::string ButtonCounter::explanation() const
    {
        return "This is a simple button counter example. A click increases the count, which is displayed alongside the "
               "button. This example demonstrates basic state management and reactivity in a Nui component.";
    }
}