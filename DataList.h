//
// Created by Виктор Решетов on 17.05.2020.
//

#include "string"
#include "CommunalPayment.h"
#include <deque>
#include <algorithm>
#include <fstream>

using std::deque;
using std::istream_iterator;
using std::ostream_iterator;
using std::istream;
using std::ostream;
using std::ifstream;
using std::ofstream;

template<typename T>
class DataList {
public:
    deque<T> deq;
    deque<T> helper;

    DataList() : deq(), helper() { }

    void add_data()
    {
        istream_iterator<T> is;
        bool Control = true;
        while (Control)
        {
            char input;
            cout << "1. Добавить данные" << endl;
            cout << "0. Отмена" << endl;
            cin >> input;
            cout << endl;
            cin.get();
            if (input == '0')
            {
                Control = false;
            }
            else
            {
                is = cin;
                deq.push_back(*is);
                cout << "Данные успешно добавлены." << endl;
            }
        }
    }

    void print_data(typename deque<T>::iterator x)
    {
        cout << *x << endl;
    }

    void print_some_data()
    {
        copy(helper.begin(), helper.end(), ostream_iterator<T>(cout, "\n"));
    }

    void delete_data(typename deque<T>::iterator x)
    {
        deq.erase(x);
        cout << "Данные успешно удалены." << endl;
    }

    void change_data(typename deque<T>::iterator x)
    {
        istream_iterator<T> is(cin);
        *x = *is;
        cout << "Данные успешно изменены." << endl;
    }

    void load_to_file(ofstream& _file, typename deque<T>::iterator x)
    {
        ostream_iterator<T> is(_file, "\n");
        *is = *x;
        cout << "Данные успешно добавлены в файл" << endl;
    }

    void load_to_file_some_data(ofstream& _file)
    {
        copy(deq.begin(), deq.end(), ostream_iterator<T>(_file, "\n"));
        cout << "Данные успешно добавлены в файл" << endl;
    }

    void load_from_file(ifstream& _file)
    {
        istream_iterator<T> is(_file);
        deq.push_back(*is);
        cout << "Данные успешно загружены из файла" << endl;
    }

    void load_from_file_some_data(ifstream& _file)
    {
        while (_file.peek() != EOF)
        {
            deq.push_back(*istream_iterator<T>(_file));
            _file.get();
            _file.get();

        }
        cout << "Данные успешно загружены из файла" << endl;
    }
};
