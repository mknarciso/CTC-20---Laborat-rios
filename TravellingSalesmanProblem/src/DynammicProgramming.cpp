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

    for (const auto& destination: hashSet)    {


        if (adjacencyMatrix[startVertex][destination] != -1) {
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
    }
    //problema here
    if (root.ChildNodes.size() !=0)
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
    //exemplo hamiltoniano
    /*vector<int> vertics  = {0,1,2,3, 4, 5, 6, 7, 8, 9};
    vector<vector<double> > adjMatrix = {
        {0, 10, 15, 20, 0, 10, 15, 20, 0 , 10},
        {5, 0 , 9, 10, 5, 0, 9, 10, 5, 9},
        {6, 13, 9, 12, 6, 13, 9, 12, 6, 13},
        {8, 8, 9, 0, 8, 8, 9, 0, 8, 8},
        {0, 10, 15, 20, 0, 10, 15, 20, 0 , 10},
        {5, 0 , 9, 10, 5, 0, 9, 10, 5, 9},
        {6, 13, 9, 12, 6, 13, 9, 12, 6, 13},
        {8, 8, 9, 0, 8, 8, 9, 0, 8, 8},
        {6, 13, 9, 12, 6, 13, 9, 12, 6, 13},
        {8, 8, 9, 0, 8, 8, 9, 0, 8, 8},
    };*/
    //exemplo nao hamiltoniano

    vector<int> vertics = {0,1,2,3,4,5};
    vector<vector<double> > adjMatrix = {
        {-1,-1,-1,-1,1,1},
        {-1,-1,-1,-1,1,1},
        {-1,-1,-1,-1,1,1},
        {-1,-1,-1,-1,1,1},
        {1,1,1,1,-1,-1},
        {1,1,1,1,-1,-1}
        };


    DynammicProgramming dynammicProgramming(vertics, adjMatrix);
    double cost;
    vector<int> route = dynammicProgramming.Solve(cost);
    if (route.size() != vertics.size()) {
        cout << "Cara, Não é hamiltoniano";
        return 0;
    }

    cout << "Route:" << endl;
    for (const auto& elem: route)
    {
        cout << elem << " " ;
    }
    cout << endl;

    cout << "Cost: " << cost << endl;

    return 0;

}
