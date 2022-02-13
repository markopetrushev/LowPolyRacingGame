# Install script for directory: D:/Glitter/Glitter/Vendor/assimp/code

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/Glitter")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "C:/Program Files (x86)/mingw-w64/i686-8.1.0-posix-dwarf-rt_v6-rev0/mingw32/bin/objdump.exe")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "D:/Glitter/cmake-build-debug/Glitter/Vendor/assimp/lib/libassimpd.a")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xassimp-devx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/assimp" TYPE FILE FILES
    "D:/Glitter/Glitter/Vendor/assimp/code/../include/assimp/anim.h"
    "D:/Glitter/Glitter/Vendor/assimp/code/../include/assimp/aabb.h"
    "D:/Glitter/Glitter/Vendor/assimp/code/../include/assimp/ai_assert.h"
    "D:/Glitter/Glitter/Vendor/assimp/code/../include/assimp/camera.h"
    "D:/Glitter/Glitter/Vendor/assimp/code/../include/assimp/color4.h"
    "D:/Glitter/Glitter/Vendor/assimp/code/../include/assimp/color4.inl"
    "D:/Glitter/cmake-build-debug/Glitter/Vendor/assimp/code/../include/assimp/config.h"
    "D:/Glitter/Glitter/Vendor/assimp/code/../include/assimp/ColladaMetaData.h"
    "D:/Glitter/Glitter/Vendor/assimp/code/../include/assimp/commonMetaData.h"
    "D:/Glitter/Glitter/Vendor/assimp/code/../include/assimp/defs.h"
    "D:/Glitter/Glitter/Vendor/assimp/code/../include/assimp/Defines.h"
    "D:/Glitter/Glitter/Vendor/assimp/code/../include/assimp/cfileio.h"
    "D:/Glitter/Glitter/Vendor/assimp/code/../include/assimp/light.h"
    "D:/Glitter/Glitter/Vendor/assimp/code/../include/assimp/material.h"
    "D:/Glitter/Glitter/Vendor/assimp/code/../include/assimp/material.inl"
    "D:/Glitter/Glitter/Vendor/assimp/code/../include/assimp/matrix3x3.h"
    "D:/Glitter/Glitter/Vendor/assimp/code/../include/assimp/matrix3x3.inl"
    "D:/Glitter/Glitter/Vendor/assimp/code/../include/assimp/matrix4x4.h"
    "D:/Glitter/Glitter/Vendor/assimp/code/../include/assimp/matrix4x4.inl"
    "D:/Glitter/Glitter/Vendor/assimp/code/../include/assimp/mesh.h"
    "D:/Glitter/Glitter/Vendor/assimp/code/../include/assimp/pbrmaterial.h"
    "D:/Glitter/Glitter/Vendor/assimp/code/../include/assimp/postprocess.h"
    "D:/Glitter/Glitter/Vendor/assimp/code/../include/assimp/quaternion.h"
    "D:/Glitter/Glitter/Vendor/assimp/code/../include/assimp/quaternion.inl"
    "D:/Glitter/Glitter/Vendor/assimp/code/../include/assimp/scene.h"
    "D:/Glitter/Glitter/Vendor/assimp/code/../include/assimp/metadata.h"
    "D:/Glitter/Glitter/Vendor/assimp/code/../include/assimp/texture.h"
    "D:/Glitter/Glitter/Vendor/assimp/code/../include/assimp/types.h"
    "D:/Glitter/Glitter/Vendor/assimp/code/../include/assimp/vector2.h"
    "D:/Glitter/Glitter/Vendor/assimp/code/../include/assimp/vector2.inl"
    "D:/Glitter/Glitter/Vendor/assimp/code/../include/assimp/vector3.h"
    "D:/Glitter/Glitter/Vendor/assimp/code/../include/assimp/vector3.inl"
    "D:/Glitter/Glitter/Vendor/assimp/code/../include/assimp/version.h"
    "D:/Glitter/Glitter/Vendor/assimp/code/../include/assimp/cimport.h"
    "D:/Glitter/Glitter/Vendor/assimp/code/../include/assimp/importerdesc.h"
    "D:/Glitter/Glitter/Vendor/assimp/code/../include/assimp/Importer.hpp"
    "D:/Glitter/Glitter/Vendor/assimp/code/../include/assimp/DefaultLogger.hpp"
    "D:/Glitter/Glitter/Vendor/assimp/code/../include/assimp/ProgressHandler.hpp"
    "D:/Glitter/Glitter/Vendor/assimp/code/../include/assimp/IOStream.hpp"
    "D:/Glitter/Glitter/Vendor/assimp/code/../include/assimp/IOSystem.hpp"
    "D:/Glitter/Glitter/Vendor/assimp/code/../include/assimp/Logger.hpp"
    "D:/Glitter/Glitter/Vendor/assimp/code/../include/assimp/LogStream.hpp"
    "D:/Glitter/Glitter/Vendor/assimp/code/../include/assimp/NullLogger.hpp"
    "D:/Glitter/Glitter/Vendor/assimp/code/../include/assimp/cexport.h"
    "D:/Glitter/Glitter/Vendor/assimp/code/../include/assimp/Exporter.hpp"
    "D:/Glitter/Glitter/Vendor/assimp/code/../include/assimp/DefaultIOStream.h"
    "D:/Glitter/Glitter/Vendor/assimp/code/../include/assimp/DefaultIOSystem.h"
    "D:/Glitter/Glitter/Vendor/assimp/code/../include/assimp/ZipArchiveIOSystem.h"
    "D:/Glitter/Glitter/Vendor/assimp/code/../include/assimp/SceneCombiner.h"
    "D:/Glitter/Glitter/Vendor/assimp/code/../include/assimp/fast_atof.h"
    "D:/Glitter/Glitter/Vendor/assimp/code/../include/assimp/qnan.h"
    "D:/Glitter/Glitter/Vendor/assimp/code/../include/assimp/BaseImporter.h"
    "D:/Glitter/Glitter/Vendor/assimp/code/../include/assimp/Hash.h"
    "D:/Glitter/Glitter/Vendor/assimp/code/../include/assimp/MemoryIOWrapper.h"
    "D:/Glitter/Glitter/Vendor/assimp/code/../include/assimp/ParsingUtils.h"
    "D:/Glitter/Glitter/Vendor/assimp/code/../include/assimp/StreamReader.h"
    "D:/Glitter/Glitter/Vendor/assimp/code/../include/assimp/StreamWriter.h"
    "D:/Glitter/Glitter/Vendor/assimp/code/../include/assimp/StringComparison.h"
    "D:/Glitter/Glitter/Vendor/assimp/code/../include/assimp/StringUtils.h"
    "D:/Glitter/Glitter/Vendor/assimp/code/../include/assimp/SGSpatialSort.h"
    "D:/Glitter/Glitter/Vendor/assimp/code/../include/assimp/GenericProperty.h"
    "D:/Glitter/Glitter/Vendor/assimp/code/../include/assimp/SpatialSort.h"
    "D:/Glitter/Glitter/Vendor/assimp/code/../include/assimp/SkeletonMeshBuilder.h"
    "D:/Glitter/Glitter/Vendor/assimp/code/../include/assimp/SmallVector.h"
    "D:/Glitter/Glitter/Vendor/assimp/code/../include/assimp/SmoothingGroups.h"
    "D:/Glitter/Glitter/Vendor/assimp/code/../include/assimp/SmoothingGroups.inl"
    "D:/Glitter/Glitter/Vendor/assimp/code/../include/assimp/StandardShapes.h"
    "D:/Glitter/Glitter/Vendor/assimp/code/../include/assimp/RemoveComments.h"
    "D:/Glitter/Glitter/Vendor/assimp/code/../include/assimp/Subdivision.h"
    "D:/Glitter/Glitter/Vendor/assimp/code/../include/assimp/Vertex.h"
    "D:/Glitter/Glitter/Vendor/assimp/code/../include/assimp/LineSplitter.h"
    "D:/Glitter/Glitter/Vendor/assimp/code/../include/assimp/TinyFormatter.h"
    "D:/Glitter/Glitter/Vendor/assimp/code/../include/assimp/Profiler.h"
    "D:/Glitter/Glitter/Vendor/assimp/code/../include/assimp/LogAux.h"
    "D:/Glitter/Glitter/Vendor/assimp/code/../include/assimp/Bitmap.h"
    "D:/Glitter/Glitter/Vendor/assimp/code/../include/assimp/XMLTools.h"
    "D:/Glitter/Glitter/Vendor/assimp/code/../include/assimp/IOStreamBuffer.h"
    "D:/Glitter/Glitter/Vendor/assimp/code/../include/assimp/CreateAnimMesh.h"
    "D:/Glitter/Glitter/Vendor/assimp/code/../include/assimp/XmlParser.h"
    "D:/Glitter/Glitter/Vendor/assimp/code/../include/assimp/BlobIOSystem.h"
    "D:/Glitter/Glitter/Vendor/assimp/code/../include/assimp/MathFunctions.h"
    "D:/Glitter/Glitter/Vendor/assimp/code/../include/assimp/Exceptional.h"
    "D:/Glitter/Glitter/Vendor/assimp/code/../include/assimp/ByteSwapper.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xassimp-devx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/assimp/Compiler" TYPE FILE FILES
    "D:/Glitter/Glitter/Vendor/assimp/code/../include/assimp/Compiler/pushpack1.h"
    "D:/Glitter/Glitter/Vendor/assimp/code/../include/assimp/Compiler/poppack1.h"
    "D:/Glitter/Glitter/Vendor/assimp/code/../include/assimp/Compiler/pstdint.h"
    )
endif()

