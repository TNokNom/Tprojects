
cmake_minimum_required(VERSION 3.18)
project(ML/Cuda Project LANGUAGES CXX CUDA)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set CUDA paths explicitly
set(CUDA_TOOLKIT_ROOT_DIR /opt/cuda)
include_directories(/opt/cuda/include)
link_directories(/opt/cuda/lib64)

# Enable CUDA language support (you can remove if you don't need to compile yet)
enable_language(CUDA)

# Set compiler to GCC (or clang++, depending on your choice)
set(CMAKE_CXX_COMPILER /sbin/g++)  # Use gcc or g++ for CUDA (GCC might not be ideal)
set(CMAKE_CUDA_COMPILER /sbin/nvcc)  # Similarly, set CUDA compiler to GCC
