cmake_minimum_required(VERSION 2.8)

project(autonomy)

include(ExternalProject)

ExternalProject_Add(
  CAF
  GIT_REPOSITORY https://github.com/actor-framework/actor-framework.git
  GIT_TAG master
  CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR>
)

ExternalProject_Get_Property(CAF install_dir)
set(CAF_INCLUDE_DIR ${install_dir}/include)
set(CAF_LIB_DIR ${install_dir}/lib)

ExternalProject_Add(
  GMock
  URL https://googlemock.googlecode.com/files/gmock-1.7.0.zip
  URL_HASH SHA1=f9d9dd882a25f4069ed9ee48e70aff1b53e3c5a5

  INSTALL_COMMAND ${CMAKE_COMMAND} -E make_directory <INSTALL_DIR>/lib
          COMMAND ${CMAKE_COMMAND} -E copy_if_different <BINARY_DIR>/libgmock.a <INSTALL_DIR>/lib
          COMMAND ${CMAKE_COMMAND} -E copy_if_different <BINARY_DIR>/libgmock_main.a <INSTALL_DIR>/lib
          COMMAND ${CMAKE_COMMAND} -E copy_if_different <BINARY_DIR>/gtest/libgtest.a <INSTALL_DIR>/lib
          COMMAND ${CMAKE_COMMAND} -E copy_if_different <BINARY_DIR>/gtest/libgtest_main.a <INSTALL_DIR>/lib
          COMMAND ${CMAKE_COMMAND} -E copy_directory <SOURCE_DIR>/include <INSTALL_DIR>/include
          COMMAND ${CMAKE_COMMAND} -E copy_directory <SOURCE_DIR>/gtest/include/gtest <INSTALL_DIR>/include/gtest
  )

ExternalProject_Get_Property(GMock install_dir)
set(GMOCK_INCLUDE_DIR ${install_dir}/include)
set(GMOCK_LIB_DIR ${install_dir}/lib)

include_directories( src ${CAF_INCLUDE_DIR} )
link_directories( ${CAF_LIB_DIR} )

set(CORE_LIBS -lboost_thread -lboost_serialization -lboost_system -lpthread -lcaf_core )
set(GUI_LIBS -lSDL -lSDL_mixer -lSDL_image -lSDL_gfx -lSDL_ttf)

add_compile_options(-Wall -DBOOST_SPIRIT_SINGLE_GRAMMAR_INSTANCE -DBOOST_SPIRIT_USE_OLD_NAMESPACE -fpermissive -ftemplate-depth=1024 -ftemplate-backtrace-limit=0 -std=gnu++11)

add_library(autonomy_core
  ./src/autonomy/command_registry.cpp
  ./src/autonomy/compiler/parse_node_attributes.cpp
  ./src/autonomy/compiler/parser_translator_map.cpp
  ./src/autonomy/compiler/symbol_table.cpp
  ./src/autonomy/compiler/translator_exceptions.cpp
  ./src/autonomy/compiler/translator_functors.cpp
  ./src/autonomy/compiler/type.cpp
  ./src/autonomy/universe.cpp
  ./src/autonomy/game.cpp
  ./src/autonomy/location_module.cpp
  ./src/autonomy/processor.cpp
  ./src/autonomy/script_builtins.cpp
  ./src/autonomy/script_commands.cpp
  ./src/autonomy/script_object.cpp
  )

add_library(autonomy_standard
  ./src/autonomy/standard/dui.cpp
  ./src/autonomy/standard/asteroid.cpp
  ./src/autonomy/standard/base_station.cpp
  ./src/autonomy/standard/drone.cpp
  ./src/autonomy/standard/scripted_drone.cpp
  ./src/autonomy/standard/script_library.cpp
  ./src/autonomy/standard/viewport.cpp
  ./src/autonomy/standard/create_asteroid.cpp
  ./src/autonomy/standard/create_drone.cpp
  ./src/autonomy/standard/create_station.cpp
  ./src/autonomy/standard/destroy_entity.cpp
  ./src/autonomy/standard/mine.cpp
  ./src/autonomy/standard/move.cpp
  ./src/autonomy/standard/scan.cpp
  ./src/autonomy/standard/unload.cpp
  ./src/autonomy/standard/where.cpp
  ./src/autonomy/standard/create_asteroid_default.cpp
  ./src/autonomy/standard/create_drone_default.cpp
  ./src/autonomy/standard/create_station_default.cpp
  ./src/autonomy/standard/destroy_entity_default.cpp
  ./src/autonomy/standard/mine_default.cpp
  ./src/autonomy/standard/move_default.cpp
  ./src/autonomy/standard/scan_default.cpp
  ./src/autonomy/standard/unload_default.cpp
  ./src/autonomy/standard/where_default.cpp
)

add_executable(autonomy ./src/autonomy/standard/autonomy.cpp)

target_link_libraries(autonomy autonomy_standard autonomy_core autonomy_standard ${CORE_LIBS} ${GUI_LIBS})

enable_testing()

link_directories(${GMOCK_LIB_DIR})
add_executable(test_feature_actors src/test/feature/actors.cpp)
target_include_directories(test_feature_actors PRIVATE ${GMOCK_INCLUDE_DIR})
target_link_libraries(test_feature_actors autonomy_core autonomy_standard gmock_main gtest pthread)
add_test(test_feature_actors test_feature_actors)
