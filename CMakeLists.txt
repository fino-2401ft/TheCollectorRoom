cmake_minimum_required(VERSION 3.10)
project(TheCollectorRoom)

set(CMAKE_CXX_STANDARD 17)

# Thêm thư mục chứa header và thư viện
include_directories(include third_party)
link_directories(${CMAKE_SOURCE_DIR}/third_party)

# Tìm OpenGL
find_package(OpenGL REQUIRED)

# Thêm tất cả file .cpp
file(GLOB SOURCES src/*.cpp)

# Tạo executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Liên kết thư viện
target_link_libraries(${PROJECT_NAME}
    ${OPENGL_LIBRARIES}
    glfw3
    glew32
)
