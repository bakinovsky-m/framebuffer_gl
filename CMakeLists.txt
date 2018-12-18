project(frame_buffer C CXX)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(GLU REQUIRED)

set(src
    main.cpp
)

set(hdr
  utils.hpp
  )

add_executable(${PROJECT_NAME} ${src} ${hdr})

target_link_libraries(${PROJECT_NAME} GL GLU glut)
