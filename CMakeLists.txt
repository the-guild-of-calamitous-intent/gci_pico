
# Specify the minimum version of CMake
cmake_minimum_required(VERSION 3.20)

# Set the Pico SDK path (adjust if needed)
set(PICO_SDK_PATH "$ENV{HOME}/github/pico-sdk")
set(PICO_BOARD "pico") # before pico_sdk_import.cmake, pico, pico2, pico_w

# Include the Pico SDK
include(${PICO_SDK_PATH}/external/pico_sdk_import.cmake)

# Set project name and language
project(gci_pico C CXX ASM)
set(CMAKE_C_STANDARD 23) # Options: 90, 99, 11, 17, 23 (or gnu90, gnu99, etc.)
# set(CMAKE_C_STANDARD_REQUIRED ON) # Enforce the standard
# set(CMAKE_C_EXTENSIONS OFF) # Disable GNU extensions (optional, use ON for gnuXX)

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -Os")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Os")
string(PREPEND CMAKE_EXE_LINKER_FLAGS " -Wl,--print-memory-usage ")

if(PROJECT_IS_TOP_LEVEL)
  cmake_host_system_information(RESULT HOST QUERY HOSTNAME)
  cmake_host_system_information(RESULT OSN QUERY OS_NAME)
  cmake_host_system_information(RESULT OS_VERSION QUERY OS_RELEASE)
  cmake_host_system_information(RESULT PROC QUERY PROCESSOR_DESCRIPTION)

  message(STATUS "-------------------------------------")
  message(STATUS "  Project: ${PROJECT_NAME}")
  message(STATUS "  Hardware: ${PICO_BOARD}")
  message(STATUS "  C++ ${CMAKE_CXX_STANDARD}")
  message(STATUS "  C ${CMAKE_C_STANDARD}")
  message(STATUS "-------------------------------------")
  message(STATUS " ${HOST}")
  message(STATUS " ${OSN}: ${OS_VERSION}")
  message(STATUS " ${PROC}")
  message(STATUS "-------------------------------------")

  set(BUILD_EXAMPLES ON)
else()
  message(STATUS "-> ${PROJECT_NAME} is submodule")
  set(BUILD_EXAMPLES OFF)
endif()

# Initialize the Pico SDK
pico_sdk_init()

LIST(APPEND pico_libs
  pico_stdlib
  hardware_adc
  hardware_i2c
  hardware_pwm
  hardware_spi
  hardware_uart
)

add_library(${PROJECT_NAME}
  src/adc.c
  src/fifo.c
  src/i2c.c
  src/linked_list.c
  src/pwm.c
  # src/rtc.c
  src/spi.c
  src/uart.c
  src/usb.c
)
target_include_directories(${PROJECT_NAME} PUBLIC src)
target_link_libraries(${PROJECT_NAME} ${pico_libs})
# target_compile_definitions(${PROJECT_NAME} PUBLIC BOARD_TYPE=${PICO_BOARD})


pico_enable_stdio_usb(${PROJECT_NAME} 1)
pico_enable_stdio_uart(${PROJECT_NAME} 0)


if (BUILD_EXAMPLES)
  add_subdirectory(examples)
endif()

# # Add the executable
# add_executable(test
#     src/main.c
# )

# Link libraries

# # target_compile_definitions(${PROJECT_NAME} PRIVATE UART_QUEUE_SIZE=512)

# # Set stdio functions to use USB rather than the serial ports
# pico_enable_stdio_usb(${PROJECT_NAME} 1)
# pico_enable_stdio_uart(${PROJECT_NAME} 0)


# # Enable USB output, disable UART output
# # pico_enable_stdio_usb(blink 1)
# # pico_enable_stdio_uart(blink 0)

# # Create map/bin/hex/uf2 files
# pico_add_extra_outputs(${PROJECT_NAME})

# # fix cleanup command ------------------------------------------------
# set_target_properties(${PROJECT_NAME}
# PROPERTIES
#     ADDITIONAL_CLEAN_FILES
#     "${PROJECT_NAME}.bin;${PROJECT_NAME}.hex;*.elf;${PROJECT_NAME}.dis;${PROJECT_NAME}.elf.map;${PROJECT_NAME}.uf2")

# # Show info after project bulid ---------------------------------------
# add_custom_command(
# TARGET ${PROJECT_NAME}
# POST_BUILD
# COMMAND echo -------------------------------------
#         && picotool info ${PROJECT_NAME}.uf2 -a
#         # && echo -------------------------------------
#         # && arm-none-eabi-size ${PROJECT_NAME}.elf
#         # && arm-none-eabi-objdump -h ${PROJECT_NAME}.elf
#         && echo -------------------------------------
# )




# cmake_minimum_required(VERSION 3.13)
# # include(pico_sdk_import.cmake)

# set(PROJECT gcipico)
# string(TOLOWER "pico" PICO_BOARD) # pico or pico_w

# set(PICO_SDK_PATH "$ENV{HOME}/github/pico-sdk")
# set(ENV{PATH} "$ENV{HOME}/github/gcc-arm/bin:$ENV{PATH}")
# set(PICO_SDK_PATH "${PICO_SDK_PATH}" CACHE PATH "Path to the PICO SDK")

# set(PICO_CXX_ENABLE_EXCEPTIONS 0)

# include(${PICO_SDK_PATH}/pico_sdk_init.cmake)

# include(FetchContent)

# # Need ASM for tinyUSB and picotool to work
# # project(${PROJECT} C CXX ASM)
# set(CMAKE_C_STANDARD 17)
# # set(CMAKE_CXX_STANDARD 20)

# string (APPEND CMAKE_CXX_FLAGS_RELEASE " -O3 ")
# string (APPEND CMAKE_C_FLAGS_RELEASE " -O3 ")
# string(PREPEND CMAKE_EXE_LINKER_FLAGS " -Wl,--print-memory-usage ")


# project(blink  C ASM)
# pico_sdk_init()

# if(PICO_SDK)
#     add_definitions(-DPICO_SDK=1)

#     # these don't seem to work???
#     if (${PICO_BOARD} STREQUAL "pico")
#         add_definitions(-DPI_PICO=1)
#     elseif(${PICO_BOARD} STREQUAL "pico_w")
#         add_definitions(-DPI_PICO_W=1)
#     endif()
# endif()


# add_executable(blink src/main.c)
# target_link_libraries(blink pico_stdlib)
# pico_add_extra_outputs(blink)