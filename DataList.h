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
    deque<T> deq;
    deque<T> helper;

public:
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
            cin.clear();
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

    void fwrite_part(ofstream& _file, typename deque<T>::iterator x)
    {
        ostream_iterator<T> is(_file, "\n");
        *is = *x;
        cout << "Данные успешно добавлены в файл" << endl;
    }

    void fwrite_full(ofstream& _file)
    {
        _file.clear();
        copy(deq.begin(), deq.end(), ostream_iterator<T>(_file, "\n"));
        cout << "Данные успешно добавлены в файл" << endl;
    }

    void fread_part(ifstream& _file)
    {
        istream_iterator<T> is(_file);
        deq.push_back(*is);
        cout << "Данные успешно загружены из файла" << endl;
    }

    void fread_full(ifstream& _file)
    {
        while (_file.peek() != EOF)
        {
            deq.push_back(*istream_iterator<T>(_file));
            _file.get();
            _file.get();

        }
        cout << "Данные успешно загружены из файла" << endl;
    }

    deque<CommunalPayment>::iterator find_if(const std::function<bool(CommunalPayment)> predicate) {
        return std::find_if(deq.begin(), deq.end(), predicate);
    }

    deque<CommunalPayment>::iterator lower_bound(CommunalPayment payment) {
        return std::lower_bound(deq.begin(), deq.end(), payment);
    }

    deque<CommunalPayment>::iterator upper_bound(CommunalPayment payment) {
        return std::upper_bound(deq.begin(), deq.end(), payment);
    }

    void sort(const std::function<bool(CommunalPayment, CommunalPayment)> comparator) {
        std::sort(deq.begin(), deq.end());
    }

    void copy_if(const std::function<bool(CommunalPayment)> predicate) {
        helper.clear();
        std::copy_if(deq.begin(), deq.end(), back_inserter(helper), predicate);
    }

    void clear() {
        helper.clear();
        deq.clear();
    }

    void print_data() {
        for (auto i = deq.begin(); i < deq.end(); i++)
            print_data(i);
    }

    deque<CommunalPayment>::iterator end() {
        return deq.end();
    }
};
