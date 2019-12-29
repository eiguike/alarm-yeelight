cmake_minimum_required(VERSION 3.0)

project(alarm_xaiomi C)

add_library(ClientUDP STATIC src/library/yeelight_udp.c)
add_library(Yeelight STATIC src/library/yeelight.c)
add_library(Logger STATIC src/library/logger.c)

include_directories("./src/include")

set(SOURCE_FILES src/main.c)
add_executable(alarm_xaiomi ${SOURCE_FILES})

target_link_libraries(Yeelight Logger)
target_link_libraries(ClientUDP Logger)

target_link_libraries(Yeelight ClientUDP)
target_link_libraries(alarm_xaiomi Yeelight)

install(TARGETS alarm_xaiomi DESTINATION /bin)
