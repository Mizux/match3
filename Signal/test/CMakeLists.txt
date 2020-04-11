set(NAME Signal_UT)

file(GLOB _SRCS "src/*.[hc]pp")

add_executable(${NAME} ${_SRCS})
target_link_libraries(${NAME} Catch Signal)
add_test(NAME ${NAME} COMMAND ${NAME})
add_test(NAME Signal::Signal COMMAND ${NAME} \[Signal\])
add_test(NAME Signal::Property COMMAND ${NAME} \[Property\])
