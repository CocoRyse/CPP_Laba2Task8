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

void clear_input() {
    cin.clear();
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
    clear_input();

    if (input == '1') {
        a.add_data();
    }
    else if (input == '2')
    {
        cout << "Введите имя файла: ";
        cin >> file_name;
        file_name += ".txt";
        ifstream _file(file_name, std::ios_base::in);
        cout << endl;

        cout << "1. Загрузить одну запись" << endl;
        cout << "2. Загрузить все записи" << endl;
        cin >> input;
        clear_input();

        if (input == '1')
            a.read_from_file(_file);
        else if (input == '2')
            a.read_from_file_some_data(_file);
        else {
            cout << "Неопознанная команда!" << endl;
            return;
        }

        cout << "Данные успешно добавлены." << endl;
    } else {
        cout << "Неизвестная команда" << endl;
    }
}

void Save(DataList<CommunalPayment> data_list)
{
    CommunalPayment payment;
    char input;
    deque<CommunalPayment>::iterator iterator;
    string file_name;

    cout << "Введите имя файла: ";
    cin >> file_name;
    file_name += ".txt";
    ofstream _file(file_name, std::ios_base::app);
    cout << "1. Сохранить одну запись" << endl;
    cout << "2. Сохранить все записи" << endl;

    cin >> input;
    clear_input();
    cout << endl;
    if (input == '1')
    {
        cin >> payment;
        iterator = data_list.find_if([&payment](const CommunalPayment& p) { return payment == p; });
        data_list.print_data(iterator);
        cin >> input;
        data_list.write_to_file(_file, iterator);
    }
    if (input == '2')
    {
//        data_list.helper = data_list.deq; // кхе-кхе
        data_list.write_to_file_some_data(_file);
    }
}

void Change(DataList<CommunalPayment>& data_list)
{
    CommunalPayment payment;
    deque<CommunalPayment>::iterator iterator;

    cin >> payment;

    iterator = data_list.find_if([&payment](const CommunalPayment& p) { return payment == p; });

    cout << "Было..." << endl;
    data_list.print_data(iterator);

    cout << "Стало..." << endl;
    data_list.change_data(iterator);
}

void Delete(DataList<CommunalPayment>& data_list)
{
    CommunalPayment payment;
    deque<CommunalPayment>::iterator iterator;

    cin >> payment;

    iterator = data_list.find_if([&payment](const CommunalPayment& p) { return payment == p; });
    data_list.delete_data(iterator);
}

void Search(DataList<CommunalPayment> data_list)
{
    CommunalPayment payment;
    deque<CommunalPayment>::iterator iterator;
    char input;

    cin >> payment;
    cout << "1. Использовать линейный поиск" << endl;
    cout << "2. Использовать бинарный поиск" << endl;
    cin >> input;
    clear_input();

    if (input == '1') {
        iterator = data_list.find_if([&payment](const CommunalPayment &p) { return payment == p; });
    }
    else if (input == '2')
    {
        data_list.sort([](const CommunalPayment &p, const CommunalPayment &payment) {
            if (payment == p)
                return 0;
            else if (payment.penny > p.penny)
                return 1;
            else
                return -1;
        });
        iterator = data_list.lower_bound(payment);
        iterator = iterator - 1;
    } else {
        cout << "Неопознанная команда!" << endl;
    }

    data_list.print_data(iterator);

    cout << "1. Cохранить данные в файл" << endl;
    cout << "0. Не сохранять данные в файл" << endl;
    cin >> input;
    if (input == '1')
    {
        string file_name;
        cout << "Введите имя файла: ";
        cin >> file_name;
        file_name += ".txt";
        ofstream _file(file_name, std::ios_base::app);
        data_list.write_to_file(_file, iterator);
        cout << "Данные успешно добавлены в файл" << endl;
    } else if (input != '2')
        cout << "Неопознанная команда!" << endl;
}

void select_by_owner(DataList<CommunalPayment> data_list) {
    string surname;

    cout << "Фамилия владельца: ";
    cin >> surname;

    data_list.copy_if([&surname](const CommunalPayment &p) { return p.owner_surname == surname; });
    data_list.print_some_data();
}

void select_by_flat(DataList<CommunalPayment> data_list) {
    int flat;

    cout << "Номер квартиры: ";
    cin >> flat;
    cout << endl;

    data_list.copy_if([&flat](const CommunalPayment &p) { return p.address.flat == flat; });
    data_list.print_some_data();
}

void select_by_house(DataList<CommunalPayment> data_list) {
    int house;

    cout << "Номер дома: ";
    cin >> house;

    data_list.copy_if([&house](const CommunalPayment &p) { return p.address.house == house; });
    data_list.print_some_data();
}

void select_by_date(DataList<CommunalPayment> data_list) {
    Date date{};

    cout << "Дата платежа: ";
    cin >> date;

    data_list.copy_if([&date](const CommunalPayment &p) { return p.date == date; });
    data_list.print_some_data();
}

void select_by_debt_state(DataList<CommunalPayment> data_list) {
    bool is_owe;
    char input;

    cout << "1 — должен\n"
            "0 — не должен\n"
            "Состояние долга: ";
    cin >> input;

    is_owe = input != '0';
    data_list.copy_if([&is_owe](const CommunalPayment &p) {
        return p.penny > 0 || p.days_past_due > 0 == is_owe;
    });

    data_list.print_some_data();
}

void Selection(const DataList<CommunalPayment>& data_list)
{
    char tmp;
    bool control = true;
    while (control)
    {
        Sub_text_menu();
        cin >> tmp;
        clear_input();
        switch (tmp)
        {
            case '1': {
                select_by_owner(data_list);
                break;
            }
            case '2': {
                select_by_flat(data_list);
                break;
            }
            case '3': {
                select_by_house(data_list);
                break;
            }
            case '4': {
                select_by_date(data_list);
                break;
            }
            case '5': {
                select_by_debt_state(data_list);
                break;
            }
            case '0':
                control = false;
                break;
            default:
                cout << "Ошибка! Повторите ввод!" << endl;
                break;
        }
    }
}

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

int main()
{
    setlocale(LC_ALL, "Rus");
    bool control = true;
    DataList<CommunalPayment> data_list;
    char tmp;
    clear_input();
    while (control)
    {
        Text_menu();
        cin >> tmp;
        clear_input();
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
                data_list.clear();
                cout << "Очередь успешно очищена" << endl;
                break;
            case '8':
                data_list.print_data();
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