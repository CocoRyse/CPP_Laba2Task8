/*Результатом должна быть консольная программа с текстовым меню. Программа
должна содержать шаблонный класс для управления данными согласно заданию.
Для хранения данных необходимо выбрать оптимальный с точки зрения задания
контейнер.*/

/*
1. Предусмотреть операции добавления, изменения и удаления элемента
контейнера.
2. Реализовать ввод и вывод элементов контейнера с использованием потоковых
итераторов на экран и в файл.
3. Реализовать операции поиска по заданным критериям и выборки подмножества
элементов по заданным критериям. Реализовать поиск в двух вариантах: линейный
поиск и двоичный поиск на отсортированном контейнере.
4. Предусмотреть вывод подмножества выборки на экран и в файл.
*/

/*Структура записи о коммунальном платеже содержит поля: адрес квартиры,
фамилия владельца, вид платежа, дата платежа, сумма платежа, процент пени,
количество дней просрочки платежа. Поиск по номеру дома, квартиры, владельцу,
дате, наличии долга. Вывод суммы долга в результатах поиска.*/


#include <iostream>
#include "DataList.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::ofstream;

void Text_menu()
{
    cout << "Выберите действие: " << endl;
    cout << "1. Добавить данные" << endl;
    cout << "2. Сохранить данные" << endl;
    cout << "3. Изменить данные" << endl;
    cout << "4. Удалить данные" << endl;
    cout << "5. Найти данные" << endl;
    cout << "6. Составить выборки" << endl;
    cout << "7. Очисить очередь" << endl;
    cout << "8. Вывести данные на экран" << endl;
    cout << "0. Выход" << endl;
}

void Sub_text_menu()
{
    cout << "Выберите действие: " << endl;
    cout << "1. Выборка с одинаковой фамилией владельца" << endl;
    cout << "2. Выборка с одинаковым номером дома" << endl;
    cout << "3. Выборка с одинаковым номеров квартиры" << endl;
    cout << "4. Выборка с одинаковой датой" << endl;
    cout << "5. Выборка с одинаковым статусом долга" << endl;
    cout << "0. Отмена" << endl;
}

void Add(DataList<CommunalPayment>& a)
{
    char input;
    string file_name;
    cout << endl;
    cout << "1. Ввод данных с клавиатуры" << endl;
    cout << "2. Загрузить данные из файла" << endl;
    cin >> input;
    cin.get();
    if (input == '1')
    {
        a.add_data();
    }
    if (input == '2')
    {
        cout << "Введите имя файла: ";
        cin >> file_name;
        file_name += ".txt";
        ifstream _file(file_name, std::ios_base::in);
        cout << endl;
        cout << "1. Загрузить одну запись" << endl;
        cout << "2. Загрузить все записи" << endl;
        cin >> input;
        cin.get();
        if (input == '1')
            a.load_from_file(_file);
        if (input == '2')
            a.load_from_file_some_data(_file);
        cout << "Данные успешно добавлены." << endl;
    }
}

void Save(DataList<CommunalPayment> a)
{
    CommunalPayment payment;
    char input;
    deque<CommunalPayment>::iterator x;
    string file_name;
    cout << "Введите имя файла: ";
    cin >> file_name;
    file_name += ".txt";
    ofstream _file(file_name, std::ios_base::app);
    cout << "1. Сохранить одну запись" << endl;
    cout << "2. Сохранить все записи" << endl;
    cin >> input;
    cin.get();
    cout << endl;
    if (input == '1')
    {
        cin >> payment;
        x = find_if(a.deq.begin(), a.deq.end(),[&payment](const CommunalPayment& p)
        {
            return payment == p;
        });
        a.print_data(x);
        cin >> input;
        a.load_to_file(_file, x);
    }
    if (input == '2')
    {
        a.helper = a.deq;
        a.load_to_file_some_data(_file);
    }
}

void Change(DataList<CommunalPayment>& a)
{
    CommunalPayment payment;
    deque<CommunalPayment>::iterator x;
    cin >> payment;
    x = find_if(a.deq.begin(), a.deq.end(), [&payment](const CommunalPayment& p)
    {
        return payment == p;
    });
    cout << "Было..." << endl;
    a.print_data(x);
    cout << "Стало..." << endl;
    a.change_data(x);
}

void Delete(DataList<CommunalPayment>& a)
{
    CommunalPayment payment;
    deque<CommunalPayment>::iterator x;
    cin >> payment;
    x = find_if(a.deq.begin(), a.deq.end(), [&payment](const CommunalPayment& p)
    {
        return payment == p;
    });
    a.delete_data(x);
}

