#include "DynammicProgramming.h"
#include <limits>
#include <iostream>

DynammicProgramming::DynammicProgramming(vector<int> verts, vector<vector<double> > matrix)
{
    //ctor
    vertices = verts;
    adjacencyMatrix = matrix;
}

DynammicProgramming::~DynammicProgramming()
{
    //dtor
}

vector<int> DynammicProgramming::Solve(double &cost)
{
    int startVertex = vertices.front();
    unordered_set<int> hashSet(vertices.begin(), vertices.end());
    hashSet.erase(startVertex);

    Node root;
    cost = GetMinimumCostRoute(startVertex, hashSet, root);
    return TraverseTree(root, startVertex);
}

double DynammicProgramming::GetMinimumCostRoute(int startVertex, unordered_set<int> &hashSet, Node &root)
{
    if (hashSet.empty()) {
        Node node;
        node.Value = vertices.front();
        node.Selected = true;
        root.ChildNodes.push_back(node);
        return adjacencyMatrix[startVertex][0];
    }

    double totalCost = numeric_limits<double>::max();
    int i = 0;
    int selectIdx = i;

    for (const auto& destination: hashSet)
    {
        Node node;
        node.Value = destination;
        node.Selected = false;
        root.ChildNodes.push_back(node);

        double costOfVisitingCurrentNode = adjacencyMatrix[startVertex][destination];

        unordered_set<int> newHashSet = hashSet;

        newHashSet.erase(destination);
        double costOfVisitingOtherNodes = GetMinimumCostRoute(destination, newHashSet, root.ChildNodes[i]);
        double currentCost = costOfVisitingCurrentNode + costOfVisitingOtherNodes;

        if (totalCost > currentCost)
        {
            totalCost = currentCost;
            selectIdx = i;
        }
        i++;
    }

    root.ChildNodes[selectIdx].Selected = true;
    return totalCost;
}

vector<int> DynammicProgramming::TraverseTree(Node &root, int startInt)
{

    queue<int> q;
    q.push(startInt);
    TraverseTreeUtil(root, q);

    vector<int> result;
    while (!q.empty())
    {
        result.push_back(q.front());
        q.pop();
    }
    return result;
}

void DynammicProgramming::TraverseTreeUtil(Node &root, queue<int> &vertics)
{
    if (root.ChildNodes.empty())
    {
        return;
    }
    for (auto& child:root.ChildNodes)
    {
        if(child.Selected)
        {
            vertics.push(child.Value);
            TraverseTreeUtil(child, vertics);
        }
    }
}

int main()
{
    vector<int> vertics  = {0,1,2,3};
    vector<vector<double> > adjMatrix = {
        {0, 10, 15, 20},
        {5, 0 , 9, 10},
        {6, 13, 9, 12},
        {8, 8, 9, 0}
    };

    DynammicProgramming dynammicProgramming(vertics, adjMatrix);
    double cost;
    vector<int> route = dynammicProgramming.Solve(cost);

    cout << "Route:" << endl;
    for (const auto& elem: route)
    {
        cout << elem << " " ;
    }
    cout << endl;

    cout << "Cost: " << cost << endl;

    return 0;

}
