cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)

project(sample-musicstreamer-applications)

cmake_policy(SET CMP0076 NEW)

add_definitions("-std=c++17")

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK+3 REQUIRED gtk+-3.0)
pkg_check_modules(GSTREAMER REQUIRED gstreamer-1.0)

include_directories(${GTK+3_INCLUDE_DIRS})
include_directories(${GSTREAMER_INCLUDE_DIRS})

add_executable(receiver)
add_executable(sender)
add_executable(registrar)
add_subdirectory(include)
add_subdirectory(src)

target_include_directories(receiver PUBLIC include)
target_include_directories(sender PUBLIC include)
target_include_directories(registrar PUBLIC include)

target_link_libraries(receiver
  ${CONAN_LIBS}
  ${GTK+3_LINK_LIBRARIES}
  ${GSTREAMER_LINK_LIBRARIES}
)

target_link_libraries(sender
  ${GTK+3_LINK_LIBRARIES}
  ${GSTREAMER_LINK_LIBRARIES}
)

target_link_libraries(registrar
  ${CONAN_LIBS}
  ${GTK+3_LINK_LIBRARIES}
  ${GSTREAMER_LINK_LIBRARIES}
)

set_target_properties(sender PROPERTIES
  MACOSX_BUNDLE TRUE
  MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_SOURCE_DIR}/Info.plist
)
