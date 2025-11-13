project(HermesHTTP_LIB)

include(FetchContent)

FetchContent_Declare(
  yaml-cpp
  GIT_REPOSITORY https://github.com/jbeder/yaml-cpp.git
  GIT_TAG master
)
FetchContent_MakeAvailable(yaml-cpp)


add_library(${PROJECT_NAME} STATIC)
target_sources(
    ${PROJECT_NAME}
    PRIVATE #Sources
            http/HMS_Http.cpp
            mt/HMS_Multithread.cpp
            server/HMS_Server.cpp
            socket/HMS_Socket.cpp

    PRIVATE
        FILE_SET internalHeaders
        TYPE HEADERS
        FILES
            http/HMS_Http.h
            mt/HMS_Multithread.h
            server/HMS_Server.h
            socket/HMS_Socket.h

    INTERFACE
        FILE_SET consumerHeaders
        TYPE HEADERS
        BASE_DIRS
            ${PROJECT_SOURCE_DIR}
        FILES
            Hermes.h
)

target_precompile_headers(${PROJECT_NAME} PRIVATE utility/HMS_pch.h)
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME} PUBLIC yaml-cpp::yaml-cpp) 

