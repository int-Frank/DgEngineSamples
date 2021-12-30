workspace "DgEngineSamples"
  architecture "x64"
  
  configurations
  {
    "Debug",
    "Release"
  }

  include("Demo/premake-proj-Demo.lua")
  include("DgEngine/premake-proj-DgEngine.lua")
  include("DgEngine/Vendor/DgLib/premake-proj-DgLib.lua")