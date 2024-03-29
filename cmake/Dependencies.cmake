set(${PROJECT_NAME}_LINKER_LIBS)

set(${PROJECT_NAME}_INSTALL_INCLUDE_PREFIX include)
set(${PROJECT_NAME}_INSTALL_LIB_PREFIX lib)
set(${PROJECT_NAME}_INSTALL_BIN_PREFIX bin)

if (${USE_OpenCV})
  find_package(OpenCV PATHS ${OpenCV_DIR} NO_DEFAULT_PATH QUIET COMPONENTS core highgui imgproc imgcodecs videoio)
  if (NOT OpenCV_FOUND) # if not OpenCV 3.x, then try to find OpenCV 2.x in default path
    find_package(OpenCV REQUIRED QUIET COMPONENTS core highgui imgproc)
  endif ()
  if (${OpenCV_VERSION} VERSION_GREATER "2.4.13")
    find_package(OpenCV REQUIRED QUIET COMPONENTS core highgui imgproc imgcodecs videoio)
  endif ()
  include_directories(SYSTEM ${OpenCV_INCLUDE_DIRS})
  list(APPEND ${PROJECT_NAME}_LINKER_LIBS ${OpenCV_LIBS})
  message(STATUS "Found OpenCV: ${OpenCV_CONFIG_PATH} (found version ${OpenCV_VERSION})")
  add_definitions(-DUSE_OpenCV)
endif ()

if (UNIX)
  if (NOT APPLE AND NOT ANDROID)
    find_package(Threads QUIET)
    if (CMAKE_THREAD_LIBS_INIT)
      list(APPEND ${PROJECT_NAME}_LINKER_LIBS ${CMAKE_THREAD_LIBS_INIT})
    else ()
      message(FATAL_ERROR "Could not find threads")
    endif ()
  endif ()
endif ()
