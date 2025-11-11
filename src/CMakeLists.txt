project(HermesHTTP)

add_executable(${PROJECT_NAME})
target_sources(
    ${PROJECT_NAME}
    PRIVATE
        HermesHTTP.cpp
        main.cpp

    PRIVATE
        FILE_SET internalHeaders
        TYPE HEADERS
        FILES
            HermesHTTP.h

)
target_link_libraries(${PROJECT_NAME} HermesHTTP_LIB)