void Search(DataList<CommunalPayment> a)
{
    CommunalPayment payment;
    deque<CommunalPayment>::iterator x;
    char tmp;
    cin >> payment;
    cout << "1. Использовать линейный поиск" << endl;
    cout << "2. Использовать бинарный поиск" << endl;
    cin >> tmp;
    cin.get();
    if (tmp == '1')
    {
        x = find_if(a.deq.begin(), a.deq.end(), [&payment](const CommunalPayment& p)
        {
            return payment == p;
        });
    }
    if (tmp == '2')
    {
        sort(a.deq.begin(), a.deq.end(), [](const CommunalPayment &p, const CommunalPayment &payment)
        {
            if (payment == p)
                return 0;
            else if (payment.penny > p.penny)
                return 1;
            else
                return -1;
        });
        x = lower_bound(a.deq.begin(), a.deq.end(), payment);
        x = x - 1;
    }
    a.print_data(x);
    cout << "1. Cохранить данные в файл" << endl;
    cout << "0. Не сохранять данные в файл" << endl;
    cin >> tmp;
    if (tmp == '1')
    {
        string temp2;
        cout << "Введите имя файла: ";
        cin >> temp2;
        temp2 += ".txt";
        ofstream _file(temp2, std::ios_base::app);
        a.load_to_file(_file, x);
        cout << "Данные успешно добавлены в файл" << endl;
    }
}

void Selection(DataList<CommunalPayment> a)
{
    char tmp;
    string surname;
    int flat;
    int house;
    Date date{};
    bool is_owe;
    bool control = true;
    while (control)
    {
        a.helper.clear();
        Sub_text_menu();
        cin >> tmp;
        cin.get();
        switch (tmp)
        {
//            cout << "1. Выборка с одинаковой фамилией владельца" << endl;
//            cout << "2. Выборка с одинаковым номером дома" << endl;
//            cout << "3. Выборка с одинаковым номеров квартиры" << endl;
//            cout << "4. Выборка с одинаковой датой" << endl;
//            cout << "4. Выборка с одинаковым статусом долга" << endl;
            case '1':
                cout << "Фамилия владельца: "; cin >> surname;
                copy_if(a.deq.begin(), a.deq.end(), back_inserter(a.helper), [&surname](const CommunalPayment& p){
                    return p.owner_surname == surname;
                });
                a.print_some_data();
                break;

            case '2':
                cout << "Номер квартиры: "; cin >> flat; cout << endl;
                copy_if(a.deq.begin(), a.deq.end(), back_inserter(a.helper), [&flat](const CommunalPayment& p){
                    return p.address.flat == flat;
                });
                a.print_some_data();
                break;
            case '3':
                cout << "Номер дома: "; cin >> house;
                copy_if(a.deq.begin(), a.deq.end(), back_inserter(a.helper), [&house](const CommunalPayment& p){
                    return p.address.house == house;
                });
                a.print_some_data();
                break;
            case '4':
                cout << "Дата платежа: "; cin >> date;
                copy_if(a.deq.begin(), a.deq.end(), back_inserter(a.helper), [&date](const CommunalPayment& p){
                    return p.date == date;
                });
                a.print_some_data();
                break;
            case '5':
                char input;
                cout << "1 — должен\n"
                        "0 — не должен\n"
                        "Состояние долга: "; cin >> input;
                is_owe = input != '0';
                copy_if(a.deq.begin(), a.deq.end(), back_inserter(a.helper), [&is_owe](const CommunalPayment& p){
                    return p.penny > 0 || p.days_past_due > 0 == is_owe;
                });
                a.print_some_data();
                break;
            case '0':
                control = false;
                break;
            default:
                cout << "Ошибка! Повторите ввод!" << endl;
                break;
        }
    }
}

int main()
{
    setlocale(LC_ALL, "Rus");
    bool control = true;
    DataList<CommunalPayment> data_list;
    char tmp;

    while (control)
    {
        Text_menu();
        cin >> tmp;
        cin.get();
        switch (tmp)
        {
            case '1':
                Add(data_list);
                break;
            case '2':
                Save(data_list);
                break;
            case '3':
                Change(data_list);
                break;
            case '4':
                Delete(data_list);
                break;
            case '5':
                Search(data_list);
                break;
            case '6':
                Selection(data_list);
                break;
            case '7':
                data_list.deq.clear();
                cout << "Очередь успешно очищена" << endl;
                break;
            case '8':
                for (auto i = data_list.deq.begin(); i < data_list.deq.end(); i++)
                    data_list.print_data(i);
                break;
            case '0':
                control = false;
                break;
            default:
                cout << "Ошибка! Повторите ввод!" << endl;
                break;
        }
    }
    return 0;
}