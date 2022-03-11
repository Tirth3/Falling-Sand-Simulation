# Falling-Sand-Simulation
Noita like sand falling simulation in SFML

# Introduction
Press S to get sand block or press D to get rock block 
And Left click to add blocks to screen


This program just creates a bunch of sand particles which a updated by this rules

  1. If square below is free go down
  2. Else look the square which is at position (i - 1 , j + 1) and (i + 1 , j + 1) the go to the free square
  3. If the square at postion (i - 1 , j + 1) or (i + 1 , j + 1) is free then choose the square to randomly
  

