#include "LogicGates.h"
#include <cmath>
#include <iostream>

LogicGates::LogicGates(LOGIC_GATE LG, int fanInValue)
{
    //ctor
    this->fanIn = fanInValue;
        for (int j = 0; j < fanInValue +2; j++)
        {
            if (j == 0)
            {
                if (LG == LOGIC_GATE::AND)
                    this->neuralNewtork.push_back(10 + fanIn*(-20));
                else if (LG == LOGIC_GATE::NOT)
                    this->neuralNewtork.push_back(10);
                else if (LG == LOGIC_GATE::OR)
                    this->neuralNewtork.push_back(-10);
                else if (LG == LOGIC_GATE::NAND)
                    this->neuralNewtork.push_back(-10 + fanIn*20);
                else if (LG == LOGIC_GATE::NOR)
                    this->neuralNewtork.push_back(10);
            }
            else if (j != fanInValue + 1)
            {
                if (LG == LOGIC_GATE::AND)
                    this->neuralNewtork.push_back(20);
                else if (LG == LOGIC_GATE::NOT)
                    this->neuralNewtork.push_back(-20);
                else if (LG == LOGIC_GATE::OR)
                    this->neuralNewtork.push_back(20);
                else if (LG == LOGIC_GATE::NAND)
                    this->neuralNewtork.push_back(-20);
                else if (LG == LOGIC_GATE::NOR)
                    this->neuralNewtork.push_back(-20);
            }
            else
                this->neuralNewtork.push_back(0);
        }
}

LogicGates::~LogicGates()
{
    //dtor
}

int LogicGates::solve(vector<int> signals)
{
    double value = 0;
    value = 1 * neuralNewtork[0];
    for (int i = 1; i < this->fanIn + 1; i++)
    {
        value += signals[i-1] * neuralNewtork[i];
    }
    double signal = 1.0/(1.0+exp(-value));
    if (signal > 0.5)
        return 1;
    return 0;
}
void backtrack (int n, vector<int> enterSignals, LogicGates *logicGate)
{
    if (n == enterSignals.size()) {
        for (auto& elem: enterSignals) {
            cout << " " << elem;
        }
        cout << ": " << logicGate->solve(enterSignals) << endl;

        return;
    }
    enterSignals[n] = 1;
    backtrack(n+1, enterSignals, logicGate);

    enterSignals[n] = 0;
    backtrack(n+1, enterSignals, logicGate);
}

void LogicGates::generateTruthTable()
{
    vector<int> enterSignals;
    for (int i = 0; i < this->fanIn; i++)
    {
        enterSignals.push_back(0);
    }
    cout << "NEURAL NETWORK:" << endl;
    for (auto& elem: this->neuralNewtork)
    {
        cout << elem << " ";
    }
    cout << endl;
    cout << "TRUTH TABLE:" << endl;
    backtrack (0, enterSignals, this);
    cout << endl;
}

int main()
{
     //AND
     cout << "AND:" <<endl;
    LogicGates logicGate(LOGIC_GATE::AND, 2);
    logicGate.generateTruthTable();
    cout << "NOT:" << endl;
    //NOT
    LogicGates logicGateNOT (LOGIC_GATE::NOT);
    logicGateNOT.generateTruthTable();
    cout << "OR:" << endl;
    //OR
    LogicGates logicGateOR (LOGIC_GATE::OR, 3);
    logicGateOR.generateTruthTable();
    cout << "NAND:" << endl;
    //NAND
    LogicGates logicGateNAND(LOGIC_GATE::NAND, 4);
    logicGateNAND.generateTruthTable();
    cout << "NOR:" << endl;
    //NOR
    LogicGates logicGateNOR (LOGIC_GATE::NOR, 5);
    logicGateNOR.generateTruthTable();



}
