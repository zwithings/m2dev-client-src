# Python 3.14 Library Setup

## Required File
- `python314.lib` - Python 3.14 linker library for Windows x64

## Obtaining the Library

### Option 1: From Official Python 3.14 Installation (Recommended)
1. Install Python 3.14 from [python.org](https://www.python.org/downloads/release/python-3142/)
2. Choose installation for Windows x64
3. Find `python314.lib` at:
   - `C:\Users\[User]\AppData\Local\Programs\Python\Python314\libs\python314.lib`
   - or `C:\Python314\libs\python314.lib`
4. Copy the file to this directory

### Option 2: Build from Source (Full Control)
Building from source is recommended for production use as it allows matching compiler settings with the client build.

#### Prerequisites
- Visual Studio 2022 with Python workload
- Python native development component installed
- Windows SDK (included with VS2022)

#### Build Steps
1. Open Command Prompt with VS2022 environment (Developer Command Prompt)
2. Navigate to Python source directory:
   ```cmd
   cd /d "path\to\Python-3.14.2\PCbuild"
   ```

3. Run the build script:
   ```cmd
   build.bat -c Release -p x64
   ```
   
   Or for a more specific build:
   ```cmd
   build.bat -c Release -p x64 --no-tkinter
   ```

4. After successful build, find `python314.lib` at:
   - `Python-3.14.2\PCbuild\amd64\python314.lib`

5. Copy to this directory:
   ```cmd
   copy "Python-3.14.2\PCbuild\amd64\python314.lib" "extern\library\Python\"
   ```

#### Debug Configuration
For debug builds, use:
```cmd
build.bat -c Debug -p x64
```
This produces `python314_d.lib` at `Python-3.14.2\PCbuild\amd64\python314_d.lib`

### Option 3: Python Embeddable Package
1. Download "Windows embeddable package (64-bit)" from python.org
2. Extract and find `python314.dll`
3. Generate import library using:
   ```cmd
   dumpbin /exports python314.dll > exports.txt
   lib /def:python314.def /out:python314.lib /machine:x64
   ```

## Build Configuration Options

| Option | Command | Description |
|--------|---------|-------------|
| Release x64 | `build.bat -c Release -p x64` | Production build, 64-bit |
| Debug x64 | `build.bat -c Debug -p x64` | Debug symbols, 64-bit |
| No Tkinter | `--no-tkinter` | Skip Tk/Tcl dependencies |
| PGO Build | `build.bat --pgo` | Profile-guided optimization |

## Verification

After placing the file, the directory structure should look like:
```
extern/library/Python/
├── CMakeLists.txt
├── python27_static.lib    # Python 2.7 (legacy fallback)
├── python312.lib          # Python 3.12 (previous version)
├── python314.lib          # Python 3.14 (current) ← ADD THIS
├── python312_README.md
└── python314_README.md    # This file
```

### Verify Library Symbols
Confirm the library exports Python API symbols:
```cmd
dumpbin /symbols python314.lib | findstr "Py_Initialize"
```

## Compatibility Notes

| Requirement | Specification |
|-------------|---------------|
| Visual Studio | 2022 (v17.x) or 2019 (v16.x) |
| Platform | x64 (amd64) |
| C Runtime | vcruntime140 (MSVC 14.x) |
| Windows SDK | 10.0.x |

## Python 3.14 Specific Changes

Python 3.14 introduces several changes relevant to embedding:
- Improved Free-threading support (experimental)
- PEP 649: Deferred Annotations
- PEP 750: Template Strings
- Various C API improvements

For C API migration guide, see: https://docs.python.org/3.14/whatsnew/3.14.html#c-api-changes

## Troubleshooting

### Link Error: Unresolved External Symbol
- Ensure library was built with same MSVC version as client
- Verify x64 platform matches

### Build Fails: Missing Dependencies
Run from PCbuild directory:
```cmd
get_externals.bat
```

### Import Error at Runtime
- Verify `lib-py314/` runtime libraries are in place
- Check `sys.path` configuration in embedded interpreter

## Related Files
- Headers: `extern/include/python314/`
- Runtime Library: `lib-py314/` (client runtime directory)
- CMake Config: `extern/library/Python/CMakeLists.txt`
