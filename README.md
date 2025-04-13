
# Deribit Trading System

A high-performance **C++ application** designed to interact with the Deribit Test API for cryptocurrency trading. This project demonstrates secure API authentication, comprehensive order management, and real-time market data retrieval—all built using modern C++ standards and a modular architecture.

---

## Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Project Structure](#project-structure)
- [Prerequisites](#prerequisites)
- [Installation Instructions](#installation-instructions)
  - [Step 1: Clone the Repository](#step-1-clone-the-repository)
  - [Step 2: Install Dependencies via vcpkg](#step-2-install-dependencies-via-vcpkg)
  - [Step 3: Configure the Project Using CMake](#step-3-configure-the-project-using-cmake)
  - [Step 4: Build the Project](#step-4-build-the-project)
  - [Step 5: Run the Executable](#step-5-run-the-executable)
- [Explanation of Key Files](#explanation-of-key-files)
- [Troubleshooting](#troubleshooting)
- [Future Enhancements](#future-enhancements)
- [License](#license)

---

## Overview

The **Deribit Trading System** is built to:

- **Securely authenticate** with the Deribit API using OAuth 2.0.
- **Manage orders** including placing, modifying, and canceling orders.
- **Retrieve market data** such as the orderbook for specific instruments.
- **Manage dependencies** and build the project using **CMake**.

**Key Points:**
- **C++-only Implementation:** Every component of the system is implemented in C++.
- **CMake-Driven Build & Dependency Management:** CMake is used not only for building the project but also for managing dependencies (e.g., libcurl and JsonCpp) via integration with `vcpkg` and custom scripts.

---

## Features

### Core Functionalities
- **Authentication**
  - Uses OAuth 2.0 to securely connect to the Deribit Test API.
- **Order Management**
  - Place buy and sell orders.
  - Modify and cancel orders.
- **Market Data Retrieval**
  - Fetch real-time orderbook data for specified instruments.

### Technical Highlights
- **Dependency Management and Build System**
  - **CMake is used for building the project and managing dependencies.** All external libraries such as `libcurl` and `JsonCpp` are integrated via `vcpkg`.
  - A custom PowerShell script (`download_deps.ps1`) is available for manual dependency management.
- **Cross-Platform Support**
  - The project is configured using CMake for cross-platform builds.
  - Supports custom triplets, including Address Sanitizer (`x64-windows-asan`), for enhanced debugging.

---

## Project Structure

```plaintext
Deribit-Trading-System-main/
├── .vscode/                   # VS Code configuration files
├── bin/                       # Binary files (if applicable)
├── build/                     # Build output directory (generated by CMake)
├── custom_triplets/           # Custom vcpkg triplet files
├── deps/                      # External dependencies (libcurl, JsonCpp)
│   ├── curl/
│   └── jsoncpp/
├── include/                   # Header files for project modules
│   ├── account.hpp
│   ├── auth.hpp
│   ├── cancel_order.hpp
│   ├── get_orderbook.hpp
│   ├── modify_order.hpp
│   ├── order.hpp
│   └── sell_order.hpp
├── lib/                       # Library files (if applicable)
├── src/                       # Source files for project modules (C++ implementation)
│   ├── account.cpp
│   ├── auth.cpp
│   ├── cancel_order.cpp
│   ├── get_orderbook.cpp
│   ├── modify_order.cpp
│   ├── order.cpp
│   └── sell_order.cpp
├── vcpkg/                     # vcpkg package manager directory
├── CMakeLists.txt             # CMake configuration file (build & dependency management)
├── download_deps.ps1          # PowerShell script to download dependencies
└── README.md                  # Project documentation file (this file)
```

---

## Prerequisites

- **C++ Compiler:** A modern C++17-compliant compiler (e.g., MinGW-w64 or MSVC).
- **CMake:** Version 3.10 or higher.
- **vcpkg:** For dependency management (see the [vcpkg GitHub repository](https://github.com/microsoft/vcpkg) for installation instructions).
- **PowerShell:** Required for running the `download_deps.ps1` script.
- **Deribit Test Account:** Register at [Deribit Test](https://test.deribit.com) to generate API credentials.

---

## Installation Instructions

### Step 1: Clone the Repository

Clone this repository and change into the project directory:

```bash
git clone https://github.com/your_username/Deribit-Trading-System.git
cd Deribit-Trading-System-main
```

### Step 2: Install Dependencies via vcpkg

Navigate to the `vcpkg` directory, bootstrap vcpkg, and install the required libraries:

```bash
cd vcpkg
.\bootstrap-vcpkg.bat
.\vcpkg install curl:x64-windows jsoncpp:x64-windows
```

### Step 3: Configure the Project Using CMake

Create a build directory from the project root and configure the project. **CMake is used for both building the project and managing dependencies.**

```bash
cd path\to\Deribit-Trading-System-main
mkdir build && cd build
cmake .. -G "MinGW Makefiles"
```

### Step 4: Build the Project

Compile the project by executing:

```bash
mingw32-make
```

### Step 5: Run the Executable

Ensure that runtime DLLs (`libcurl.dll`, `jsoncpp.dll`) are present in the executable directory, then run:

```bash
.\deribit_trading_system.exe
```

---

## Explanation of Key Files

- **`CMakeLists.txt`**
  - The main configuration file for building the project using CMake. It handles dependency management (e.g., linking `libcurl` and `JsonCpp`).
- **`download_deps.ps1`**
  - A PowerShell script to manually download and extract dependencies if needed.
- **Source Files (`src/`)**
  - **`auth.cpp`**: Implements authentication with the Deribit API.
  - **`order.cpp`**: Implements buy order placement.
  - **`sell_order.cpp`**: Implements sell order functionality.
  - **`modify_order.cpp`**: Handles order modifications.
  - **`cancel_order.cpp`**: Implements order cancellation.
  - **`get_orderbook.cpp`**: Fetches and processes real-time market data.
- **Header Files (`include/`)**
  - Provide declarations for corresponding source files.

---

## Troubleshooting

### Missing Dependencies
Ensure all dependencies are installed via vcpkg:

```bash
cd vcpkg
.\vcpkg install curl:x64-windows jsoncpp:x64-windows
```

### DLL Issues at Runtime
If you encounter missing DLL errors, copy the required DLLs from:

```
vcpkg/installed/x64-windows/bin/
```

to the same directory as your executable.

### CMake Build Errors
Confirm that paths in `CMakeLists.txt` correctly reflect your project’s directory structure.

---

## Future Enhancements

- **WebSocket Integration:** Enable real-time market data streaming.
- **Performance Optimization:** Improve memory management and implement lock-free data structures.
- **Advanced Order Types:** Add support for stop-loss, take-profit, and trailing stop orders.
- **Risk Management:** Integrate features like position sizing and maximum drawdown controls.
- **Backtesting Framework:** Incorporate historical data for strategy testing and validation.

---

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

---

Thank you for exploring the Deribit Trading System! 

All functionality is implemented entirely in C++, and the build process is managed through CMake for seamless dependency integration and platform support.
