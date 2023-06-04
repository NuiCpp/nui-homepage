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
            div{}(
                h1{style = "text-align:center"}("About Nui"),
                p{style = "text-align:center"}("The Nui project is free and fully open source and available on GitHub."),
                p{style = "text-align:center"}("Contributions are welcome!")
            ),  
            section{class_ = "card_about-list"}(
                article{class_ = "card_about"}(
                    header{class_ = "card_about-header"}(
                        h2{}("Core Contributor")
                    ),
                    div{class_ = "card_about-author"}(
                        a{class_ = "author-avatar", href="https://github.com/5cript"}(
                            img{src = "https://avatars.githubusercontent.com/u/6238896?v=4"}()
                        ),
                        img{class_ = "half-circle", src="./assets/halfcircle.svg"}(),
                        div{class_ = "author-name"}(
                            div{class_ = "author-name-prefix"}("Nui Creator and Lead Developer"),
                            div{class_ = "author-name"}("Tim Ebbeke")
                        )
                    ),
                    div{class_ = "tags"}(
                        a{href = "https://github.com/5cript"}("github"),
                        a{href = "mailto:tim06tr@gmail.com"}("tim06tr@gmail.com")
                    )
                )
            ),
            div{style = "text-align:center"}(
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