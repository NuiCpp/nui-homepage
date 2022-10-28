include(FetchContent)
FetchContent_Declare(
	nui
	GIT_REPOSITORY https://github.com/NuiCpp/Nui.git
	GIT_TAG        7fb8c4bc9f1b18da1db4f3d3d200a8f581555cd7    
)
FetchContent_MakeAvailable(nui)