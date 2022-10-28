# nui-template
A template repository to base new projects off of.
This is a template for projects using Nui https://github.com/NuiCpp/Nui.

## Transform into your own project:
Rename the project "nui-template" in your cmake file to what your project is called.

## Dependencies
You need the following things installed to get going.
- clang 14 oder higher.
- npm (available from the environment variable PATH)
- boost
- libcurl
- crypto++
- binaryen
### Windows
Currently only the msys2 environemt is supported: https://www.msys2.org/
Install it and use the CLANG64 environment to get going.
You can install the dependencies in the CLANG64 terminal like so (except for npm):
`pacman -S mingw-w64-clang-x86_64-clang mingw-w64-clang-x86_64-boost mingw-w64-clang-x86_64-curl mingw-w64-clang-x86_64-crypto++ mingw-w64-clang-x86_64-binaryen`
### Linux 
Install gtk+-3.0 and webkit2gtk-4.0 for webview, more information here: https://github.com/webview/webview