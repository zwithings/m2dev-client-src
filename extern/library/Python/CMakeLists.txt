add_library(Python INTERFACE)

# Python 3.14 support - conditional include paths and library linking
if(USE_PYTHON3)
    message(STATUS "Building with Python 3.14 support")
    target_include_directories(Python INTERFACE "${CMAKE_SOURCE_DIR}/extern/include/python314")
    target_link_libraries(Python INTERFACE "${CMAKE_CURRENT_LIST_DIR}/python314.lib")
    target_compile_definitions(Python INTERFACE PYTHON_3)
else()
    message(STATUS "Building with Python 2.7 support")
    target_include_directories(Python INTERFACE "${CMAKE_SOURCE_DIR}/extern/include/python")
    target_link_libraries(Python INTERFACE "${CMAKE_CURRENT_LIST_DIR}/python27_static.lib")
endif()
