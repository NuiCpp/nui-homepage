#include <frontend/basic_card.hpp>

#include <algorithm>

namespace NuiPage
{
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
}