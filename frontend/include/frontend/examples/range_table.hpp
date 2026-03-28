#pragma once

#include <frontend/examples/basic_example.hpp>
#include <nui/frontend/api/console.hpp>

#include <string>
#include <vector>

namespace NuiPage
{
    class RangeTable : public BasicExample
    {
      protected:
        std::string heading() const override;
        std::string explanation() const override;
        std::string editorContentHeader() const override;
        std::string editorContentSource() const override;
        Nui::ElementRenderer render() override;

      private:
        struct Entry
        {
            std::size_t id;
            std::string name;
            std::string score;
        };

        Nui::ElementRenderer tableRow(Entry const& entry);

      private:
        Nui::Observed<std::vector<Entry>> rows_{
            std::vector<Entry>{{0, "Alice", "42"}, {1, "Bob", "87"}, {2, "Carol", "61"}}
        };
        std::string inputName_;
        std::string inputScore_;
        std::size_t nextId_{3};
    };
}
