#include <frontend/cards/list_card.hpp>

#include <nui/frontend/attributes.hpp>
#include <nui/frontend/components/table.hpp>
#include <nui/frontend/elements.hpp>

#include <string>
#include <vector>

namespace NuiPage
{
    // #####################################################################################################################
    namespace
    {
        static Nui::ElementRenderer renderImpl()
        {
            using namespace Nui;
            using namespace Nui::Elements;
            using namespace Nui::Attributes;
            using namespace Nui::Components;
            using Nui::Elements::span;
            using Nui::Elements::div; // because of the global div.

            thread_local Observed<std::vector<std::string>> names =
                std::vector<std::string>{"John", "Jane", "Joe", "Jill"};
            thread_local std::string name;

            // clang-format off
            return div{
                style = Style{
                    "display"_style = "flex",
                    "flex-direction"_style = "column",
                    "gap"_style = "5px",
                }
            }(
                div{
                    style = Style{
                        "display"_style = "flex",
                        "gap"_style = "5px",
                    }
                }(
                    input{
                        id = "attributeInput",
                        class_ = "form-control",
                        type = "text",
                        onInput = [](auto const& event) {
                            name = event["target"]["value"].template as<std::string>();
                        }
                    }(),
                    button{
                        onClick = [](){
                            names.push_back(name);
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
                        range(names),
                        [](long i, auto const& name) {
                            return tr{}(
                                td{}(
                                    button{
                                        onClick = [i](){
                                            names.erase(names.begin() + i);
                                        },
                                        class_ = "btn btn-danger"
                                    }("X")
                                ),
                                td{}(std::to_string(i)), 
                                td{}(name)
                            );
                        }
                    )
                )
            );
            // clang-format on
        }
    }
    // #####################################################################################################################
    struct ListCard::Implementation
    {};
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
            thread_local Observed<std::vector<std::string>> names =
                std::vector<std::string>{"John", "Jane", "Joe", "Jill"};
            thread_local std::string name;

            return div{
                style = Style{
                    "display"_style = "flex",
                    "flex-direction"_style = "column",
                    "gap"_style = "5px",
                }
            }(
                div{
                    style = Style{
                        "display"_style = "flex",
                        "gap"_style = "5px",
                    }
                }(
                    input{
                        id = "attributeInput",
                        class_ = "form-control",
                        type = "text",
                        onInput = [](auto const& event) {
                            name = event["target"]["value"].template as<std::string>();
                        }
                    }(),
                    button{
                        onClick = [](){
                            names.push_back(name);
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
                        range(names),
                        [](long i, auto const& name) {
                            return tr{}(
                                td{}(
                                    button{
                                        onClick = [i](){
                                            names.erase(names.begin() + i);
                                        },
                                        class_ = "btn btn-danger"
                                    }("X")
                                ),
                                td{}(std::to_string(i)), 
                                td{}(name)
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
               "Nui provides a simple way to display them using the range() expression. ";
    }
    //---------------------------------------------------------------------------------------------------------------------
    Nui::ElementRenderer ListCard::render() const
    {
        return renderImpl();
    }
    // #####################################################################################################################
}