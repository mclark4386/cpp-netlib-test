cmake_minimum_required (VERSION 2.8)

project(cpp-netlib-test)


if (${CMAKE_CXX_COMPILER_ID} MATCHES GNU)
  INCLUDE(CheckCXXCompilerFlag)
  CHECK_CXX_COMPILER_FLAG(-std=c++0x HAVE_STD0X)
  CHECK_CXX_COMPILER_FLAG(-std=c++11 HAVE_STD11)

  if (HAVE_STD11)
    set(CMAKE_CXX_FLAGS -std=c++11)
  elseif (HAVE_STD0X)
    set(CMAKE_CXX_FLAGS -std=c++0x)
  else()
    message(FATAL_ERROR "No advanced standard C++ support (-std=c++0x and -std=c++11 not defined).")
  endif()
endif()

FIND_PACKAGE(Boost)

IF(Boost_FOUND)
	include_directories(cpp-netlib/include ${Boost_INCLUDE_DIR})
	link_directories(${CMAKE_CURRENT_SOURCE_DIR}/cpp-netlib/libs/network/src ${Boost_LIBRARYDIR})

	add_executable(server main.cpp) 
	target_link_libraries(server cppnetlib-uri cppnetlib-server-parsers cppnetlib-client-connections)
ENDIF()
