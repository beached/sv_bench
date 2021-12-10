cmake_minimum_required(VERSION 3.14)
project(string_view_bench)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(extern)

find_package(benchmark CONFIG REQUIRED)

include_directories(include/)
add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE benchmark::benchmark benchmark::benchmark_main)

target_link_libraries(
        ${PROJECT_NAME}
        PRIVATE
        daw::daw-header-libraries
)

install(TARGETS ${PROJECT_NAME}
        EXPORT ${PROJECT_NAME}_Targets
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
