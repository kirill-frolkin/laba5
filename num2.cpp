#include <iostream>
#include <vector>
#include "zadanye2_1.h"

using namespace std;

Doing returnEnam(string a)
{
    if (a == "ENQUEUE")
        return Doing::ENQUEUE;
    if (a == "DISTRIBUTE")
        return Doing::DISTRIBUTE;
    return Doing::EMPTY;
};

int min(vector<int> sums)
{
    int min = sums[0];
    int index = 0;
    for (size_t i = 0; i < sums.size(); ++i)
    {
        if (sums[i] < min)
        {
            min = sums[i];
            index = i;
        }
    }
    return index;
}

int sum(vector<pair<string, int>> a)
{
    int result = 0;
    for (pair<string, int> item : a)
    {
        result += item.second;
    }
    return result;
}

int main()
{
    vector<pair<string, int>> allQueue;
    int time, number = 1, windows_count;
    string command, talon;
    cout << "Введите количество окон: \n";
    cin >> windows_count;
    vector<vector<pair<string, int>>> windows(windows_count);

    while (true)
    {
        cin >> command;
        if (returnEnam(command) == Doing::ENQUEUE)
        {
            cin >> time;
            if (number < 10)
                talon = "T00" + to_string(number);
            else if (number > 9 || number < 100)
                talon = "T0" + to_string(number);
            else
                talon = "T" + to_string(number);
            cout << talon << "\n";
            allQueue.push_back({talon, time});
            number++;
        }
        else if (returnEnam(command) == Doing::DISTRIBUTE)
        {
            for (pair<string, int> item : allQueue)
            {
                vector<int> sums = {};

                allQueue.clear();

                for (vector<pair<string, int>> el : windows)
                {
                    sums.push_back(sum(el));
                }
                int minIndex = min(sums);
                windows[minIndex].push_back(item);
            }
            int window_number = 1;
            for (vector<pair<string, int>> item : windows)
            {
                cout << "Окно " << window_number << "(" << sum(item) << " минут) : ";
                window_number++;
                for (pair<string, int> el : item)
                {
                    cout << el.first << ", ";
                }
                cout << "\n";
            }
        }
        else
        {
            cout << "Такой команды не найдено \n";
        }
    }
}