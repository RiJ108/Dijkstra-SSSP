# Dijkstra-SSSP
Program that execute the Dijkstra algorythm of single source shortest path.
The program work with index.
To get a graph to the program, edit the data.txt file following the rules:
1. the first line of the file is "number of state-index of the initial state-index of the goal state"
2. for each transition, add a line as "index of the source/cost of the transition/index of the destination"

For exemple, the following graph:

![GitHub Logo](/graph.png)

Translate to the following data.txt:

6-0-5
0/2/1
0/4/2
1/1/2
1/7/3
2/3/4
4/2/3
4/5/5
3/1/5
