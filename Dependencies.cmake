include(cmake/CPM.cmake)
include(FetchContent)

function(Agin_setup_dependencies)

  set(BUILD_SHARED_LIBS OFF)
  set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

  set(FETCHCONTENT_QUIET FALSE)

endfunction()
