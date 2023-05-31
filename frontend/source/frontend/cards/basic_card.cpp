#include <frontend/cards/basic_card.hpp>

#include <nui/frontend/attributes.hpp>
#include <nui/frontend/elements.hpp>

#include <algorithm>
#include <deque>

namespace NuiPage
{
    // #####################################################################################################################
    Nui::ElementRenderer BasicCard::operator()() const
    {
        using namespace Nui;
        using namespace Nui::Elements;
        using namespace Nui::Attributes;
        using Nui::Elements::span;
        using Nui::Elements::div; // because of the global div.

        // clang-format off
        return div{
            class_ = "card",
            reference = [](auto&& weakElementPtr){                
                auto element = weakElementPtr.lock();
                if (!element)
                    return;

                emscripten::val::global("setupCardFlyin")(element->val());
            }
        }(
            div{}
            (
                div{
                    class_ = "card-header"
                }(
                    h2{
                        class_ = "card-title"
                    }(
                        header()
                    ),
                    p{
                        class_ = "card-subtitle"
                    }(
                        description()
                    )
                ),
                div{
                    class_ = "card-body"
                }(
                    div{
                        class_ = "card-source",
                        reference = [weak = weak_from_this()](auto&& weakElementPtr){
                            auto element = weakElementPtr.lock();
                            if (!element)
                                return;
                            auto self = weak.lock();
                            if (!self)
                                return;

                            emscripten::val::global("createCodeMirror")(element->val(), emscripten::val{self->source()}, emscripten::val{true});
                        }
                    }(),
                    // what the source generates
                    div{
                        class_ = "card-content"
                    }(
                        render()
                    )
                )
            )
        );
        // clang-format on
    }
    //---------------------------------------------------------------------------------------------------------------------
    std::string BasicCard::removeIndentation(std::string const& str)
    {
        std::string result;
        result.reserve(str.size() / 2);

        std::deque<std::string> lines;
        std::istringstream iss(str);
        std::string line;
        while (std::getline(iss, line))
        {
            lines.push_back(line);
        }

        if (lines.empty())
            return "No Source Code Found!";

        auto trimLeft = [](std::string& s) {
            s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
                        return !std::isspace(ch);
                    }));
        };

        // Remove all empty lines at the beginning:
        do
        {
            trimLeft(lines.front());
            if (lines.front().empty())
                lines.pop_front();
        } while (lines.front().empty() && !lines.empty());

        // Get indentation of first line, respecting tabs and spaces:
        int indentation = 0;
        for (auto const& c : lines.front())
        {
            if (c == ' ')
                indentation++;
            else if (c == '\t')
                indentation += 4;
            else
                break;
        }

        // Remove indentation from all lines, respecting tabs and spaces:
        for (auto& line : lines)
        {
            if (line.size() < indentation)
            {
                line.clear();
                continue;
            }

            int toErase = 0;
            for (auto const& c : line)
            {
                if (c == ' ')
                {
                    toErase++;
                    if (toErase == indentation)
                        break;
                }
                else if (c == '\t')
                {
                    toErase += 4;
                    if (toErase == indentation)
                        break;
                }
                else
                    break;
            }

            line.erase(0, toErase);
        }

        // Concat all lines:
        for (auto const& line : lines)
        {
            result += line;
            result += '\n';
        }

        return result;
    }
    // #####################################################################################################################
}