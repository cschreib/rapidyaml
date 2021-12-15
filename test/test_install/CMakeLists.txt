cmake_minimum_required(VERSION 3.12 FATAL_ERROR)
project(ryml
    DESCRIPTION "Test project for an installed ryml"
    HOMEPAGE_URL "https://github.com/biojppm/rapidyaml"
    LANGUAGES CXX)
include(../../cmake/c4Project.cmake)
c4_project(VERSION 0.2.3
    AUTHOR "Joao Paulo Magalhaes <dev@jpmag.me>")

if(RYML_TEST_INSTALL_PACKAGE_MODE)
    find_package(ryml REQUIRED)
    add_library(ryml ALIAS ryml::ryml)
else()
    find_path(TREE_HPP tree.hpp PATH_SUFFIXES c4 REQUIRED)
    find_library(RYML_LIBRARY ryml REQUIRED)
    get_filename_component(RYML_INCLUDE_DIR "${TREE_HPP}" DIRECTORY)
    add_library(ryml UNKNOWN IMPORTED)
    set_target_properties(ryml PROPERTIES IMPORTED_LOCATION "${RYML_LIBRARY}")
    target_include_directories(ryml INTERFACE "${RYML_INCLUDE_DIR}")
endif()

enable_testing()
set(RYML_INSTALL_TEST ON)
add_subdirectory(../../test test)
