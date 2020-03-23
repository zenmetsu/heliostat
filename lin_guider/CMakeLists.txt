#configure_file(config.h.in "${CMAKE_CURRENT_BINARY_DIR}/../config.h" @ONLY)


if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

project(heliostat-server)

find_package(Qt5 5.7.0 REQUIRED COMPONENTS
    Core
    Widgets
)

set(CMAKE_AUTOMOC ON)

add_executable(
    heliostat-server 
    	server.cpp
	utils.cpp
)

target_link_libraries(heliostat-server 
	Qt5::Core
	Qt5::Widgets
	pthread
)


install(
	TARGETS heliostat-server 
	RUNTIME DESTINATION "${INSTALL_BIN_DIR}" COMPONENT bin
)
