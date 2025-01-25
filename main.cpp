#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Node{
    vector<vector<int>> boardState;
    Node* parent; //
    int cost; //g(n)
    int heuristic; //h(n)

    Node(vector<vector<int>> s, Node* p = nullptr, int c = 0, int h = 0) 
        : boardState(s), parent(p), cost(c), heuristic(h) {}
    
    int prio() const //neeeded for priority q comparator argument https://www.geeksforgeeks.org/implement-min-heap-using-stl/
    {
        return cost + heuristic; //f(n) = g(n) + h(n)
    }
};

struct NodeComparator //for the prioq
{
    bool operator()(const Node* a, const Node* b)
    {
        return a->prio() > b->prio(); //remember why "->" not "."
    }
};

int main()
{
    //stuff
    return 0;
}