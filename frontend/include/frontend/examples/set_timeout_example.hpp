#pragma once

#include <frontend/examples/basic_example.hpp>

namespace NuiPage
{
    class SetTimeoutExample : public BasicExample
    {
      protected:
        std::string heading() const override;
        std::string explanation() const override;
        std::string editorContentHeader() const override;
        std::string editorContentSource() const override;
        Nui::ElementRenderer render() override;

      private:
        Nui::Observed<std::string> status_{"Press the button."};
    };
}
