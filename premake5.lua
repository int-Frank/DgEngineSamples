workspace "DgEngineSamples"
  architecture "x64"
  
  configurations
  {
    "Debug",
    "Release"
  }

  group("Samples")
    include("Demo/premake-proj-Demo.lua")
    include("Terrain/premake-proj-Terrain.lua")
  group("")
  
  include("DgEngine/premake-proj-DgEngine.lua")
  include("DgEngine/Vendor/DgLib/premake-proj-DgLib.lua")