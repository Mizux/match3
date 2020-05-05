include(GNUInstallDirs)

# Qt Setting
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Widgets REQUIRED)

file(GLOB_RECURSE _SRCS "src/*.[hc]pp")
file(GLOB_RECURSE _QRCS "data/*.qrc")

add_executable(Match3App ${_SRCS} ${_QRCS})
# note: macOS is APPLE and also UNIX !
if(APPLE)
	set_target_properties(Match3App PROPERTIES
    INSTALL_RPATH "@loader_path/../${CMAKE_INSTALL_LIBDIR}")
elseif(UNIX AND NOT APPLE)
	set_target_properties(Match3App PROPERTIES
    INSTALL_RPATH "$ORIGIN/../${CMAKE_INSTALL_LIBDIR}")
endif()
target_link_libraries(Match3App match3::Match3 Qt5::Core Qt5::Gui Qt5::Widgets)
add_executable(match3::Match3App ALIAS Match3App)

install(TARGETS Match3App EXPORT Match3Targets)
