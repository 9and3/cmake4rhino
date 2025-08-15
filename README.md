<!-- <p align="center">
  <img src="~logo/logo_4html.svg" width="600" alt="CMake4Rhino Logo" style="margin-bottom:0;">
  <br>
  <img src="~logo/logo_title_code.svg" width="300">
</p> -->


# cmake4rhino

This is a [CMake](https://cmake.org/) template for [Rhino plugins](https://developer.rhino3d.com/guides/cpp/), to quickly set up a new C++ project.

The template is distributed as a [cookiecutter](https://github.com/cookiecutter/cookiecutter) template, which can be used to generate a new project with the desired name and settings. Have fun cmakers!

<p align="center">
  <img src="assets/record_exp.gif" width="700" alt="Install Lgif" style="margin-bottom:0;">
</p>


<br>

##### Supported Toolchains & Platforms:

<table width="100%">
  <tr style="background-color:#f6f8fa;">
    <th>OS</th>
    <th>Generator / Compiler</th>
    <th>Rhino SDK</th>
    <th>CMake</th>
  </tr>
  <tr>
    <td style="text-align:center;">
    <img src="https://cdn.jsdelivr.net/gh/devicons/devicon/icons/windows8/windows8-original.svg" width="18" style="vertical-align:middle; margin-left:4px;"/>
    Windows
    </td>
    <td style="text-align:center;">Visual Studio 16 2019 <img src="https://img.shields.io/badge/-not%20tested-orange?style=for-the-badg&logo=visualstudiocode&logoColor=white"/> <br> Visual Studio 17 2022 <img src="https://img.shields.io/badge/-tested-brightgreen?style=for-the-badg&logo=visualstudiocode&logoColor=white"/></td>
    <td style="text-align:center;">Rhino 6 <img src="https://img.shields.io/badge/-not%20supported-red?style=for-the-badg"/> <br> Rhino 7 <img src="https://img.shields.io/badge/-not%20tested-orange?style=for-the-badg"/> <br> Rhino 8 <img src="https://img.shields.io/badge/-tested-brightgreen?style=for-the-badg"/></td>
    <td style="text-align:center;">3.15+ <img src="https://img.shields.io/badge/-tested-brightgreen?style=for-the-badg"/></td>
  </tr>
</table>

##### CI status:

<table width="100%">
  <tr style="background-color:#f6f8fa;">
    <th>Name</th>
    <th>Build Status</th>
    <th>Branch</th>
    <th>Notes</th>
  </tr>
  <tr>
    <td style="text-align:center;">Downloadable Template</td>
    <td style="text-align:center;">
      <a href="https://github.com/9and3/cmake4rhino/actions/workflows/build_cookietemplate.yml">
        <img src="https://github.com/9and3/cmake4rhino/actions/workflows/build_cookietemplate.yml/badge.svg">
      </a>
    </td>
    <td style="text-align:center;">
      <a href="https://github.com/9and3/cmake4rhino/tree/cookietemplate">cookietemplate</a>
    </td>
    <td style="text-align:center;">
      <code>cookiecutter gh:9and3/cmake4rhino --checkout cookietemplate</code>
    </td>
  </tr>
  <tr>
    <td style="text-align:center;">CMake/VS17-2022/Rhino8SDK build</td>
    <td style="text-align:center;">
      <a href="https://github.com/9and3/cmake4rhino/actions/workflows/build_cmake.yml">
        <img src="https://github.com/9and3/cmake4rhino/actions/workflows/build_cmake.yml/badge.svg">
      </a>
    </td>
    <td style="text-align:center;">
      <a href="https://github.com/9and3/cmake4rhino/tree/Main">Main</a>
    </td>
    <td style="text-align:center;">
      <code>..</code>
    </td>
  </tr>
</table>

<br>

## Quickstart

### Download the template

You can download the template with the following command in a terminal:

```bash
pip install cookiecutter
cookiecutter gh:9and3/cmake4rhino --checkout cookietemplate
```
When asked, change the project name with your plug-in name.

### Project information
The remaining information to change can be found in the `CMakeLists.txt` file to be filled with your project information, such as the name, version, author, etc:

https://github.com/9and3/cmake4rhino/blob/5d0722a11a8476ff51b25dceda3b8a25a282155d/CMakeLists.txt#L20-L31

### Logo
The logo should be replaced in the `res/` folder with your own (remember 256-pixel square `.ico` file).

### Compile

Check-in your folder:
```bash
cd <your-genereated-project-folder>
```
For debug build
```bash
cmake -S . -B build -G "Visual Studio 17 2022" -A x64 -DRHINO_DEBUG_PLUGIN=ON; cmake --build build --config Debug
```

```bash
cmake -S . -B build -G "Visual Studio 17 2022" -A x64 -DRHINO_DEBUG_PLUGIN=ON; cmake --build build --config Release
```

Important flags:
- `-DMFC_ROOT=<path_to_mfc>`: Path to the MFC library, if not set it will try to find it in the default location.
- `-DRHINOSDK_ROOT=<path_to_rhino8_sdk>`: Path to the Rhino 8 SDK, if not set it will try to find it in the default location.
- `-DRHINO_EXE_PATH=<path_to_rhino_exe>`: Path to the Rhino executable, if not set it will try to find it in the default location.
- `-DRUN_POSTBUILD_RHINO=ON`: Enable to automatically open RHino and install the plugin after building.

### Testing
 
> [!IMPORTANT]  
> Be sure to install by drag-and-drop the `build/Release/YourPlugin.rhp` file into the Rhino window before to run the tests. After this, the tests, if enabled, will work every time.

Googletest framework is used, tests can be enabled with `-DBUILD_TESTS=ON` (default: off).
You can write either unit tests or test your commands:
```cpp
TEST_F(RhinoDocTest, MyIntegrationTest) {
    // macro
    const wchar_t* cmdName = 
        L"!_cmake4rhino "
        L"\"test\" "
        L"_Enter";

    // run the command
    bool resCmd = pDoc->RunScript(cmdName);

    // get the objects added to the document
    ON_SimpleArray<ON_UUID> objectIDs = GetObjectIDs();

    ASSERT_TRUE(resCmd) << "Command execution failed";
    ASSERT_EQ(objectIDs.Count(), 2) << "No sphere and curve found in the document";
}
```
You can run your command as a macro and read and evaluate the generated geometries as in the example.

> [!WARNING]  
> Note that it's not possible to test UI but only command interface and geometries.

### How it works

<table>
  <tr>
    <td width="420">
      <img src="assets/diagramrhptest.png" width="400" alt="diagramw">
    </td>
    <td> 
      The cmake project compilation is split in 3 parts:<br>
      <ul>
        <li><code>PLUGIN_CORE</code>: your external library</li>
        <li><code>PLUGIN_RHP</code>: the Rhino plugin itself</li>
        <li><code>PLUGIN_TEST</code>: where your tests live</li>
      </ul>
      Basically, Rhino is linked two times with different flags based on the <code>.rhp</code> compilation or the test part which is a console exec. For this last one we also add the <code>Rhino.Inside.Cpp</code> ([here](https://github.com/mcneel/rhino-developer-samples/blob/8/rhino.inside/cpp/Main.cpp#L7)) headers which allows to run headless instances of Rhino.
    </td>
  </tr>
</table>

### Contributions

Contributions to the project are welcome! If you have suggestions, improvements, or bug fixes, please submit a pull request or open an issue.
