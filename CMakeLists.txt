cmake_minimum_required(VERSION 3.0)

project(alarm_yeelight C)

add_library(ClientUDP STATIC src/library/yeelight_integration.c)
add_library(Yeelight STATIC src/library/yeelight_lamp.c)
add_library(Logger STATIC src/vendors/logger-c/library/logger.c)

include_directories("./src/include")
include_directories("./src/vendors/logger-c/include")

set(SOURCE_FILES src/main.c)
add_executable(alarm_yeelight ${SOURCE_FILES})

target_link_libraries(Yeelight Logger)
target_link_libraries(ClientUDP Logger)

target_link_libraries(Yeelight ClientUDP)
target_link_libraries(alarm_yeelight Yeelight)

install(TARGETS alarm_yeelight DESTINATION /bin)
