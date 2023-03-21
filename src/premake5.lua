
baseName = path.getbasename(os.getcwd());

project (workspaceName)
    kind "ConsoleApp"
    location "../src"
    targetdir "../_bin/%{cfg.buildcfg}"

    filter "action:vs*"
        debugdir "$(SolutionDir)"
		
	filter {"action:vs*", "configurations:Release"}
		kind "WindowedApp"
		entrypoint "mainCRTStartup"
		
    filter{}

    vpaths 
    {
        ["Header Files/*"] = {"**.h", "**.hpp"},
        ["Source Files/*"] = {"**.c", "**.cpp"},
    }
    files {"**.c", "**.cpp", "**.h", "**.hpp"}
  
    includedirs {"./"}
	includedirs {"../include"}
    link_raylib();
	
	-- To link to a lib use link_to("LIB_FOLDER_NAME")