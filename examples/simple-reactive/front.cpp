#include <nui/frontend/dom/dom.hpp>

#include <nui/frontend/attributes.hpp>
#include <nui/frontend/elements.hpp>

extern "C" void EMSCRIPTEN_KEEPALIVE frontendMain()
{
    using namespace Nui;
    using namespace Nui::Elements;
    using namespace Nui::Attributes;
    using Nui::Elements::div; // because of the global div.

    thread_local Nui::Dom::Dom dom;
    dom.setBody(div{}("Hello World"));
}

EMSCRIPTEN_BINDINGS(nui_example_frontend)
{
    emscripten::function("main", &frontendMain);
}
#include <nui/frontend/bindings.hpp>