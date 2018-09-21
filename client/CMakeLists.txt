#1.cmake verson, 3.9.1
cmake_minimum_required(VERSION 3.9)

#2.project name
PROJECT(client CXX C)
#add_compile_options(-Wall -std=c++11 -lpthread)
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11" )

#3.head file path
INCLUDE_DIRECTORIES(
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
    ${CMAKE_CURRENT_SOURCE_DIR}/../third_party/inc
)

#4.source directory
AUX_SOURCE_DIRECTORY(
    ${CMAKE_CURRENT_SOURCE_DIR} DIR_SRCS
)
ADD_SUBDIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/src)

##5.set environment variable
##SET(
 #   TEST_MATH ${DIR_SRCS}
#)

#6.add executable file，添加要编译的可执行文件
ADD_EXECUTABLE(${PROJECT_NAME} ${DIR_SRCS})

#7.add link library
TARGET_LINK_LIBRARIES(${PROJECT_NAME} client_)


