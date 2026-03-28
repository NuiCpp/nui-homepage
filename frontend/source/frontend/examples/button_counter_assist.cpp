#include <frontend/examples/button_counter.hpp>

namespace NuiPage
{
    std::string ButtonCounter::heading() const
    {
        return "Button Counter";
    }

    std::string ButtonCounter::editorContentHeader() const
    {
        return
        {
#embed "../../../include/frontend/examples/button_counter.hpp"
        };
    }

    std::string ButtonCounter::editorContentSource() const
    {
        return
        {
#embed "button_counter.cpp"
        };
    }

    std::string ButtonCounter::explanation() const
    {
        return "This is a simple button counter example. A click increases the count, which is displayed alongside the "
               "button. This example demonstrates basic state management and reactivity in a Nui component.";
    }
}