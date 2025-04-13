cmake_minimum_required(VERSION 3.10)

# Set vcpkg configuration before the project() command
set(VCPKG_OVERLAY_TRIPLETS "${CMAKE_CURRENT_SOURCE_DIR}/custom_triplets")
set(VCPKG_TARGET_TRIPLET "x64-windows-asan")
set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")

project(DeribitTradingSystem)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Define dependency paths
set(DEPS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/deps")
set(CURL_DIR "${DEPS_DIR}/curl/curl-8.6.0_3-win64-mingw")

# Use JsonCpp from vcpkg
set(JSONCPP_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/installed/x64-windows/include")
set(JSONCPP_LIBRARY "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/installed/x64-windows/lib/jsoncpp.lib")

# Print paths for debugging
message(STATUS "Using CURL include directory: ${CURL_DIR}/include")
message(STATUS "Using JsonCpp include directory: ${JSONCPP_INCLUDE_DIR}")
message(STATUS "Using JsonCpp library: ${JSONCPP_LIBRARY}")

# Create the source file list
set(SOURCES
    src/auth.cpp
    src/account.cpp
    src/order.cpp
    src/cancel_order.cpp
    src/get_orderbook.cpp
    src/modify_order.cpp
    src/sell_order.cpp
    src/main.cpp
)

# Create executable target
add_executable(deribit_trading_system ${SOURCES})

# Add include directories for headers
target_include_directories(deribit_trading_system PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CURL_DIR}/include
    ${JSONCPP_INCLUDE_DIR}
)

# Link libraries - use the local libcurl and vcpkg JsonCpp library
target_link_libraries(deribit_trading_system PRIVATE
    ${CURL_DIR}/lib/libcurl.dll.a
    ${JSONCPP_LIBRARY}
)
