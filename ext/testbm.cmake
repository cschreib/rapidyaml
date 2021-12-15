set(ed ${CMAKE_CURRENT_BINARY_DIR}/subprojects) # casual ryml extern dir (these projects are not part of ryml and are downloaded and compiled on the fly)
# these are used both for testing and benchmarking
c4_require_subproject(c4fs REMOTE
    GIT_REPOSITORY https://github.com/biojppm/c4fs
    GIT_TAG master)
c4_require_subproject(libyaml REMOTE
    GIT_REPOSITORY https://github.com/yaml/libyaml
    GIT_TAG master
    OVERRIDE BUILD_TESTING OFF
    SET_FOLDER_TARGETS ext yaml)
c4_import_remote_proj(yaml-cpp ${ed}/yaml-cpp REMOTE
    GIT_REPOSITORY https://github.com/jbeder/yaml-cpp
    # the master branch regularly screws up on windows builds.
    # so use fixed pre-validated commit hashes
    GIT_TAG 587b24e2eedea1afa21d79419008ca5f7bda3bf4
    OVERRIDE YAML_CPP_BUILD_TESTS OFF YAML_CPP_BUILD_TOOLS OFF YAML_CPP_BUILD_CONTRIB OFF YAML_CPP_BUILD_INSTALL OFF
    SET_FOLDER_TARGETS ext yaml-cpp format)
set(ryml_yaml_cpp_inc ${ed}/yaml-cpp/src/include)
if(MSVC)
    target_compile_definitions(yaml-cpp PUBLIC -D_SILENCE_CXX17_ITERATOR_BASE_CLASS_DEPRECATION_WARNING)
endif()
