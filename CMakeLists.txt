cmake_minimum_required(VERSION 3.16)

project(cbor LANGUAGES C)

add_executable(cbor pointer_test.c
    json.c
    cbor.c
    pointer.c )

# set(cbor
#   cbor.c
#   pointer.c
#   json.c)

# add_library(${PROJECT_NAME} STATIC ${CBOR_SRC})

install(TARGETS cbor
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
