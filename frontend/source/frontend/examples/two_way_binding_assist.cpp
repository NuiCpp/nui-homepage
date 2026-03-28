#include <frontend/examples/two_way_binding.hpp>

namespace NuiPage
{
    std::string TwoWayBinding::heading() const
    {
        return "Two-Way Binding";
    }

    std::string TwoWayBinding::explanation() const
    {
        return "The input's value attribute is driven by an observed string, and onInput writes back to that same "
               "observed value. This creates a two-way binding: external changes (e.g. programmatic resets) update "
               "the input, and user typing updates the observed state.";
    }

    std::string TwoWayBinding::editorContentHeader() const
    {
        return
        {
#embed "../../../include/frontend/examples/two_way_binding.hpp"
        };
    }

    std::string TwoWayBinding::editorContentSource() const
    {
        return
        {
#embed "two_way_binding.cpp"
        };
    }
}
