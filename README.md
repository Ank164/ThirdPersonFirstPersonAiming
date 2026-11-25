# Third Person First Person Aiming for Skyrim 1.7.104

This SKSE plugin adds Skyrim 1.7.104 support for [Third Person First Person Aiming](https://www.nexusmods.com/skyrimspecialedition/mods/84587) by Zzyxzz. It targets Skyrim Steam 1.7.104.0, SKSE 2.3.1, and the matching Address Library.

## Install

Install the original mod and its requirements. Install the DLL archive from GitHub Releases in MO2 and place it after the original mod in the left pane so its `SKSE/Plugins/ThirdPersonFirstPersonAiming.dll` wins. The original mod supplies the ESL, compiled Papyrus scripts, and MCM files.

The DLL registers the same three native Papyrus functions. It preserves the original third-person zoom handling and the spell delivery value returned for a missing spell.

## Build

The source requires MSVC, CMake 3.28 or later, and x64 CommonLibSSE-NG and DirectXTK packages. The CommonLibSSE package must support Skyrim 1.7 and Address Library format 5. Use packages built with the static MSVC runtime. Configure from this source directory with the installed dependency prefix.

```powershell
cmake -S . -B build -G "Visual Studio 18 2026" -A x64 "-DCMAKE_PREFIX_PATH=C:/path/to/x64-windows-static" -DCMAKE_HAVE_LIBC_PTHREAD=FALSE -DCMAKE_HAVE_PTHREADS_CREATE=FALSE -DCMAKE_HAVE_PTHREAD_CREATE=FALSE
cmake --build build --config Release
cmake --install build --config Release --prefix dist
```
