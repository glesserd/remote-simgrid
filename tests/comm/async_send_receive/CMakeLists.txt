set(EXECUTABLE_OUTPUT_PATH "${CMAKE_CURRENT_BINARY_DIR}")

add_executable(async_send_simple sender.cpp)

# Libraries to link
target_link_libraries(async_send_simple rsg)

target_link_libraries(async_send_simple "RsgService.thrift")
target_link_libraries(async_send_simple ${THRIFT_LIBRARIES})
target_link_libraries(async_send_simple ${SimGrid_LIBRARY})


add_executable(async_receive_simple receiver.cpp)

# Libraries to link
target_link_libraries(async_receive_simple rsg)

target_link_libraries(async_receive_simple "RsgService.thrift")
target_link_libraries(async_receive_simple ${THRIFT_LIBRARIES})
target_link_libraries(async_receive_simple ${SimGrid_LIBRARY})

configure_file(deploy.xml.in "${CMAKE_CURRENT_BINARY_DIR}/deploy.xml")
ADD_TESH(async_send_receive_simple --setenv resources=${TEST_RESOURCES_DIR} --setenv bindir=${RSG_BINARY_DIR} --setenv bintestdir=${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/client_test.tesh)
