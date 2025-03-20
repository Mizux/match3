set(NAME Signal_UT)

file(GLOB _SRCS "src/*.[hc]pp")

add_executable(${NAME} ${_SRCS})
# note: macOS is APPLE and also UNIX !
if(APPLE)
  set_target_properties(${NAME} PROPERTIES
    INSTALL_RPATH "@loader_path/../${CMAKE_INSTALL_LIBDIR}")
elseif(UNIX AND NOT APPLE)
  set_target_properties(${NAME} PROPERTIES
    INSTALL_RPATH "$ORIGIN/../${CMAKE_INSTALL_LIBDIR}")
endif()
target_link_libraries(${NAME} PRIVATE
  ${PROJECT_NAMESPACE}::Signal Catch2)
add_test(NAME ${NAME} COMMAND ${NAME})
add_test(NAME Signal::Signal COMMAND ${NAME} \[Signal\])
add_test(NAME Signal::Property COMMAND ${NAME} \[Property\])
