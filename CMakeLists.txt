cmake_minimum_required(VERSION 2.8)
PROJECT(RenderingVolumeFromDICOM)

find_package(VTK REQUIRED)
include(${VTK_USE_FILE})

add_executable(RenderingVolumeFromDICOM MACOSX_BUNDLE RenderingVolumeFromDICOM)

target_link_libraries(RenderingVolumeFromDICOM ${VTK_LIBRARIES})
