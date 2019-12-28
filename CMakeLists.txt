cmake_minimum_required(VERSION 3.0)

project(alarm_xaiomi C)

add_library(ClientUDP STATIC library/yeelight_udp.c)
add_library(Yeelight STATIC library/yeelight.c)

include_directories("./include")

set(SOURCE_FILES main.c)
add_executable(alarm_xaiomi ${SOURCE_FILES})

target_link_libraries(Yeelight ClientUDP)
target_link_libraries(alarm_xaiomi Yeelight)

install(TARGETS alarm_xaiomi DESTINATION /bin)
