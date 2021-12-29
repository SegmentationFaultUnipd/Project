cmake_minimum_required(VERSION 3.10)

# set the project name
project(VirtualChessboard)

# add the executable
add_executable(Scacchiera src/main.cpp src/Board.cpp src/Pieces/Knight.cpp src/Players/HumanPlayer.cpp)