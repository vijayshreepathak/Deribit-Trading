set(VCPKG_TARGET_ARCHITECTURE x64)
set(VCPKG_CRT_LINKAGE dynamic)
set(VCPKG_LIBRARY_LINKAGE dynamic)

# For MinGW/GCC on Windows
set(VCPKG_CXX_FLAGS "${VCPKG_CXX_FLAGS} -fsanitize=address")
set(VCPKG_C_FLAGS "${VCPKG_C_FLAGS} -fsanitize=address")
set(VCPKG_LINKER_FLAGS "${VCPKG_LINKER_FLAGS} -fsanitize=address")

# For MSVC (uncomment these lines instead if using MSVC)
# set(VCPKG_CXX_FLAGS "${VCPKG_CXX_FLAGS} /fsanitize=address")
# set(VCPKG_C_FLAGS "${VCPKG_C_FLAGS} /fsanitize=address")
# set(VCPKG_LINKER_FLAGS "${VCPKG_LINKER_FLAGS} /fsanitize=address")
