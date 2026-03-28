#include <frontend/examples/basic_example.hpp>

#include <script-nui-components/button.hpp>

#include <nui/frontend/attributes.hpp>
#include <nui/frontend/elements.hpp>
#include <nui/event_system/listen.hpp>

namespace NuiPage
{
    // #####################################################################################################################
    bool BasicExample::isMobile()
    {
        return emscripten::val::global("window")
            .call<emscripten::val>("matchMedia", std::string{"(max-width: 640px)"})["matches"]
            .as<bool>();
    }
    //---------------------------------------------------------------------------------------------------------------------
    std::string BasicExample::preconditionContent(std::string content)
    {
        static constexpr std::array<std::string_view, 4> overrides = {
            "std::string heading() const override;",
            "std::string explanation() const override;",
            "std::string editorContentHeader() const override;",
            "std::string editorContentSource() const override;",
        };

        // Remove override declaration lines (strip leading whitespace before comparing)
        std::string filtered;
        filtered.reserve(content.size());
        std::size_t pos = 0;
        while (pos < content.size())
        {
            std::size_t lineEnd = content.find('\n', pos);
            const bool hasNewline = lineEnd != std::string::npos;
            if (!hasNewline)
                lineEnd = content.size();

            std::string_view line{content.data() + pos, lineEnd - pos};

            std::size_t first = 0;
            while (first < line.size() && (line[first] == ' ' || line[first] == '\t'))
                ++first;
            std::string_view trimmed = line.substr(first);
            if (!trimmed.empty() && trimmed.back() == '\r')
                trimmed = trimmed.substr(0, trimmed.size() - 1);

            bool remove = false;
            for (const auto& pat : overrides)
            {
                if (trimmed == pat)
                {
                    remove = true;
                    break;
                }
            }

            if (!remove)
            {
                filtered.append(line.data(), line.size());
                if (hasNewline)
                    filtered += '\n';
            }

            pos = lineEnd + (hasNewline ? 1 : 0);
        }

        if (!isMobile())
            return filtered;

        // Reduce indentation: each tab or group of 4 spaces → 2 spaces (leading only)
        std::string result;
        result.reserve(filtered.size());
        pos = 0;
        while (pos < filtered.size())
        {
            std::size_t lineEnd = filtered.find('\n', pos);
            const bool hasNewline = lineEnd != std::string::npos;
            if (!hasNewline)
                lineEnd = filtered.size();

            std::size_t i = pos;
            while (i < lineEnd)
            {
                if (filtered[i] == '\t')
                {
                    result += "  ";
                    ++i;
                }
                else if (
                    i + 3 < lineEnd && filtered[i] == ' ' && filtered[i + 1] == ' ' && filtered[i + 2] == ' ' &&
                    filtered[i + 3] == ' '
                )
                {
                    result += "  ";
                    i += 4;
                }
                else
                {
                    break;
                }
            }
            result.append(filtered.data() + i, lineEnd - i);
            if (hasNewline)
                result += '\n';

            pos = lineEnd + (hasNewline ? 1 : 0);
        }

        return result;
    }
    //---------------------------------------------------------------------------------------------------------------------
    std::string BasicExample::explanation() const
    {
        return {};
    }
    //---------------------------------------------------------------------------------------------------------------------
    Nui::ElementRenderer BasicExample::operator()()
    {
        using namespace Nui::Elements;
        using namespace Nui::Attributes;
        using Nui::Elements::div;

        // clang-format off
        return div{class_ = "example"}(
            h2{class_ = "example__heading"}(heading()),
            p{class_ = "example__explanation"}(explanation()),
            div{class_ = "example__body",
                "touchstart"_event = [this](Nui::val event) {
                    event.call<void>("stopPropagation");
                },
                "touchmove"_event = [this](Nui::val event) {
                    event.call<void>("stopPropagation");
                },
            }(
                div{class_ = "example__editor-section"}(
                    div{class_ = "example__tabs",
                    "mousedown"_event = [this](Nui::val event) {
                        event.call<void>("stopPropagation");
                    },
                }(
                        ScriptNuiComponents::button({
                            .text = "Header",
                            .attributes = {
                                onClick = [this](Nui::val) { activeTab_ = 0; }
                            },
                            .styleVariant = Nui::observe(activeTab_).generate(
                                std::function([](int active) -> ScriptNuiComponents::StyleVariant
                                {
                                    return active == 0 ? ScriptNuiComponents::StyleVariant::Primary
                                                       : ScriptNuiComponents::StyleVariant::Regular;
                                })
                            )
                        }),
                        ScriptNuiComponents::button({
                            .text = "Source",
                            .attributes = {
                                onClick = [this](Nui::val) { activeTab_ = 1; }
                            },
                            .styleVariant = Nui::observe(activeTab_).generate(
                                [](int active) -> ScriptNuiComponents::StyleVariant
                                {
                                    return active == 1 ? ScriptNuiComponents::StyleVariant::Primary
                                                       : ScriptNuiComponents::StyleVariant::Regular;
                                }
                            )

                        })
                    ),
                    div{}(
                        Nui::observe(activeTab_),
                        [this](int tab) -> Nui::ElementRenderer {
                            std::string content = preconditionContent((tab == 0) ? editorContentHeader() : editorContentSource());
                            return div{
                                class_ = "example__editor",
                                reference = [c = std::move(content)](auto&& weakElementPtr) {
                                    auto element = weakElementPtr.lock();
                                    if (!element)
                                        return;
                                    emscripten::val::global("createCodeMirror")(
                                        element->val(), emscripten::val{c}, emscripten::val{true}
                                    );
                                },
                                "mousedown"_event = [this](Nui::val event) {
                                    event.call<void>("stopPropagation");
                                },
                            }();
                        }
                    )
                ),
                div{class_ = "example__resizer"}(),
                div{class_ = "example__output",
                    "mousedown"_event = [this](Nui::val event) {
                        event.call<void>("stopPropagation");
                    },
                }(
                    render()
                )
            )
        );
        // clang-format on
    }
    // #####################################################################################################################
}
