#include <frontend/page_frame.hpp>

#include <nui/core.hpp>
#include <nui/window.hpp>

#include <nui/frontend/dom/dom.hpp>

extern "C" void frontendMain()
{
    using namespace NuiPage;

    thread_local PageFrame pageFrame;
    thread_local Nui::Dom::Dom dom;
    dom.setBody(pageFrame.render());
}

EMSCRIPTEN_BINDINGS(nui_example_frontend)
{
    emscripten::function("main", &frontendMain);
}
#include <nui/frontend/bindings.hpp>