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