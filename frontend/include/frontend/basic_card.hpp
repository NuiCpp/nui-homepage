#pragma once

#include <string>

namespace NuiPage
{
    class BasicCard
    {
      protected:
        static std::string removeIndentation(std::string const& str);
    };
}