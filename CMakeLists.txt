# Name Abaci Client
# Date: Jan 23, 2020
# Version: 0.1a
# Target: Mr. Di Tomasso
# Programer: Ty Lamontagne
# File Purpose: This file sets up the compiler / linker flags and copies the QT libraries to the 
#				required output folder. To build and send the .exe file elsewhere look at the Abaci Client Document
cmake_minimum_required (VERSION 3.8)

project (Abaci_Client)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(WIN32)
set(CMAKE_PREFIX_PATH "C://Qt/5.12.5/msvc2017_64/lib/cmake")

set(GUI_TYPE WIN32)

endif()
find_package(Qt5 COMPONENTS Widgets Core Sql Network REQUIRED) # Search for QT5

set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_executable(Abaci_Client ${GUI_TYPE} main.cpp 
gui/MainWindow.cpp gui/MainWindow.h gui/MainWindow.ui WorkerThread.h Primes/PrimeClass.h 
Primes/PrimeClass.cpp Client.h gui/EditClient.cpp gui/EditClient.h gui/EditClient.ui)

target_include_directories(Abaci_Client PUBLIC Qt5_INCLUDE_DIRS)
target_link_libraries(Abaci_Client Qt5::Widgets Qt5::Core Qt5::Network)
if(WIN32)
	add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Core> $<TARGET_FILE_DIR:${PROJECT_NAME}>
		COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Gui> $<TARGET_FILE_DIR:${PROJECT_NAME}>
		COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Widgets> $<TARGET_FILE_DIR:${PROJECT_NAME}> 
		COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Network> $<TARGET_FILE_DIR:${PROJECT_NAME}> )
endif(WIN32)