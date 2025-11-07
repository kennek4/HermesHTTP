project(HermesHTTP_LIB)

add_library(${PROJECT_NAME})
target_sources(
    ${PROJECT_NAME}
    PRIVATE #Sources
            socket/HMS_TCPSocket.cpp
        
    PRIVATE
        FILE_SET internalHeaders
        TYPE HEADERS
        BASE_DIRS
            socket
        FILES
            socket/HMS_TCPSocket.h

    INTERFACE
        FILE_SET consumerHeaders
        TYPE HEADERS
        BASE_DIRS
            ${PROJECT_SOURCE_DIR}
        FILES
            Hermes.h
)
