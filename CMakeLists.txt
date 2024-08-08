#----------------------------------------------------------------------------
# Setup the project
cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
#set(CMAKE_C_COMPILER "/public4/soft/gcc/9.3.0/bin/gcc")  #调用自己安装的gcc，北京超用这个
#set(CMAKE_CXX_COMPILER "/public4/soft/gcc/9.3.0/bin/g++") #调用自己安装的g++，北京超用这个
#set(XercesC_LIBRARY_RELEASE "/public4/home/sc56219/soft/xerces-c-3.2.4/install/lib/libxerces-c.so")

set(PROJ_NAME LaBr3)
project(${PROJ_NAME} C CXX )#init_vis.mac
#set(CMAKE_CXX_FLAGS "-std=c++11 -Wno-deprecated") 
#-Wno-deprecated是表示 no-deprecated这类警告忽略。

#SET(CMAKE_BUILD_TYPE Debug) #编译调试版本

#----------------------------------------------------------------------------
# Find Geant4 package, activating all available UI and Vis drivers by default
# You can set WITH_GEANT4_UIVIS to OFF via the command line or ccmake/cmake-gui
# to build a batch mode only executable
#
option(WITH_GEANT4_UIVIS "Build example with Geant4 UI and Vis drivers" ON)
if(WITH_GEANT4_UIVIS)
  find_package(Geant4 REQUIRED ui_all vis_all)
else()
  find_package(Geant4 REQUIRED)
endif()
#----------------------------------------------------------------------------
# Setup Geant4 include directories and compile definitions
# Setup include directory for this project
#
include(${Geant4_USE_FILE})

#----------------------------------------------------------------------------
# Locate sources and headers for this project
# NB: headers are included so they will show up in IDEs
#
include_directories(${PROJECT_SOURCE_DIR}/include ${Geant4_INCLUDE_DIR}) #
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc   )
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh )
# file(GLOB libs  )


#----------------------------------------------------------------------------
# Add the executable, and link it to the Geant4 libraries
#

add_executable(${PROJ_NAME} main.cc ${sources} ${headers})
target_link_libraries(${PROJ_NAME} ${Geant4_LIBRARIES})#


#
#----------------------------------------------------------------------------
# Copy all scripts to the build directory, i.e. the directory in which we
# build B1. This is so that we can run the executable directly because it
# relies on these scripts being in the current working directory.
#
set(COPY_SCRIPTS
   init.mac
   init_vis.mac
   vis.mac
   run.mac
   Zjn.in
   Zjn.out
  )

foreach(_script ${COPY_SCRIPTS})
  configure_file(
    ${PROJECT_SOURCE_DIR}/${_script}
    ${PROJECT_BINARY_DIR}/${_script}
    COPYONLY
    )
endforeach()


