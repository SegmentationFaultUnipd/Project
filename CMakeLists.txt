cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

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
)

# add the executable
add_executable(
    Scacchiera
    src/main.cpp
    src/Board.cpp
    src/GameManager.cpp
)

target_link_libraries(Scacchiera PUBLIC Pieces)
target_link_libraries(Scacchiera PUBLIC Players)