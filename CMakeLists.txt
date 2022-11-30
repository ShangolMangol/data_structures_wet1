cmake_minimum_required(VERSION 3.22)
project(wet1)

set(CMAKE_CXX_STANDARD 11)

add_executable(wet1 main.cpp worldcup23a1.cpp worldcup23a1.h wet1util.h AVLTree.h ComparePlayerById.cpp ComparePlayerById.h Player.cpp Player.h Team.cpp Team.h CompareTeamById.cpp CompareTeamById.h ComparePlayerByScore.cpp ComparePlayerByScore.h CompareValidTeamById.cpp CompareValidTeamById.h CompareTeamPlayerByScore.cpp CompareTeamPlayerByScore.h)

add_executable(formalTest main23a1.cpp worldcup23a1.cpp worldcup23a1.h wet1util.h AVLTree.h ComparePlayerById.cpp ComparePlayerById.h Player.cpp Player.h Team.cpp Team.h CompareTeamById.cpp CompareTeamById.h ComparePlayerByScore.cpp ComparePlayerByScore.h CompareValidTeamById.cpp CompareValidTeamById.h CompareTeamPlayerByScore.cpp CompareTeamPlayerByScore.h)
