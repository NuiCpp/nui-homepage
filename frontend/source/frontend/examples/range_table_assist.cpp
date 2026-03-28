#include <frontend/examples/range_table.hpp>

namespace NuiPage
{
    std::string RangeTable::heading() const
    {
        return "Range Table";
    }

    std::string RangeTable::explanation() const
    {
        return "Observed<vector<T>> (or Observed<deque<T>>) tracks insertions and deletions so that Nui::range()"
               "patches only the affected DOM rows, the rest are left untouched. Rows are deleted by stable id rather "
               "than index, because indices shift when an earlier row is removed but the id never changes. A range can "
               "also be std::unordered_map, std::map, std::set, std::list, but those are not optimized and do full "
               "range rerenders, keep that in mind.";
    }

    std::string RangeTable::editorContentHeader() const
    {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc23-extensions"
        return
        {
#embed "../../../include/frontend/examples/range_table.hpp"
        };
#pragma clang diagnostic pop
    }

    std::string RangeTable::editorContentSource() const
    {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc23-extensions"
        return
        {
#embed "range_table.cpp"
        };
#pragma clang diagnostic pop
    }
}
