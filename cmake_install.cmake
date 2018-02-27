# Install script for directory: /Users/fehedwasti/Documents/University/1st Year/robotics/Simulator_Release_180107/Client/applications

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/Users/fehedwasti/Documents/University/1st Year/robotics/Simulator_Release_180107/Client/applications/Task1/cmake_install.cmake")
  include("/Users/fehedwasti/Documents/University/1st Year/robotics/Simulator_Release_180107/Client/applications/Task2/cmake_install.cmake")
  include("/Users/fehedwasti/Documents/University/1st Year/robotics/Simulator_Release_180107/Client/applications/Task3/cmake_install.cmake")
  include("/Users/fehedwasti/Documents/University/1st Year/robotics/Simulator_Release_180107/Client/applications/MidTerm/cmake_install.cmake")
  include("/Users/fehedwasti/Documents/University/1st Year/robotics/Simulator_Release_180107/Client/applications/TheRace/cmake_install.cmake")
  include("/Users/fehedwasti/Documents/University/1st Year/robotics/Simulator_Release_180107/Client/applications/groupC2_MidTerm/cmake_install.cmake")

endif()

