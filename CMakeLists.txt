cmake_minimum_required(VERSION 2.8)

project(autonomy)

include_directories( src )
add_compile_options(-Wall -DBOOST_SPIRIT_SINGLE_GRAMMAR_INSTANCE -DBOOST_SPIRIT_USE_OLD_NAMESPACE -fpermissive -ftemplate-depth=1024 -ftemplate-backtrace-limit=0 -std=gnu++11)

add_executable(autonomy 
  ./src/autonomy/action/create_asteroid.cpp
  ./src/autonomy/action/create_drone.cpp
  ./src/autonomy/action/create_station.cpp
  ./src/autonomy/action/destroy_entity.cpp
  ./src/autonomy/action/mine.cpp
  ./src/autonomy/action/move.cpp
  ./src/autonomy/action/scan.cpp
  ./src/autonomy/action/unload.cpp
  ./src/autonomy/action/where.cpp
  ./src/autonomy/action_handler/create_asteroid_default.cpp
  ./src/autonomy/action_handler/create_drone_default.cpp
  ./src/autonomy/action_handler/create_station_default.cpp
  ./src/autonomy/action_handler/destroy_entity_default.cpp
  ./src/autonomy/action_handler/mine_default.cpp
  ./src/autonomy/action_handler/move_default.cpp
  ./src/autonomy/action_handler/scan_default.cpp
  ./src/autonomy/action_handler/unload_default.cpp
  ./src/autonomy/action_handler/where_default.cpp
  ./src/autonomy/autonomy.cpp
  ./src/autonomy/command_registry.cpp
  ./src/autonomy/compiler/parse_node_attributes.cpp
  ./src/autonomy/compiler/parser_translator_map.cpp
  ./src/autonomy/compiler/symbol_table.cpp
  ./src/autonomy/compiler/translator_exceptions.cpp
  ./src/autonomy/compiler/translator_functors.cpp
  ./src/autonomy/compiler/type.cpp
  ./src/autonomy/dui.cpp
  ./src/autonomy/entity/asteroid.cpp
  ./src/autonomy/entity/base_station.cpp
  ./src/autonomy/entity/drone.cpp
  ./src/autonomy/entity/scripted_drone.cpp
  ./src/autonomy/entity/universe.cpp
  ./src/autonomy/game.cpp
  ./src/autonomy/location_module.cpp
  ./src/autonomy/processor.cpp
  ./src/autonomy/script_builtins.cpp
  ./src/autonomy/script_commands.cpp
  ./src/autonomy/script_object.cpp
  ./src/autonomy/script_library.cpp
  ./src/autonomy/viewport.cpp
)

target_link_libraries(autonomy -lSDL -lSDL_mixer -lSDL_image -lSDL_gfx -lSDL_ttf -lboost_thread -lboost_serialization -lboost_system -lpthread)
