find_package(Qt5 COMPONENTS Core REQUIRED)
add_library(digikam_shims OBJECT src/digikam_globals.cpp src/digikam_version.cpp)
target_include_directories(digikam_shims PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(digikam_shims PRIVATE Qt5::Core)
