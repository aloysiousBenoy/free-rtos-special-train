cmake_minimum_required(VERSION 3.12)

# set(FREERTOS_KERNEL_PATH "/home/raider0ne/projects/hardware/free_rtos/FreeRTOS/Source")
set(FREERTOS_KERNEL_PATH "../FreeRTOS-Kernel")


include(pico_sdk_import.cmake)
include(FreeRTOS_Kernel_import.cmake)

project(neopix)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)


pico_sdk_init()

add_executable(neopix neopix.c)

target_include_directories(neopix PRIVATE ${CMAKE_CURRENT_LIST_DIR})

target_link_libraries(neopix pico_stdlib FreeRTOS-Kernel FreeRTOS-Kernel-Heap4)

pico_enable_stdio_usb(neopix 0)

pico_enable_stdio_uart(neopix 1)

pico_add_extra_outputs(neopix)