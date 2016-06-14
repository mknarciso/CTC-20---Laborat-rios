#include "DynammicProgramming.h"
#include <limits>
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <algorithm>
#include <ctime>
#include <vector>

using namespace std;

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
    clock_t begin = clock();
    int startVertex = vertices.front();
    unordered_set<int> hashSet(vertices.begin(), vertices.end());
    hashSet.erase(startVertex);

    Node root;
    cost = GetMinimumCostRoute(startVertex, hashSet, root);
    clock_t end = clock();
    cout << "Elapsed time in DynammicPrograming : " << (end-begin)/1000 << "." << (end-begin)%1000 << " s" << endl;
    return TraverseTree(root, startVertex);

}
vector<int> DynammicProgramming::getBestRoute(double &cost, vector<int> &cities, int &root, int where_id){
    vector<int> result, local;
    local = cities;
    local[where_id]=-1;
    int from = where_id;
    if (root == -1)
        root = from;
    int any = 0;
    double temp_cost = -1;
    double min_cost = -1;
    int id_min = -1;
    vector<int> temp_route, min_route;
    for (int i=0;i<local.size();i++){
        if (local[i] != -1){
            any = any+1;
            temp_route = getBestRoute(temp_cost, local, root, i);
            if ((min_cost==-1) || ((temp_cost + adjacencyMatrix[from][i]) < min_cost)){

                min_cost = temp_cost + adjacencyMatrix[from][i];
                min_route = temp_route;
                id_min = i;
            }
            temp_cost = -1;
            temp_route.clear();

        }
    }
    if (any==0){
        result.push_back(root);
        result.push_back(from);
        cost = adjacencyMatrix[from][root];
        return result;
    }

    cost = min_cost;
    result = min_route;
    result.push_back(from);
    return result;

}

vector<int> DynammicProgramming::BruteForce(double &cost)
{
    clock_t begin = clock();

    int root = -1;
    vector<int> result = getBestRoute(cost,vertices, root, 0);
    reverse(result.begin(),result.end());

    clock_t end = clock();
    cout << "Elapsed time in Brute Force : " << (end-begin)/1000 << "." << (end-begin)%1000 << " s" << endl;
    return result;

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
bool DynammicProgramming::CheckHamiltonian(vector<int> &route)
{
    if (route.size() != vertices.size() + 1) {
        cout << "Grafo nao hamiltoniano." << endl;
        return false;
    }
    return true;
}

int DynammicProgramming::vertices_size()
{
    return vertices.size();
}

/*vector<int> generateVert(int order){
    vector<int> result;
    result.reserve(order);
    for(int i=0; i<order;i++){
        result[i] = i;
    }
}*/
struct c_unique {
  int current;
  c_unique() {current=0;}
  int operator()() {return current++;}
} UniqueNumber;

int main()
{
         // How to get a number.
     int order = 0;
        string input = "";
     while (true) {
       cout << "Digite a ordem do grafo para teste: ";
       std::getline(cin, input);

       // This code converts from string to number safely.
       stringstream myStream(input);
       if (myStream >> order)
         break;
       cout << "Numero invalido, tente novamente." << endl;
     }
     cout << "Gerando Grafo de ordem " << order << endl << endl;

    //exemplo hamiltoniano simple
    /*vector<int> vertics  = {0,1,2,3};
    vector<vector<double> > adjMatrix = {
        {-1, 10, 15, 20},
        {5, -1 , 9, 10},
        {6, 13, -1, 12},
        {8, 8, 9, -1},
    };*/
    //exemplo hamiltoniano
    vector<int> vertics;
    vertics.resize(order);
    generate (vertics.begin(), vertics.end(), UniqueNumber);

    vector<vector<double> > adjMatrix;
    adjMatrix.resize(order);
    for (int i = 0; i < order; ++i)
        adjMatrix[i].resize(order);
    for (int i = 0; i < order; ++i){
        for (int j = 0; j < order; ++j)
            if (i!=j)
                adjMatrix[i][j] = double(rand() % 10 +1);
            else
                adjMatrix[i][j] = -1;
    }
    // Show the randoms
    cout << "Vetor gerado : ";
    for (int i = 0; i < order; ++i)
        cout << " " << vertics[i];
    cout << endl;
    cout << "Matriz gerada : " << endl;
    for (int i = 0; i < order; ++i){
        for (int j = 0; j < order; ++j)
            cout << " " << setw(3) << adjMatrix[i][j];
        cout << endl;
    }

    //vertics =  {0,1,2,3, 4, 5, 6, 7, 8, 9};//generateVert(order); //= {0,1,2,3, 4, 5, 6, 7, 8, 9};
    /*vector<vector<double> > adjMatrix = {
        {-1, 10, 15, 20, 0, 10, 15, 20, 0 , 10},
        {5, -1 , 9, 10, 5, 0, 9, 10, 5, 9},
        {6, 13, -1, 12, 6, 13, 9, 12, 6, 13},
        {8, 8, 9, -1, 8, 8, 9, 0, 8, 8},
        {0, 10, 15, 20, -1, 10, 15, 20, 0 , 10},
        {5, 0 , 9, 10, 5, -1, 9, 10, 5, 9},
        {6, 13, 9, 12, 6, 13, -1, 12, 6, 13},
        {8, 8, 9, 0, 8, 8, 9, -1, 8, 8},
        {6, 13, 9, 12, 6, 13, 9, 12, -1, 13},
        {8, 8, 9, 0, 8, 8, 9, 0, 8, -1},
    };*/
    //exemplo nao hamiltoniano

   /* vector<int> vertics = {0,1,2,3,4,5};
    vector<vector<double> > adjMatrix = {
        {-1,-1,-1,-1,1,1},
        {-1,-1,-1,-1,1,1},
        {-1,-1,-1,-1,1,1},
        {-1,-1,-1,-1,1,1},
        {1,1,1,1,-1,-1},
        {1,1,1,1,-1,-1}
        };*/

    DynammicProgramming dynammicProgramming(vertics, adjMatrix);
    double cost, brute_cost;
    vector<int> route = dynammicProgramming.Solve(cost);
    bool isHamiltonian = true;
    isHamiltonian = dynammicProgramming.CheckHamiltonian(route);
    if (isHamiltonian) {
        // Print Dynammic Result
        cout << "Route (Dynammic) - " << vertics.size() << " verts"  << endl;
        for (const auto& elem: route)
            {cout << elem << " " ;}
        cout << endl;
        cout << "Cost: " << cost << endl << endl << endl;
        // Call and print Brute Force
        vector<int> brute_route = dynammicProgramming.BruteForce(brute_cost);
        cout << "Route (Brute) - " << vertics.size() << " verts"  << endl;
        for (const auto& elem: brute_route)
            {cout << elem << " " ;}
        cout << endl;
        cout << "Cost: " << brute_cost << endl << endl << endl;
    }

    return 0;

}
