project(DecCore)

SET(DecCore_HEADERS
    src/Database/DatabaseId.hpp
    src/Database/ObjectDatabase.hpp
    src/Graph/DependencyNode.hpp
    src/Graph/GraphController.hpp
    src/Log/ConsoleLogger.hpp
    src/GlobalEnvironment.hpp
)

SET(DecCore_SOURCES
    src/Database/DatabaseId.cpp
    src/Database/ObjectDatabase.cpp
    src/Graph/DependencyNode.cpp
    src/Graph/GraphController.cpp
    src/Log/ConsoleLogger.cpp
    src/GlobalEnvironment.cpp
    src/Main.cpp
)

#ToDo: Change this to static lib at some point, it's setup as an executable to make testing easier in these early stages.
add_executable(DecCore ${DecCore_SOURCES} ${DecCore_HEADERS})

target_link_libraries(DecCore DecFramework)

target_include_directories(DecCore
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)