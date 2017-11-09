#BEAST

add_library(beast INTERFACE)

target_include_directories(beast INTERFACE include) 

target_link_libraries(beast INTERFACE boost)