# CS1708Puzz
Develop a program that can solve user-enter 8-puzzles using three different heuristics.

function general-search(problem, QUEUEING-FUNCTION)
nodes = MAKE-QUEUE(MAKE-NODE(problem.INITIAL-STATE))
loop do
if EMPTY(nodes) then return "failure"
 node = REMOVE-FRONT(nodes)
if problem.GOAL-TEST(node.STATE) succeeds then return node
 nodes = QUEUEING-FUNCTION(nodes, EXPAND(node, problem.OPERATORS))
end

1. All the 3s in the Manhattan heuristic will need to be changed to a variable in order to for the puzzle to be changed to a 15, 24 etc puzz.

taking the value of the tile, subtracting 1, and dividing/modulus by n (the size of the puzzle), gives you the goalColumn/goalRow. i ran the numbers for each tile and it is correct (ie tile (7 - 1)/%3 = goalRow of 2 and goalCol of 1).

2. Just iterates through the board and counts up the value if a tile is out of place.

Okay now all the hard stuff...

3. So generic search will need the following:
- a "problem" class with at least a goal-test (see video) and an operators function (the 4 moves the blank can make)
- nodes with pop and push but i already made the class with that in mind.
- Queueing function? Does this just mean prioq and relevant comparator? hopefully
- and the queueing function needs to have the "expand" function to make the "frontier" nodes.

Also all the examples I've seen of A* have an "explored" set for optimization but the psuedo doesn't. Will try with and without to see the difference.
From the Notes:
"As we will later see, for an algorithm called A-star, it probably does not help to detect repeated states"

Also review functions wrappers/howtopassfunctions 
https://www.geeksforgeeks.org/passing-a-function-as-a-parameter-in-cpp/

4. If/when this program starts working, try to get the EXPAND function to match the psuedo code more closely. Currently: calling .expand, storing them temporarily and then looping through to create new nodes and push, it seems the psuedo wants me to have a floating EXPAND function that just does it all at once? Then the queueing function pushes the new nodes as a list?

5. Now with the knowledge of function wrappers in my backpocket, I was able not only to pass a custom queueing function to the search function, but also allow the user to select between the heuristics at runtime.

Num of times "heuristic" mispelled: 11111111