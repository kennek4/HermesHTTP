project(HermesHTTP_LIB)

add_library(${PROJECT_NAME} STATIC)
target_sources(
    ${PROJECT_NAME}
    PRIVATE #Sources
            mt/HMS_Multithread.cpp
            socket/HMS_Socket.cpp

    PRIVATE
        FILE_SET internalHeaders
        TYPE HEADERS
        FILES
            mt/HMS_Multithread.h
            socket/HMS_Socket.h

    INTERFACE
        FILE_SET consumerHeaders
        TYPE HEADERS
        BASE_DIRS
            ${PROJECT_SOURCE_DIR}
        FILES
            Hermes.h
)

target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR})
