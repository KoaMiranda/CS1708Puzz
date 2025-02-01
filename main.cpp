#include <iostream>
#include <vector>
#include <queue> //prioq
#include <unordered_set> //to hold the "explored" nodes
#include <string> //to print 2d vector 
#include <cmath>
#include <functional> //for passing q fucntion

using namespace std;

struct Node{
    vector<vector<int>> state;
    Node* parent; //needed to trace the solution path
    int cost; //g(n)
    int heuristic; //h(n)

    Node(vector<vector<int>> s, Node* p = nullptr, int c = 0, int h = 0) 
        : state(move(s)), parent(p), cost(c), heuristic(h) {}
    
    int prio() const //neeeded for priority q comparator argument https://www.geeksforgeeks.org/implement-min-heap-using-stl/
    {
        return cost + heuristic; //f(n) = g(n) + h(n)
    }
};

struct NodeComparator //for the prioq
{
    bool operator()(const Node* a, const Node* b)
    {
        return a->prio() > b->prio(); //remember "->" not "."
    }
};

/*
int manhattanHeuristic(const vector<vector<int>>& board) 
{
    //See README note 1
    int dist = 0;
    for (int i = 0; i<3; ++i) 
    {
        for (int j = 0; j<3; ++j)
        {
            int tile = board[i][j];
            if (tile != 0)
            {
                int goalRow = (tile - 1) / 3; 
                int goalCol = (tile - 1) % 3;
                dist += abs(i - goalRow) + abs(j - goalCol);
            }
        }
    }
    return dist;
}
*/

/*see README 2
int misplacedTileHeuristic(const vector<vector<int>>& board)
{
    int misplacedNum = 0;
    int counter = 1;
    for (int i = 0; i<3; ++i)
    {
        for (int j = 0; j<3; ++j)
        {
            int tile = board[i][j];
            if(tile == 0) continue;
            if(tile == counter) misplacedNum++;
        }
    }
    return misplacedNum;
}
*/

/*stringify
string boardToString(const vector<vector<int>>& board)
{
    string returnString{};
    for (int i = 0; i<3; ++i)
    {
        for (int j = 0; j<3; ++j)
        {
            returnString += to_string(board[i][j]) + ',';
        }
        returnString += "\n";
    }
    return returnString;
}
*/

//"problem" class so as to match the psuedo code variables/function
//as close as possible. ie have "problem.GOALTEST" and "problem.OPERATORS"
class Problem
{
    public:
    vector<vector<int>> initialState;
    vector<vector<int>> goalState;
    //README 5
    function<int(const vector<vector<int>>&)> chosenHeuristic;
    
    //take in initial and goal
    Problem(vector<vector<int>> init, vector<vector<int>> goal)
    : initialState(move(init)), goalState(move(goal)) {}

    bool goalTest(const vector<vector<int>>& state) const 
    {
        return state == goalState;
    }
    
    //see README 2
    int misplacedTileHeuristic(const vector<vector<int>>& board)
    {
        int misplacedNum = 0;
        int counter = 1;
        for (int i = 0; i<3; ++i)
        {
            for (int j = 0; j<3; ++j)
            {
                int tile = board[i][j];
                if(tile == 0) continue;
                if(tile == counter) misplacedNum++;
            }
        }
        return misplacedNum;
    }

    int manhattanHeuristic(const vector<vector<int>>& board) 
    {
        //See README note 1
        int dist = 0;
        for (int i = 0; i<3; ++i) 
        {
            for (int j = 0; j<3; ++j)
            {
                int tile = board[i][j];
                if (tile != 0)
                {
                    int goalRow = (tile - 1) / 3; 
                    int goalCol = (tile - 1) % 3;
                    dist += abs(i - goalRow) + abs(j - goalCol);
                }
            }
        }
        return dist;
    }

    void setHeuristic(function<int(const vector<vector<int>>&)> heuristic)
    {
        chosenHeuristic = heuristic;
    }

    //The EXPAND funtion to "create all of A's children and push" see README 4
    vector<vector<vector<int>>> expand(const vector<vector<int>>& state) const
    {
        vector<vector<vector<int>>> frontier;
        //first find the blank
        int blankRow; //{0,y}
        int blankCol; //{x,0}

        for(int i=0; i<3; ++i)
        {
            for(int j=0; j<3; ++j)
            {
                if(state[i][j] == 0)
                {
                    blankRow = i;
                    blankCol = j;
                }
            }
        }

        //hold the possible moves of the blank space
        vector<pair<int, int>> possibleMoves = {{1,0}, {-1,0}, {0,1}, {0,-1}};
        //then apply them all to the current blankspace
        for (auto [x,y] : possibleMoves)
        {
            int newRow = blankRow + x; //left  or right 1
            int newCol = blankCol + y; //up or down 1
            //now check to see if the moves were within the bounds of the board
            if (newRow >= 0 && newRow < 3 && newCol >= 0 && newCol < 3)
            {
                vector<vector<int>> newState = state;
                swap(newState[blankRow][blankCol], newState[newRow][newCol]);
                frontier.push_back(newState);
            }
        }
        return frontier;
    }
};

//h(n) = 0, see README 5
void uniformCost(priority_queue<Node*, vector<Node*>, NodeComparator>& nodes, Node* node)
{
    node->heuristic = 0;
    nodes.push(node);
}

//regular
void standardAStar(priority_queue<Node*, vector<Node*>, NodeComparator>& nodes, Node* node)
{
    nodes.push(node);
}

//general search function. see README 3
Node* genericSearch(Problem& problem, function<void(priority_queue<Node*, vector<Node*>, NodeComparator>&, Node*)> queueingFunction)
{
    //nodes = MAKE-QUEUE(MAKE-NODE(problem.INITIAL-STATE))
    priority_queue<Node*, vector<Node*>, NodeComparator> nodes;
    nodes.push(new Node(problem.initialState, nullptr, 0, problem.chosenHeuristic(problem.initialState)));

    //loop do
    //if EMPTY(nodes) then return "failure"
    while(!nodes.empty())
    {
        //node = REMOVE-FRONT(nodes)
        Node* node = nodes.top();
        nodes.pop();

        //if problem.GOAL-TEST(node.STATE) then return node
        if(problem.goalTest(node->state)) return node;

        //nodes = QUEUEING-FUNCTION(nodes, EXPAND(node, problem.OPERATORS))
        vector<vector<vector<int>>> frontier = problem.expand(node->state);
        for (const auto& newState : frontier)
        {
            int newC = node->cost+1;
            int hVal = problem.chosenHeuristic(newState);
            Node* newNode = new Node(newState, node, newC, hVal);
            queueingFunction(nodes, newNode);
        }
    }
};

//see if it makes any difference putting in global vs in main
vector<vector<int>> goalState = {{1, 2, 3}, {4, 5, 6}, {7, 8, 0}};

int main()
{
    //stuff
    return 0;
}