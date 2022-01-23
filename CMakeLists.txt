cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_CXX_FLAGS, "-O2")
set(CMAKE_CXX_FLAGS_DEBUG, "-O2")
set(CMAKE_CXX_FLAGS_RELEASE, "-O2")

# set the project name
project(VirtualChessboard)

# add pieces
add_library(
    Pieces
    src/Pieces/Piece.cpp
    src/Pieces/Knight.cpp
    src/Pieces/King.cpp
    src/Pieces/Rook.cpp
    src/Pieces/Pawn.cpp
    src/Pieces/Bishop.cpp
    src/Pieces/Queen.cpp
)

# add players
add_library(
    Players
    src/Players/HumanPlayer.cpp
    src/Players/ComputerPlayer.cpp
	src/Players/ReplayPlayer.cpp
)

# add the executable
add_executable(
    scacchiera
    src/main.cpp
    src/Board.cpp
    src/GameManager.cpp
)

add_executable(
    replay
    src/Replay.cpp
    src/Board.cpp
    src/ReplayManager.cpp
)

target_link_libraries(scacchiera PUBLIC Pieces)
target_link_libraries(scacchiera PUBLIC Players)

target_link_libraries(replay PUBLIC Pieces)
target_link_libraries(replay PUBLIC Players)
