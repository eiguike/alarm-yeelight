cmake_minimum_required(VERSION 3.0)

project(alarm_xaiomi C)

include_directories("./include")

set(SOURCE_FILES main.c)
add_executable(alarm_xaiomi ${SOURCE_FILES})

install(TARGETS alarm_xaiomi DESTINATION /bin)
