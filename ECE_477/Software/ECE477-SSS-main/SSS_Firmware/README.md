| Supported Targets | ESP32 | ESP32-C2 | ESP32-C3 | ESP32-C6 | ESP32-H2 | ESP32-S2 | ESP32-S3 |
| ----------------- | ----- | -------- | -------- | -------- | -------- | -------- | -------- |

# SSS Firmware

This folder contains all the firmware present on the ESP32 in the ESP-IDF language. The development environment is VSCODE with the ESP-IDF extension.

## How to use example
Git clone this folder and open in VSCODE with the ESP-IDF extension installed in .vscode/c_cpp_properties.json, change the "compilerPath" to wherever the ESP-IDF extension is installed.

## Example folder contents

The project contains several source files in C language located in folder [main](main).
.vscode and .devcontainer contain settings and configuration.

ESP-IDF projects are built using CMake. The project build configuration is contained in `CMakeLists.txt`
files that provide set of directives and instructions describing the project's source files and targets
(executable, library, or both). 

Additionally, the sample project contains Makefile and component.mk files, used for the legacy Make based build system. 
They are not used or needed when building with CMake and idf.py.
