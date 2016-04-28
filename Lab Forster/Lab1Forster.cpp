#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <map>


using namespace std;

int main()
{

    for (int i = 1 ; i <= 8 ; i++)
    {
        //Read from files
        ifstream myFile;
        stringstream ss;
        ss << i;
        string nameTable = "table " + ss.str() + ".txt";
        const char* c = nameTable.c_str();
        myFile.open (c, ifstream::in);
        vector <string> table;
        string row;
        getline(myFile, row);
        table.push_back(row);
        while (!myFile.eof())
        {
            getline(myFile,row);
            table.push_back(row);
        }
        vector<string>::iterator it;
        cout << "Table " + ss.str() + ":" << endl;
        for (it = table.begin(); it != table.end(); it++)
        {
            cout << *it << endl;
        }
        cout << endl;

        //Verificação 1 - Nas linhas
        map <char,int> temp;
        bool isGroup = true;
        for (int i = 0; i < table[0].length() && isGroup; i++)
        {
            temp[table[0][i]] = 1;
        }

        for (int i = 1; i < table.size() && isGroup; i++)
        {
            for (int j = 0; j < table[i].length() && isGroup; j++)
            {
                if (temp[table[i][j]] == i)
                {
                    temp[table[i][j]] += 1;
                }
                else
                {
                    isGroup = false;
                    cout << "Elemento " << table[i][j] << " foge do criterio de grupo" << endl;
                    break;
                }
            }
        }
        map<char,int>::iterator it2;
        for (it2 = temp.begin(); it2 != temp.end() && isGroup; it2++)
        {
            if (it2->second != table.size())
            {
                isGroup = false;
                break;
            }
        }
        //Verificação 2 - Colunas
        temp.clear();
        for (int i = 0; i < table.size() && isGroup; i++)
        {
            temp[table[i][0]] = 1;
        }
        for (int i = 1; i < table[0].length() && isGroup; i++)
        {
            for (int j = 0; j < table.size() && isGroup; j++)
            {
                if (temp[table[j][i]] == 1)
                {
                    temp[table[j][i]] += 1;
                }
                else
                {
                    isGroup = false;
                    cout << "Elemento " << table[j][i] << " foge do critério de grupo" << endl;
                    break;
                }
            }
        }


    }
    return 0;
}
