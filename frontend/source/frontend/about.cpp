#include <frontend/about.hpp>

#include <nui/frontend/attributes.hpp>
#include <nui/frontend/elements.hpp>

MAKE_HTML_VALUE_ATTRIBUTE_RENAME(data_github, "data-github")
MAKE_HTML_VALUE_ATTRIBUTE_RENAME(data_width, "data-width")
MAKE_HTML_VALUE_ATTRIBUTE_RENAME(data_height, "data-height")
MAKE_HTML_VALUE_ATTRIBUTE_RENAME(data_theme, "data-theme")

namespace NuiPage
{
    // #####################################################################################################################
    struct AboutPage::Implementation
    {};
    // #####################################################################################################################
    AboutPage::AboutPage()
        : impl_{std::make_unique<Implementation>()}
    {}
    //---------------------------------------------------------------------------------------------------------------------
    AboutPage::~AboutPage() = default;
    //---------------------------------------------------------------------------------------------------------------------
    AboutPage::AboutPage(AboutPage&&) = default;
    //---------------------------------------------------------------------------------------------------------------------
    AboutPage& AboutPage::operator=(AboutPage&&) = default;
    //---------------------------------------------------------------------------------------------------------------------
    Nui::ElementRenderer AboutPage::operator()()
    {
        using namespace Nui;
        using namespace Nui::Elements;
        using namespace Nui::Attributes;
        using Nui::Elements::div; // because of the global div.

        // clang-format off
        return div{id = "aboutPage"}(
            div{class_ = "about-section"}(
                h1{}("About Nui"),
                p{}("The Nui project is free and fully open source and available on GitHub."),
                p{}("Contributions are welcome!")
            ),
            h2{style = "text-align:center"}("Core Contributors"),
            div{class_ = "about-row"}(
                div{class_ = "about-column"}(
                    div{class_ = "about-card"}(
                        a{
                            href = "https://github.com/5cript"
                        }(
                            img{
                                class_ = "about-contributor-image",
                                src = "https://avatars.githubusercontent.com/u/6238896?v=4", 
                                alt = "Tim"
                            }()
                        ),
                        div{class_ = "container"}(
                            h2{}("Tim Ebbeke"),
                            p{class_ = "about-title"}("Lead Developer"),
                            p{}("Nui Creator and Lead Developer"),
                            p{}("tim06tr@gmail.com")
                        )
                    )
                )
            ),
            div{class_ = "about-section"}(
                h2{style = "text-align:center"}("Special Thanks to All Further Contributors"),
                p{}(
                    a{href = "https://github.com/NuiCpp/Nui/graphs/contributors?from=2022-07-17&to=2023-05-31&type=a"}(
                        "See all contributors"
                    )
                )
            )
        );
        // clang-format on
    }
    // #####################################################################################################################
}