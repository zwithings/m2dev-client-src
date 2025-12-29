cmake_minimum_required(VERSION 3.19)

project(m2dev-client-src)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ASan support
option(ENABLE_ASAN "Enable AddressSanitizer" OFF)

# Python 3.14 support
option(USE_PYTHON3 "Use Python 3.14 instead of Python 2.7" OFF)

set(CMAKE_MODULE_PATH
	${CMAKE_MODULE_PATH}
	"${CMAKE_CURRENT_SOURCE_DIR}/buildtool"
)

include(Utils)

set(CMAKE_CONFIGURATION_TYPES "Debug;RelWithDebInfo;Release" CACHE STRING "Configurations" FORCE)
set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<$<CONFIG:Debug,RelWithDebInfo,Release>:ProgramDatabase>")

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /Zi")
set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} /DEBUG")

add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options(/MP)

if(MSVC)
	add_compile_definitions(UNICODE _UNICODE)
endif()

add_compile_options(
	$<$<CXX_COMPILER_ID:MSVC>:/wd4828>
	$<$<CXX_COMPILER_ID:MSVC>:/wd4996>
)

# ASan flags
if(ENABLE_ASAN)
	if(MSVC)
		add_compile_options(/fsanitize=address)
		add_link_options(/fsanitize=address)
		add_definitions(-D_DISABLE_VECTOR_ANNOTATION)
		add_definitions(-D_DISABLE_STRING_ANNOTATION)
	else()
		add_compile_options(-fsanitize=address -fno-omit-frame-pointer)
		add_link_options(-fsanitize=address)
	endif()
endif()

add_definitions(-DNOMINMAX)
add_definitions(-DWIN32_LEAN_AND_MEAN)
add_definitions(-D_CRT_SECURE_NO_WARNINGS)
add_definitions(-DWINDOWS_IGNORE_PACKING_MISMATCH)

add_definitions(-DUSE_LOD)
add_definitions(-DDUNGEON_WORK)
add_definitions(-DBUILDING_GRANNY_STATIC)
add_definitions(-DGRANNY_THREADED)
# Py_NO_ENABLE_SHARED is only for Python 2.7 static build
if(NOT USE_PYTHON3)
    add_definitions(-DPy_NO_ENABLE_SHARED)
endif()

add_compile_definitions("$<$<CONFIG:Debug>:DEBUG>")
add_compile_definitions("$<$<CONFIG:RelWithDebInfo>:_DISTRIBUTE>")
add_compile_definitions("$<$<CONFIG:Release>:_DISTRIBUTE>")

# Python 3.14 support - must be before include_directories to ensure correct header order
if(USE_PYTHON3)
    # Define PYTHON_3 globally so all targets use Python 3.14 headers
    add_definitions(-DPYTHON_3)
    # Add Python 3.14 headers BEFORE extern/include to ensure they are found first
    include_directories("extern/include/python314")
endif()

include_directories("src")
include_directories("extern/include")

# Add subdirectories for libraries and executables
add_subdirectory(vendor)
add_subdirectory(src)
add_subdirectory(extern)