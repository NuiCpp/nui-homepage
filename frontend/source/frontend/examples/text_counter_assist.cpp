#include <frontend/examples/text_counter.hpp>

namespace NuiPage
{
    std::string TextCounter::heading() const
    {
        return "Text Counter";
    }

    std::string TextCounter::explanation() const
    {
        return "A text input that reactively counts the number of characters as you type. "
               "This example demonstrates how to handle DOM events and use their payload to update observed state.";
    }

    std::string TextCounter::editorContentHeader() const
    {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc23-extensions"
        return
        {
#embed "../../../include/frontend/examples/text_counter.hpp"
        };
#pragma clang diagnostic pop
    }

    std::string TextCounter::editorContentSource() const
    {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc23-extensions"
        return
        {
#embed "text_counter.cpp"
        };
#pragma clang diagnostic pop
    }
}
