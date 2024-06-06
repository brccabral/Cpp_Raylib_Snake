cmake_minimum_required(VERSION 3.28)
project(Snake)

include(GNUInstallDirs)

set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} raylib)
install(TARGETS ${PROJECT_NAME})

# copy resources to Build folder for debugging
set(resources_list)
file(GLOB resources_files resources/*)
list(APPEND resources_list ${resources_files})
file(COPY ${resources_files} DESTINATION "resources/")

# copy resources to Install location
install(DIRECTORY
        ${PROJECT_SOURCE_DIR}/resources
        DESTINATION ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_BINDIR}
)


