project(HermesHTTP)

add_executable(${PROJECT_NAME})
target_sources(
    ${PROJECT_NAME}
    PRIVATE
        main.cpp        
)

target_link_libraries(${PROJECT_NAME} HermesHTTP_LIB)

