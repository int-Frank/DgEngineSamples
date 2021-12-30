import subprocess
import sys
sys.path.insert(0, 'DgEngine\\Vendor\\BuildScripts')

import DgBuild

DgBuild.Make_vpaths("DgEngine/Vendor/DgLib/src/", "DgEngine/Vendor/DgLib/DgLib_vpaths.lua")
DgBuild.Make_vpaths("DgEngine/src/", "DgEngine/DgEngine_vpaths.lua")

subprocess.call("DgEngine/Vendor/DgLib/3rdParty/premake/premake5.exe vs2022")
