#include <frontend/page_frame.hpp>

#include <nui/core.hpp>
#include <nui/window.hpp>

#include <nui/frontend/dom/dom.hpp>

static std::unique_ptr<NuiPage::PageFrame> pageFrame;
static std::unique_ptr<Nui::Dom::Dom> dom;

extern "C" void frontendMain()
{
    using namespace NuiPage;

    pageFrame = std::make_unique<PageFrame>();
    dom = std::make_unique<Nui::Dom::Dom>();
    dom->setBody(pageFrame->render());
}

EMSCRIPTEN_BINDINGS(nui_example_frontend)
{
    emscripten::function("main", &frontendMain);
}
#include <nui/frontend/bindings.hpp>