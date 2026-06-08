#include <iostream>
#include <map>
#include <utility>
#include <vector>
#include "zadanye1_1.h"

using namespace std;

// Константы для Варианта 6
const double TOTAL_CAPACITY = 23040.0; // Общая вместимость в единицах товара
const double ZONE_CAPACITY = 7680.0;   // Вместимость одной зоны (768 ячеек * 10)

void AddFunction(map<string, pair<string, int>> &storage)
{
    string item, when;
    int count;
    cin >> item >> count >> when;
    if (storage.count(when) == 0)
    {
        if (count <= 10)
        {
            storage[when] = {item, count};
            cout << "Добавлено " << count << " " << item << " в " << when << endl;
        }
        else
            cout << "Ошибка: Превышена вместимость ячейки (максимум 10)" << endl;
    }
    else
    {
        if (storage[when].first != item)
        {
            cout << "Ошибка: Ячейка " << when << " занята товаром " << storage[when].first << endl;
        }
        else
        {
            if (storage[when].second + count <= 10)
            {
                storage[when].second += count;
                cout << "Добавлено " << count << " " << item << " в " << when << endl;
            }
            else
            {
                cout << "Ошибка: Превышена вместимость ячейки (максимум 10)" << endl;
            }
        }
    }
    return;
}

void RemoveFunction(map<string, pair<string, int>> &storage)
{
    string item, when;
    int count;
    cin >> item >> count >> when;
    if (storage.count(when) != 0)
    {
        if (storage[when].first == item)
        {
            if (count < storage[when].second)
            {
                storage[when].second -= count;
                cout << "Удалено " << count << " " << item << " (остаток: " << storage[when].second << ")" << endl;
            }
            else if (count == storage[when].second)
            {
                storage.erase(when); // Полностью освобождаем ячейку, если товар закончился
                cout << "Удалено всего количества товара из ячейки, она считается свободной" << endl;
            }
            else
            {
                cout << "Ошибка: Недостаточно товара для списания" << endl;
            }
        }
        else
        {
            cout << "Ошибка: Товар " << item << " не найден в ячейке " << when << endl;
        }
    }
    else
    {
        cout << "Ошибка: Товар " << item << " не найден в ячейке " << when << endl;
    }
}

void InfoFunction(const map<string, pair<string, int>> &storage)
{
    int totalItems = 0;
    int countA = 0, countB = 0, countC = 0;

    // Считаем сумму штук товаров по зонам
    for (pair<string, pair<string, int>> item : storage)
    {
        int qty = item.second.second;
        totalItems += qty;
        if (item.first[0] == 'A')
            countA += qty;
        if (item.first[0] == 'B')
            countB += qty;
        if (item.first[0] == 'C')
            countC += qty;
    }

    // Вывод процентов загрузки (магический трюк для округления до 2 знаков без iomanip)
    cout << "Загруженность склада: " << (int)(totalItems / TOTAL_CAPACITY * 10000 + 0.5) / 100.0 << " %\n";
    cout << "Загруженность зоны A: " << (int)(countA / ZONE_CAPACITY * 10000 + 0.5) / 100.0 << " %\n";
    cout << "Загруженность зоны B: " << (int)(countB / ZONE_CAPACITY * 10000 + 0.5) / 100.0 << " %\n";
    cout << "Загруженность зоны C: " << (int)(countC / ZONE_CAPACITY * 10000 + 0.5) / 100.0 << " %\n";

    cout << "Заполненные ячейки: " << endl;
    for (pair<string, pair<string, int>> item : storage)
    {
        cout << item.first << ": " << item.second.first << " (" << item.second.second << ")\n";
    }

    cout << "Пустые ячейки:\n";
    bool first = true;
    for (string item : {"A", "B", "C"})
    {
        for (int i = 1; i <= 16; ++i) // Вариант 6: 16 стеллажей
        {
            for (int j = 1; j <= 8; ++j) // Вариант 6: 8 вертикальных секций
            {
                for (int k = 1; k <= 6; ++k) // Вариант 6: 6 полок
                {
                    string address = item + to_string(i) + to_string(j) + to_string(k);
                    if (storage.count(address) == 0)
                    {
                        if (!first)
                            cout << ", ";
                        cout << address;
                        first = false;
                    }
                }
            }
        }
    }
    cout << "\n";
}

Doing returnEnam(string a)
{
    if (a == "ADD")
        return Doing::ADD;
    if (a == "REMOVE")
        return Doing::REMOVE;
    if (a == "INFO")
        return Doing::INFO;
    return Doing::EMPTY;
}

int main()
{
    map<string, pair<string, int>> storage;
    string d;
    while (cin >> d)
    {
        switch (returnEnam(d))
        {
        case Doing::ADD:
            AddFunction(storage);
            break;
        case Doing::REMOVE:
            RemoveFunction(storage);
            break;
        case Doing::INFO:
            InfoFunction(storage);
            break;
        default:
            cout << "Ошибка: Неизвестная команда. Введите ADD, REMOVE или INFO\n";
            break;
        }
    }
    return 0;
}