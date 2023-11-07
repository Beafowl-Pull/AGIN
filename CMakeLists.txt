cmake_minimum_required(VERSION 3.21)

# This template attempts to be "fetch_content"-able
# so that it works well with tools like CPM or other
# manual dependency management

# Only set the cxx_standard if it is not set by someone else
if (NOT DEFINED CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 20)
endif()

# Set the project name and language
project(
  Agin
  VERSION 0.0.1
  DESCRIPTION ""
  HOMEPAGE_URL "https://github.com/UwUClub/R-Type"
  LANGUAGES CXX C)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

add_library(Agin_warnings INTERFACE)

include(cmake/CompilerWarnings.cmake)
Agin_set_project_warnings(
        Agin_warnings
        FALSE
        ""
        ""
        ""
        "")

include(Dependencies.cmake)
Agin_setup_dependencies()

include(cmake/StandardProjectSettings.cmake)

add_library(Agin::Agin_warnings ALIAS Agin_warnings)

# Adding the src:
add_subdirectory(src)

# Adding the tests:
# include(CTest)

if(BUILD_TESTING)
  add_subdirectory(test)
endif()

include(InstallRequiredSystemLibraries)

set(CPACK_PACKAGE_NAME "Agin")
if(NOT DEFINED CPACK_PACKAGE_VERSION)
    set(CPACK_PACKAGE_VERSION ${CMAKE_PROJECT_VERSION})
endif()
set(CPACK_PACKAGE_FILE_NAME
    "${CMAKE_PROJECT_NAME}-${CMAKE_PROJECT_VERSION}-${GIT_SHORT_SHA}-${CMAKE_SYSTEM_NAME}-${CMAKE_BUILD_TYPE}-${CMAKE_CXX_COMPILER_ID}-${CMAKE_CXX_COMPILER_VERSION}"
)
set(CPACK_PACKAGE_INSTALL_DIRECTORY "Agin")
set(CPACK_PACKAGE_CONTACT "Agin")

if(WIN32)
    set(CPACK_GENERATOR "NSIS64")
else()
    set(CPACK_GENERATOR "DEB;RPM")
endif()

include(CPack)