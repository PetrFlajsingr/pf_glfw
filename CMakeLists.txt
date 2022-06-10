cmake_minimum_required(VERSION 3.20)
project(pf_glfw
        VERSION 0.2.0)

if (MSVC AND CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL 19.29.30129 AND CMAKE_VERSION VERSION_GREATER 3.20.3)
    set(CMAKE_CXX_STANDARD 23) # /std:c++latest - unlocks the non stable cpp20 features. For new 16.11 versions
else ()
    set(CMAKE_CXX_STANDARD 20) # /std:c++latest for msvc and -std=c++20 for everyone else.
endif ()


find_package(fmt CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(range-v3 CONFIG REQUIRED)
find_package(magic_enum CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
include_directories(${GLFW_INCLUDE_DIRS})
find_package(pf_common CONFIG REQUIRED)



set(SOURCES
        src/pf_glfw/Window.cpp
        src/pf_glfw/enums/Key.cpp
        src/pf_glfw/Cursor.cpp
        src/pf_glfw/Image.cpp
        src/pf_glfw/Monitor.cpp
        src/pf_glfw/GLFW.cpp
        src/pf_glfw/WindowHints.cpp
        src/pf_glfw/Joystick.cpp)

set(INCLUDES src/pf_glfw/Window.h
        src/pf_glfw/enums/Key.h
        src/pf_glfw/enums/KeyAction.h
        src/pf_glfw/enums/ModifierKey.h
        src/pf_glfw/enums/MouseButton.h
        src/pf_glfw/enums/CursorEntered.h
        src/pf_glfw/Cursor.h
        src/pf_glfw/Image.h
        src/pf_glfw/enums/CursorShape.h
        src/pf_glfw/Monitor.h
        src/pf_glfw/enums/Connection.h
        src/pf_glfw/concepts.h
        src/pf_glfw/structs.h
        src/pf_glfw/GLFW.h
        src/pf_glfw/fwd.h
        src/pf_glfw/enums/Error.h
        src/pf_glfw/Exception.h
        src/pf_glfw/enums/ButtonState.h
        src/pf_glfw/enums/CursorBehavior.h
        src/pf_glfw/WindowHints.h
        src/pf_glfw/constants.h
        src/pf_glfw/enums/OpenGLProfile.h
        src/pf_glfw/enums/ContextCreationAPI.h
        src/pf_glfw/enums/ContextRobustness.h
        src/pf_glfw/enums/ContextReleaseBehavior.h
        src/pf_glfw/enums/ClientAPI.h
        src/pf_glfw/enums/GamepadAxis.h
        src/pf_glfw/enums/GamepadButton.h
        src/pf_glfw/enums/JoystickHatState.h
        src/pf_glfw/enums/JoystickID.h
        src/pf_glfw/Joystick.h)

SET(CMAKE_DEBUG_POSTFIX "d" CACHE STRING "add a postfix, usually d on windows")
SET(CMAKE_RELEASE_POSTFIX "" CACHE STRING "add a postfix, usually empty on windows")
SET(CMAKE_RELWITHDEBINFO_POSTFIX "rd" CACHE STRING "add a postfix, usually empty on windows")
SET(CMAKE_MINSIZEREL_POSTFIX "s" CACHE STRING "add a postfix, usually empty on windows")

add_library(${PROJECT_NAME} STATIC ${SOURCES} ${INCLUDES})
add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})
target_compile_options(${PROJECT_NAME} PRIVATE ${flags})

include(GNUInstallDirs)

target_include_directories(${PROJECT_NAME} PUBLIC $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)
target_include_directories(${PROJECT_NAME} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>)

target_link_libraries(${PROJECT_NAME} PUBLIC pf_common::pf_common glfw)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_INCLUDE_CURRENT_DIR_IN_INTERFACE ON)


include(GenerateExportHeader)
generate_export_header(${PROJECT_NAME} EXPORT_FILE_NAME ${PROJECT_NAME}/${PROJECT_NAME_LOWER}_export.h)

set_property(TARGET ${PROJECT_NAME} PROPERTY VERSION ${PROJECT_VERSION})
set_property(TARGET ${PROJECT_NAME} PROPERTY SOVERSION ${PROJECT_VERSION_MAJOR})
set_property(TARGET ${PROJECT_NAME} PROPERTY INTERFACE_${PROJECT_NAME}_MAJOR_VERSION ${PROJECT_VERSION_MAJOR})
set_property(TARGET ${PROJECT_NAME} APPEND PROPERTY COMPATIBLE_INTERFACE_STRING ${PROJECT_NAME}_MAJOR_VERSION)


install(TARGETS ${PROJECT_NAME}
        EXPORT ${PROJECT_NAME}Targets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
        )

#install(
#        FILES
#        ${INCLUDES}
#        ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}/${PROJECT_NAME_LOWER}_export.h
#        DESTINATION
#        ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}
#        COMPONENT
#        Devel
#)

install(
        FILES
        ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}/${PROJECT_NAME_LOWER}_export.h
        DESTINATION
        ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}
        COMPONENT
        Devel
)

install(
        DIRECTORY "${CMAKE_SOURCE_DIR}/src/pf_glfw/"
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}
        FILES_MATCHING
        PATTERN "*.h"
)
install(
        FILES
        ${GENERATED_INCLUDES}
        DESTINATION
        ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}/Generated
        COMPONENT
        Devel
)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
        ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}/${PROJECT_NAME}ConfigVersion.cmake
        VERSION ${PROJECT_VERSION}
        COMPATIBILITY SameMajorVersion
)

export(EXPORT ${PROJECT_NAME}Targets
        FILE ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}/${PROJECT_NAME}Targets.cmake
        NAMESPACE ${PROJECT_NAME}::
        )

set(ConfigPackageLocation lib/cmake/${PROJECT_NAME})
install(EXPORT ${PROJECT_NAME}Targets
        FILE
        ${PROJECT_NAME}Targets.cmake
        NAMESPACE
        ${PROJECT_NAME}::
        DESTINATION
        ${ConfigPackageLocation}
        )

file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}/${PROJECT_NAME}Config.cmake
        "include($" "{CMAKE_CURRENT_LIST_DIR}/${PROJECT_NAME}Targets.cmake)"
        )

install(
        FILES
        ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}/${PROJECT_NAME}Config.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}/${PROJECT_NAME}ConfigVersion.cmake
        DESTINATION
        ${ConfigPackageLocation}
        COMPONENT
        Devel
)
