#include <frontend/examples/range_table.hpp>

#include <ui5-sap-icons/icons/delete.hpp>

#include <nui/frontend/attributes.hpp>
#include <nui/frontend/elements.hpp>
#include <nui/frontend/elements/table.hpp>
#include <nui/frontend/api/mouse_event.hpp>

#include <fmt/format.h>

namespace NuiPage
{
    Nui::ElementRenderer RangeTable::tableRow(Entry const& entry)
    {
        using namespace Nui::Elements;
        using namespace Nui::Attributes;

        return tr{}(
            td{}(entry.name),
            td{}(entry.score),
            td{}(button{
                class_ = "script-nui-button",
                // Comes from ScriptNuiComponents, will move to nui components at some point.
                "data-variant"_attr = "danger",
                // Capture the stable id, not the index: indices
                // shift on deletion but the id never changes.
                onClick = [this, id = entry.id](Nui::WebApi::MouseEvent)
                {
                    auto& rows = rows_;

                    // ids are assigned in ascending order so the vector stays
                    // sorted — binary search is O(log n) instead of O(n).
                    const auto it = std::lower_bound(
                        rows->begin(), // -> untracked access to value
                        rows->end(), // -> untracked access to value
                        id,
                        [](const Entry& e, std::size_t v)
                        {
                            return e.id < v;
                        }
                    );

                    if (it != rows->end() && it->id == id) // -> untracked access to value
                        rows.erase(it); // -> TRACKED access to value
                },
            }(Ui5Icons::delete_()))
        );
    }

    Nui::ElementRenderer RangeTable::render()
    {
        using namespace Nui::Elements;
        using namespace Nui::Attributes;
        using Nui::Elements::div;

        const auto onAdd = [this]()
        {
            if (inputName_.empty())
                return;
            rows_.emplace_back(Entry{nextId_++, inputName_, inputScore_});
        };

        // clang-format off
        return div{class_ = "range-table"}(
            div{class_ = "range-table__form"}(
                input{
                    class_ = "script-nui-text-input",
                    type = "text",
                    placeHolder = "Name",
                    onInput = [this](auto const& event) {
                        inputName_ = event["target"]["value"].template as<std::string>();
                    },
                }(),
                input{
                    class_ = "script-nui-text-input",
                    type = "text",
                    placeHolder = "Score",
                    onInput = [this](auto const& event) {
                        inputScore_ = event["target"]["value"].template as<std::string>();
                    },
                }(),
                button{
                    class_ = "script-nui-button",
                    onClick = onAdd,
                }("Add")
            ),
            table{class_ = "range-table__table"}(
                thead{}(
                    tr{}(
                        th{}("Name"),
                        th{}("Score"),
                        th{}("")
                    )
                ),
                tbody{}(
                    // Observed<vector<T>> tracks insertions and deletions only
                    // affected rows_ are added/removed from the DOM.
                    range(rows_),
                    [this](long long /*i*/, auto const& entry)
                    {
                        return tableRow(entry);
                    }
                )
            )
        );
        // clang-format on
    }
}
