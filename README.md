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

Also I dont REALLY understand how taking the value of the tile, subtracting 1, and dividing/modulus by n (the size of the puzzle), gives you the goalColumn/goalRow BUT i ran the numbers for each tile and it is correct (ie tile (7 - 1)/%3 = goalRow of 2 and goalCol of 1).