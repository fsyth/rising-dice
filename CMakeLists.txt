cmake_minimum_required (VERSION 3.8)

project ("QuestRoller")


# Common source code.

add_library (QuestLib
 "Available.hpp"
 "Available.cpp"
 "Choice.hpp"
 "Choice.cpp"
 "GameState.hpp"
 "play.hpp"
 "play.cpp"
)
target_compile_features (QuestLib PRIVATE cxx_std_17)


# Executable for an interactive game playable as a human.

add_executable (QuestRoller
 "Color.hpp"
 "displayGameState.hpp"
 "displayGameState.cpp"
 "playerStrategy.hpp"
 "playerStrategy.cpp"
 "main_play.cpp"
)
target_compile_features (QuestRoller PRIVATE cxx_std_17)
target_link_libraries   (QuestRoller QuestLib)


# Executable for evaulating different strategies.

add_executable (QuestTester
 "displaySolverResults.hpp"
 "displaySolverResults.cpp"
 "solve.hpp"
 "solve.cpp"
 "solverStrategy.hpp"
 "solverStrategy.cpp"
 "miscStrategies.hpp"
 "miscStrategies.cpp"
 "main_test.cpp"
)
target_compile_features (QuestTester PRIVATE cxx_std_17)
target_link_libraries   (QuestTester QuestLib)
