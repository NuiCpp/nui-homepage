#include <frontend/cards/basic_card.hpp>

#include <nui/frontend/attributes.hpp>
#include <nui/frontend/elements.hpp>

#include <algorithm>

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
            class_ = "card"
        }(
            Nui::Dom::reference([](auto&& weakElementPtr){                
                auto element = weakElementPtr.lock();
                if (!element)
                    return;

                emscripten::val::global("setupCardFlyin")(element->val());
            }),
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
                        class_ = "card-source"
                    }(
                        Nui::Dom::reference([weak = weak_from_this()](auto&& weakElementPtr){
                            auto element = weakElementPtr.lock();
                            if (!element)
                                return;
                            auto self = weak.lock();
                            if (!self)
                                return;

                            emscripten::val::global("createCodeMirror")(element->val(), emscripten::val{self->source()}, emscripten::val{true});
                        })
                    ),
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

        auto firstNonWhitespace = str.find_first_not_of(" \t\r\n");
        if (firstNonWhitespace == std::string::npos)
            return result;

        auto iterToFirstNonEmptyLine = std::find(str.rbegin() + (str.size() - firstNonWhitespace), str.rend(), '\n');

        auto firstNonEmptyLine = iterToFirstNonEmptyLine.base();
        auto firstNonEmptyLineIndentation = std::distance(firstNonEmptyLine, std::begin(str) + firstNonWhitespace);

        auto next = std::find(firstNonEmptyLine, std::end(str), '\n');
        auto begin = firstNonEmptyLine;
        while (begin < std::end(str))
        {
            std::string line{begin, next};

            if (line.size() <= firstNonEmptyLineIndentation)
            {
                result += '\n';
                begin = next + 1;
                next = std::find(begin, std::end(str), '\n');
                continue;
            }
            line.erase(std::begin(line), std::begin(line) + firstNonEmptyLineIndentation);

            result += line;
            result += '\n';

            begin = next + 1;
            next = std::find(begin, std::end(str), '\n');
        }
        while (result.back() == '\n')
            result.pop_back();
        return result;
    }
    // #####################################################################################################################
}