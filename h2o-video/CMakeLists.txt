# CMakeList.txt : CMake project for h2o-video, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

find_package(raylib CONFIG REQUIRED)

# Add source to this project's executable.
add_executable (h2o-video "h2o-video.cpp" "h2o-video.h")
target_compile_features(h2o-video PRIVATE cxx_std_20)
target_include_directories(h2o-video PRIVATE ${RAYLIB_INCLUDE_DIRS})
target_link_libraries(h2o-video PRIVATE ${RAYLIB_LIBRARIES})
# TODO: Add tests and install targets if needed.
