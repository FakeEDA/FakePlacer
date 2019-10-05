cmake_minimum_required(VERSION 3.5)
project(fakeplacer VERSION 1.0.0 LANGUAGES CXX)

list(INSERT CMAKE_MODULE_PATH 0 ${CMAKE_SOURCE_DIR}/cmake)

add_library(fakeplacer
    src/fakeplacer.cpp
)

add_library(FakePlacer::fakeplacer ALIAS fakeplacer)

target_compile_features(fakeplacer PRIVATE cxx_auto_type)
target_compile_options(fakeplacer PRIVATE $<$<CXX_COMPILER_ID:GNU>:-Wall>)

# find opendb package
find_package(FakeDB 1.0 REQUIRED)
find_package(FakeTimer 1.0 REQUIRED)

target_include_directories(fakeplacer
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${PROJECT_BINARY_DIR}/include
        /usr/local/include
)

target_link_libraries(fakeplacer
    PRIVATE
        fakedb
        faketimer
)

include(GNUInstallDirs)
set(INSTALL_CONFIGDIR ${CMAKE_INSTALL_LIBDIR}/cmake/FakePlacer)

install(TARGETS fakeplacer
    EXPORT fakeplacer-targets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

set_target_properties(fakeplacer PROPERTIES EXPORT_NAME FakePlacer)

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(EXPORT fakeplacer-targets
  FILE
    FakePlacerTargets.cmake
  NAMESPACE
    FakePlacer::
  DESTINATION
    ${INSTALL_CONFIGDIR}
)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/FakePlacerConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
)

configure_package_config_file(${CMAKE_CURRENT_LIST_DIR}/cmake/FakePlacerConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/FakePlacerConfig.cmake
    INSTALL_DESTINATION ${INSTALL_CONFIGDIR}
)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/FakePlacerConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/FakePlacerConfigVersion.cmake
    DESTINATION ${INSTALL_CONFIGDIR}
)

export(EXPORT fakeplacer-targets FILE ${CMAKE_CURRENT_BINARY_DIR}/FakePlacerTargets.cmake NAMESPACE FakePlacer::)

export(PACKAGE FakePlacer)