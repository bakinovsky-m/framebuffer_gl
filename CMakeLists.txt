project(frame_buffer C CXX)

set(src
    main.cpp
)

set(hdr
  utils.hpp
  )

add_executable(${PROJECT_NAME} ${src} ${hdr})

target_link_libraries(${PROJECT_NAME} GL GLU glut)
