#include <iostream>
#include <vector>
#include "zadanye4_1.h"
#include <map>

using namespace std;

Doing returnEnam(string a)
{
    if (a == "CLASS")
        return Doing::CLASS;
    if (a == "NEXT")
        return Doing::NEXT;
    if (a == "VIEW")
        return Doing::VIEW;
    return Doing::EMPTY;
};

bool identity(vector<string> array, string findWord)
{
    for (string item : array)
    {
        if (item == findWord)
        {
            return true;
        }
    }
    return false;
}

void printVector(vector<string> array)
{
    for (auto item : array)
    {
        cout << item << " ";
    }
}

int main()
{
    int n, i, numberMonth = 0;
    vector<int> monthDays = {30, 28, 31, 30, 31, 30, 31, 30, 31, 30, 31, 30};
    map<int, vector<string>> leson; //  мэп<день месяца, Вектор пар>
    string command, s;
    cout << "Введите количество запросов (N): \n";
    cin >> n;
    for (int j = 0; j < n; ++j)
    {
        cin >> command;
        if (returnEnam(command) == Doing::CLASS)
        {
            cin >> i >> s;
            if (identity(leson[i], s))
            {
                cout << "Урок уже добавлен в день " << i << '\n';
            }
            else if (!identity(leson[i], s))
            {
                vector<string> temp = leson[i];
                temp.push_back(s);
                leson[i] = temp;
                cout << "Добавлен урок " << s << " в день " << i << '\n';
            }
            else if (leson[i].size() == 0)
            {
                leson[i] = {s};
                cout << "Добавлен урок " << s << " в день" << i << '\n';
            }
        }
        else if (returnEnam(command) == Doing::NEXT)
        {
            numberMonth++;
            if (numberMonth == 12)
                numberMonth = 0;
            cout << "Переход на следующий месяц \n";
        }
        else if (returnEnam(command) == Doing::EMPTY)
        {
            cin >> i;
            if (i > monthDays[numberMonth])
            {
                cout << "Ошибка: В этом месяце всего " << monthDays[numberMonth] << " дней \n";
            }
            // Для февраля
            else if (i == 28 && numberMonth == 1)
            {
                cout << "В день " << i << " занятия в университете: ";
                for (int k = 28; k < 32; ++k)
                {
                    printVector(leson[k]);
                }
                cout << '\n';
            }
            // Для месяцев по 30 дней

            else if (i == 30 && numberMonth % 2 == 0)
            {

                if (monthDays[numberMonth] == i)
                {
                    cout << "В день " << i << " занятия в университете: ";
                    for (int k = 30; k < 32; ++k)
                    {
                        printVector(leson[k]);
                    }
                    cout << '\n';
                }
            }
            // Вывод точной даты
            else if (leson[i].size() != 0)
            {
                cout << "В день " << i << " занятия в университете: ";
                printVector(leson[i]);
                cout << '\n';
            }

            else if (leson[i].size() == 0)
            {
                cout << "В день " << i << " мы свободны! \n";
            }
        }
    }
}