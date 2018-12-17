project(frame_buffer C CXX)

set(src
    main.cpp
)

add_executable(${PROJECT_NAME} ${src})

target_link_libraries(${PROJECT_NAME} GL GLU glut)