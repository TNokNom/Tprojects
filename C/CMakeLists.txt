cmake_minimum_required(VERSION 3.10)
project(TorchProject)

# Set the path to TorchConfig.cmake
set(Torch_DIR "/opt/libtorch/share/cmake/Torch")
find_package(Torch REQUIRED)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_executable(main src/main.cpp)

# Link Torch libraries
target_link_libraries(main "${TORCH_LIBRARIES}")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(OpenCV_LIBS opencv_core opencv_highgui opencv_imgcodecs opencv_imgproc)
target_include_directories(main PRIVATE ${TORCH_INCLUDE_DIRS})
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)


set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")
