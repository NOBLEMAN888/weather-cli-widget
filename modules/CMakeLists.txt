add_library(
        api_processor
        api_processor/api_processor.cpp
        api_processor/api_processor.h
)
add_library(
        event_listener
        event_listener/event_listener.cpp
        event_listener/event_listener.h
)
add_library(
        output_processor
        output_processor/output_processor.cpp
        output_processor/output_processor.h
)
target_include_directories(api_processor PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
target_include_directories(event_listener PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
target_include_directories(output_processor PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
