#include <frontend/cards/list_card.hpp>

#include <nui/frontend/attributes.hpp>
#include <nui/frontend/components/table.hpp>
#include <nui/frontend/elements.hpp>
#include <nui/frontend/api/mouse_event.hpp>

#include <fmt/format.h>

#include <string>
#include <vector>

namespace NuiPage
{
    // #####################################################################################################################
    struct ListCard::Implementation
    {
        std::size_t increasing{4};
        Nui::Observed<std::vector<std::pair<std::size_t, std::string>>> names{
            std::vector<std::pair<std::size_t, std::string>>{{0, "John"}, {1, "Jane"}, {2, "Joe"}, {3, "Jill"}}
        };
        std::string name;
    };
    //---------------------------------------------------------------------------------------------------------------------
    ListCard::ListCard()
        : impl_(std::make_unique<Implementation>())
    {}
    //---------------------------------------------------------------------------------------------------------------------
    ListCard::~ListCard() = default;
    //---------------------------------------------------------------------------------------------------------------------
    ListCard::ListCard(ListCard&&) = default;
    //---------------------------------------------------------------------------------------------------------------------
    ListCard& ListCard::operator=(ListCard&&) = default;
    //---------------------------------------------------------------------------------------------------------------------
    std::string ListCard::source() const
    {
        return removeIndentation(R"(
            return div{
                style = fmt::format(
                    "display: {}; flex-direction: {}; gap: {}",
                    "flex", "column", "5px"
                )
            }(
                div{
                    style = fmt::format(
                        "display: {}; gap: {}",
                        "flex", "5px"
                    )
                }(
                    input{
                        id = "attributeInput",
                        class_ = "form-control",
                        type = "text",
                        onInput = [this](auto const& event) {
                            impl_->name = event["target"]["value"].template as<std::string>();
                        }
                    }(),
                    button{
                        onClick = [this](){
                            impl_->names.emplace_back(++impl_->increasing, impl_->name);
                        },
                        class_ = "btn btn-primary"
                    }("Add Name")
                ),
                table{}(
                    thead{}(
                        tr{}(
                            th{}(""),
                            th{}("Number"),
                            th{}("Name")
                        )
                    ),
                    tbody{}(
                        // range indicates that the following ElementRenderer
                        // is to be rendered for each item.
                        range(impl_->names),
                        [this](long long i, auto const& name) {
                            return tr{}(
                                td{}(
                                    button{
                                        onClick = [this, id = name.first](Nui::WebApi::MouseEvent event){
                                            // get the iter of the button that was clicked
                                            const auto iter = std::lower_bound(impl_->names.value().begin(), impl_->names.value().end(), std::make_pair(id, std::string{}),
                                                [](auto const& a, auto const& b){
                                                    return a.first < b.first;
                                                });
                                            if (iter != impl_->names.value().end() && iter->first == id)
                                                impl_->names.erase(iter);
                                        },
                                        class_ = "btn btn-danger"
                                    }("X")
                                ),
                                td{}(std::to_string(i)),
                                td{}(name.second)
                            );
                        }
                    )
                )
            );
        )");
    }
    //---------------------------------------------------------------------------------------------------------------------
    std::string ListCard::header() const
    {
        return "Lists and Tables";
    }
    //---------------------------------------------------------------------------------------------------------------------
    std::string ListCard::description() const
    {
        return "Lists and tables are a very common use case for web applications. "
               "Nui provides a simple way to display them using the range() expression. "
               "Note that the number column starts to be incorrect when items are removed. "
               "This example intentionally shows that this is the case to demonstrate that the view is not re-rendered "
               "from scratch on every update, but only the necessary changes are made. ";
    }
    //---------------------------------------------------------------------------------------------------------------------
    Nui::ElementRenderer ListCard::render()
    {
        using namespace Nui;
        using namespace Nui::Elements;
        using namespace Nui::Attributes;
        using namespace Nui::Components;
        using Nui::Elements::span;
        using Nui::Elements::div; // because of the global div.

        // clang-format off
        return div{
            style = fmt::format(
                "display: {}; flex-direction: {}; gap: {}",
                "flex", "column", "5px"
            )
        }(
            div{
                style = fmt::format(
                    "display: {}; gap: {}",
                    "flex", "5px"
                )
            }(
                input{
                    id = "attributeInput",
                    class_ = "form-control",
                    type = "text",
                    onInput = [this](auto const& event) {
                        impl_->name = event["target"]["value"].template as<std::string>();
                    }
                }(),
                button{
                    onClick = [this](){
                        impl_->names.emplace_back(++impl_->increasing, impl_->name);
                    },
                    class_ = "btn btn-primary"
                }("Add Name")
            ),
            table{}(
                thead{}(
                    tr{}(
                        th{}(""),
                        th{}("Number"),
                        th{}("Name")
                    )
                ),
                tbody{}(
                    // range indicates that the following ElementRenderer
                    // is to be rendered for each item.
                    range(impl_->names),
                    [this](long long i, auto const& name) {
                        return tr{}(
                            td{}(
                                button{
                                    onClick = [this, id = name.first](Nui::WebApi::MouseEvent event){
                                        // get the iter of the button that was clicked
                                        const auto iter = std::lower_bound(impl_->names.value().begin(), impl_->names.value().end(), std::make_pair(id, std::string{}),
                                            [](auto const& a, auto const& b){
                                                return a.first < b.first;
                                            });
                                        if (iter != impl_->names.value().end() && iter->first == id)
                                            impl_->names.erase(iter);
                                    },
                                    class_ = "btn btn-danger"
                                }("X")
                            ),
                            td{}(std::to_string(i)),
                            td{}(name.second)
                        );
                    }
                )
            )
        );
        // clang-format on
    }
    // #####################################################################################################################
}