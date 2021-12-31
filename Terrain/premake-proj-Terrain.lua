  project "Terrain"
    kind "ConsoleApp"
    targetdir ("%{wks.location}/build/%{prj.name}-%{cfg.buildcfg}")
    objdir ("%{wks.location}/build/intermediate/%{prj.name}-%{cfg.buildcfg}")
    systemversion "latest"
    language "C++"
    cppdialect "C++17"
    
    files 
    {
      "src/**.h",
      "src/**.cpp",
    }
    
    includedirs
    {
      "../DgEngine/src",
      "../DgEngine/Vendor/spdlog/include",
      "../DgEngine/Vendor/DgLib/src"
    }
    
    links
    {
      "DgEngine",
      "DgLib",
      "Glad",
      "../DgEngine/Vendor/freetype2/lib/x64/freetype.lib",
      "../DgEngine/Vendor/SDL2/lib/x64/SDL2.lib",
      "../DgEngine/Vendor/SDL2/lib/x64/SDL2main.lib"
    }
    
    postbuildcommands 
    {
      "{COPY} ../DgEngine/Vendor/SDL2/lib/x64/SDL2.dll %{cfg.targetdir}",
      "{COPY} ../DgEngine/Vendor/FreeType2/lib/x64/freetype.dll %{cfg.targetdir}"
    }
    
    filter "configurations:Debug"
      defines "DGE_DEBUG"
      runtime "Debug"
      symbols "on"

    filter "configurations:Release"
      defines "DGE_RELEASE"
      runtime "Release"
      optimize "on"