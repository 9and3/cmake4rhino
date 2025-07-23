
<p align="center">
    <img src="~logo/logo_txt_900.png" width="300">
</p>
<!-- <p align="center">
    <img src="https://github.com/ibois-epfl/augmented-carpentry/actions/workflows/docker-ubuntu-build.yml/badge.svg">
    <img src="https://github.com/ibois-epfl/augmented-carpentry/actions/workflows/docker-ubuntu-build-and-test.yml/badge.svg">
    <img src="https://github.com/ibois-epfl/augmented-carpentry/actions/workflows/gh-build.yml/badge.svg">
</p> -->

## Content

## Quickstart





### Resources:

-- https://discourse.mcneel.com/t/cmakelists-rhino-plugin-c/144188/16 thread for cmake in rhino

- MFC is needded to be isntalled via Visual Studio Installer
### to build:

for debug build:
```bash
❯ cmake -S . -B build -G "Visual Studio 17 2022" -A x64 -DRHINO_DEBUG_PLUGIN=ON; cmake --build build --config Debug
```

```bash
❯ Remove-Item --Recurse -Force build; cmake -S . -B build -G "Visual Studio 17 2022" -A x64; cmake --build build --config Release
```

Notes:
- `RHINO8SDK_PATH` can be set to the path of the Rhino SDK, or it will try to find it in the default location.
- It supports Rhino 8 and 7 SDK.
- Specify the the config Debug or Release needss to be eexplicitly set in `cmake --build build --config Debug` or `cmake --build build --config Release`.

### todo:
- [ ] test CI
- [ ] do the coockiecutter
