#include <iostream>
#include <vector>
#include <queue> //prioq
#include <unordered_set> //to hold the "explored" nodes
#include <string> //to print 2d vector 
#include <cmath>

using namespace std;

struct Node{
    vector<vector<int>> boardState;
    Node* parent; //
    int cost; //g(n)
    int heuristic; //h(n)

    Node(vector<vector<int>> s, Node* p = nullptr, int c = 0, int h = 0) 
        : boardState(move(s)), parent(p), cost(c), heuristic(h) {}
    
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

//stringify
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

int main()
{
    //stuff
    return 0;
}