#include <frontend/examples/set_timeout_example.hpp>

namespace NuiPage
{
    std::string SetTimeoutExample::heading() const
    {
        return "setTimeout via Nui::bind";
    }

    std::string SetTimeoutExample::explanation() const
    {
        return "Nui::bind wraps a C++ lambda into a JS-callable functor so it can be passed directly to "
               "window.setTimeout. After the delay, the callback updates an Observed<> value and the UI "
               "reacts immediately. Note: if the component could be destroyed before the timer fires, "
               "capture a weak_ptr or a shared flag instead of 'this' to avoid a dangling pointer.";
    }

    std::string SetTimeoutExample::editorContentHeader() const
    {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc23-extensions"
        return
        {
#embed "../../../include/frontend/examples/set_timeout_example.hpp"
        };
#pragma clang diagnostic pop
    }

    std::string SetTimeoutExample::editorContentSource() const
    {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc23-extensions"
        return
        {
#embed "set_timeout_example.cpp"
        };
#pragma clang diagnostic pop
    }
}
