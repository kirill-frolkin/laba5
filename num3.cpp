#include <iostream>
#include "zadanye3_1.h"
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

Doing returnEnam(string a);

bool identity(vector<string> towns, string town)
{
    for (string item : towns)
    {
        if (item == town)
        {
            return true;
        }
    }
    return false;
}

void CREATE_TRAIN_Function(map<string, vector<string>> &tramvai)
{
    string name, station;
    int count_stations;
    vector<string> stansions;
    cin >> name;
    cin >> count_stations;
    if (tramvai.count(name) == 0)
    {
        for (int i = 0; i < count_stations; i++)
        {
            cin >> station;
            stansions.push_back(station);
        }
        tramvai[name] = stansions;
        if (stansions.size() == 1)
        {
            cout << "Нельзя создать поезд с 1 остановкой \n";
        }
        else if (stansions.size() == 2 && stansions[0] == stansions[1])
        {
            cout << "Ошибка: Поезд не может быть создан с двумя одинаковыми остановками";
        }
        else
            cout << "Поезд с именем:" << name << " Создан \n";
    }
    else
    {
        cout << "Такой поезд уже есть \n";
    }
}

void TRAINS_FOR_TOWN_Functions(map<string, vector<string>> &tramvai)
{
    string town;
    cin >> town;
    bool isDone = false;
    cout << "Через город " << town << " проходят поезда: ";
    for (pair<string, vector<string>> item : tramvai)
    {
        if (identity(item.second, town))
        {
            cout << item.first;
            isDone = true;
        }
    }
    if (!isDone)
    {
        cout << "Через город " << town << " не проходят поезда";
    }
    cout << "\n";
}

void TOWNS_FOR_TRAIN_Functions(map<string, vector<string>> &tramvai)
{
    string train;
    cin >> train;
    bool isDone = false;
    cout << "Поезд " << train << "идет через города: ";
    for (string item : tramvai[train])
    {
        cout << item;
        isDone = true;
    }
    cout << '\n';
    if (!isDone)
    {
        cout << "Такого поезда нет \n";
        tramvai.erase(train);
    }
}

void TRAINS_Function(map<string, vector<string>> &tramvai)
{
    if (tramvai.empty())
    {
        cout << "Ошибка: Поезда не найдены \n";
    }
    else
    {
        for (pair<string, vector<string>> item : tramvai)
        {
            cout << item.first << ": ";
            for (string el : item.second)
            {
                cout << el << " ";
            }
        }
    }
}

int main()
{
    map<string, vector<string>> tramvai; // пара<Название, Список остановок>
    string commands;
    while (true)
    {
        cin >> commands;
        switch (returnEnam(commands))
        {
        case Doing::CREATE_TRAIN:
            CREATE_TRAIN_Function(tramvai);
            break;
        case Doing::TRAINS_FOR_TOWN:
            TRAINS_FOR_TOWN_Functions(tramvai);
            break;
        case Doing::TOWNS_FOR_TRAIN:
            TOWNS_FOR_TRAIN_Functions(tramvai);
            break;
        case Doing::TRAINS:
            TRAINS_Function(tramvai);
            break;
        default:
            cout << "Нет такой команды \n";
            break;
        }
    }
}

Doing returnEnam(string a)
{
    if (a == "CREATE_TRAIN")
        return Doing::CREATE_TRAIN;
    if (a == "TRAINS_FOR_TOWN")
        return Doing::TRAINS_FOR_TOWN;
    if (a == "TOWNS_FOR_TRAIN")
        return Doing::TOWNS_FOR_TRAIN;
    if (a == "TRAINS")
        return Doing::TRAINS;
    else
        return Doing::EMPTY;
}