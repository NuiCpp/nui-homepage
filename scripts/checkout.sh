#!/bin/env bash

# This script is used to checkout the latest version of the code and update the submodules.

NUI_VERSION="v3.2.0"
NUI_COMPONENTS_COMMIT="26145a440f7f1c829397e6cf26d938e23b81c687"

mkdir -p dependencies
cd dependencies

# Nui
if [ -d "Nui" ]; then
    echo "Updating Nui..."
    git -C Nui fetch --tags
    git -C Nui checkout "$NUI_VERSION"
else
    echo "Cloning Nui..."
    git clone https://github.com/NuiCpp/Nui.git
    git -C Nui checkout "$NUI_VERSION"
fi

# 5cript-nui-components
if [ -d "5cript-nui-components" ]; then
    echo "Updating 5cript-nui-components..."
    git -C 5cript-nui-components fetch
    git -C 5cript-nui-components checkout "$NUI_COMPONENTS_COMMIT"
    git -C 5cript-nui-components submodule update --init --recursive
else
    echo "Cloning 5cript-nui-components..."
    git clone https://github.com/5cript/5cript-nui-components.git
    git -C 5cript-nui-components checkout "$NUI_COMPONENTS_COMMIT"
    git -C 5cript-nui-components submodule update --init --recursive
fi