# Copyright (c) 2021-2025 Nicolas Beddows <nicolas.beddows@gmail.com>

# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:

# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.

# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

cmake_minimum_required (VERSION 3.25)
set(include_dir include)
set(source_dir source)
set(lib_name action)
set(major 0)
set(minor 0)
set(bugfix 1)

project(${lib_name} VERSION ${major}.${minor}.${bugfix} LANGUAGES C CXX ASM)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

if(DEFINED MSVC)
  set(build_type $<CONFIG>)
else()
  set(build_type ${CMAKE_BUILD_TYPE})
endif()

if(NOT DEFINED build_arch)
  set(build_arch ${CMAKE_SYSTEM_PROCESSOR})
endif()

if(NOT DEFINED build_os)
  set(build_os ${CMAKE_SYSTEM_NAME})
endif()

if(NOT DEFINED archive_dir)
  set(archive_dir "lib")
endif()

if(NOT DEFINED runtime_dir)
  set(runtime_dir "bin")
endif()

if(${BUILD_SHARED_LIBS} STREQUAL ON)
  set(lib_type SHARED)

  if(DEFINED WIN32)
    set(ext dll)
  else()
    set(ext so)
  endif()
else()
  set(lib_type STATIC)

  if(DEFINED WIN32)
    set(ext lib)
  else()
    set(ext a)
  endif()
endif()

set(artifacts_dir $<1:${CMAKE_SOURCE_DIR}/artifacts/${build_type}/${build_arch}>)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${artifacts_dir}/${archive_dir})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${artifacts_dir}/${runtime_dir})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${artifacts_dir}/${runtime_dir})

find_package(nlohmann_json REQUIRED)

set (${lib_name}_public_include_files
	${include_dir}/${lib_name}/Action.h
)

set (${lib_name}_source_files
  ${source_dir}/Action.cpp
)

SOURCE_GROUP(${lib_name}/${include_dir} FILES ${${lib_name}_public_include_files})
SOURCE_GROUP(${lib_name}/${source_dir} FILES ${${lib_name}_source_files})

add_library(${lib_name} ${lib_type}
  ${${lib_name}_public_include_files}
  ${${lib_name}_source_files}
)

target_include_directories(${lib_name} PRIVATE ${CMAKE_SOURCE_DIR}/${include_dir})
set_target_properties(${lib_name} PROPERTIES VERSION ${CMAKE_PROJECT_VERSION} SOVERSION ${CMAKE_PROJECT_VERSION})
target_compile_definitions(${lib_name} PUBLIC ${lib_name}_${lib_type})

if (NOT DEFINED BUILD_TESTING OR NOT ${BUILD_TESTING} STREQUAL OFF)
  add_subdirectory(tests/${lib_name}_test)
endif()

set(CMAKE_INSTALL_PREFIX ./)
set(CPACK_PACKAGE_FILE_NAME ${lib_name}-v${CMAKE_PROJECT_VERSION}-${build_os}-${build_arch}-${CMAKE_C_COMPILER_ID}-${CMAKE_C_COMPILER_VERSION})
set(CPACK_GENERATOR TGZ)

target_sources(${lib_name} INTERFACE FILE_SET HEADERS BASE_DIRS ${include_dir} FILES ${${lib_name}_public_include_files})

install(TARGETS ${lib_name} FILE_SET HEADERS)
install(FILES LICENSE DESTINATION .)

if(NOT DEFINED WIN32)
  set(CPACK_SET_DESTDIR ON)
endif()

include(CPack)
