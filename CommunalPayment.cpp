//
// Created by Виктор Решетов on 15.05.2020.
//

#include "CommunalPayment.h"
#include <utility>
#include <set>
#include <fstream>

CommunalPayment::CommunalPayment(
        Address new_address,
        string new_owner_surname,
        PaymentType new_type,
        Date new_Date, int new_sum, int new_penny,
        int new_days_past_due)
        :
        address(new_address),
        owner_surname(std::move(new_owner_surname)),
        type(new_type), date(new_Date), sum(new_sum),
        penny(new_penny), days_past_due(new_days_past_due)
{ }

CommunalPayment::CommunalPayment() : address(),
                                     owner_surname(""),
                                     type(PaymentType::GasSupply),
                                     date({}),
                                     sum(0),
                                     penny(0),
                                     days_past_due(0)
{ }

std::istream &operator>>(std::istream &in, CommunalPayment &payment) {
    if (typeid(in) == typeid(std::ifstream)) {
        in >> payment.owner_surname;
        in >> payment.address;
        int code;
        in >> code;
        payment.type = PaymentType(code - 1);
        in >> payment.date;
        in >> payment.sum;
        in >> payment.penny;
        in >> payment.days_past_due;

    } else {
        cout << "Фамилия владельца: ";
        in >> payment.owner_surname;
        cout << payment.owner_surname << endl;

        in >> payment.address;
        int code = -1;
        while (code < 1 || code > 5) {
            cout << "1 — Водоснабжение\n"
                    "2 — Водоотведение\n"
                    "3 — Отопление\n"
                    "4 — Газоснабжение\n"
                    "5 — Электроснабжение\n"
                    "Тип платежа: ";
            in >> code;
            cout << code << endl;
            in.get();
            if (code < 1 || code > 5)
                cout << "Ошибка! Повторите ввод!" << endl;
        }
        payment.type = PaymentType(code - 1);

        cout << "Введите дату платежа" << endl;
        in >> payment.date;

        cout << "Сумма платежа: ";
        in >> payment.sum;
        cout << payment.sum << endl;

        cout << "Пенни: ";
        in >> payment.penny;
        cout << payment.penny << endl;

        cout << "Количество дней просрочки платежа: ";
        in >> payment.days_past_due;
        cout << payment.days_past_due << endl << endl;
    }
    return in;
}

std::ostream &operator<<(std::ostream &out, const CommunalPayment &payment) {
    if (typeid(out) == typeid(ofstream)) {
        out << payment.owner_surname << endl;
        out << payment.address << endl;
        out << (int)payment.type << endl;
        out << payment.date << endl;
        out << payment.sum << endl;
        out << payment.penny << endl;
        out << payment.days_past_due << endl;
    } else {
        out << "Фамилия владельца: " << payment.owner_surname << endl;
        out << "Адрес: " << endl << payment.address << endl;

        out << "Тип платежа: ";
        switch (payment.type) {
            case PaymentType::WaterSupply:
                out << "Водоснабжение";
                break;
            case PaymentType::WaterDisposal:
                out << "Водоотведение";
                break;
            case PaymentType::HeatSupply:
                out << "Отопление";
                break;
            case PaymentType::GasSupply:
                out << "Газоснабжение";
                break;
            case PaymentType::PowerSupply:
                out << "Электроснабжение";
                break;
        }
        out << endl;

        out << "Дата: " << endl << payment.date << endl;
        out << "Сумма: " << payment.sum << endl;
        out << "Пенни: " << payment.penny << endl;
        out << "Количество дней просрочки платежа: " << payment.days_past_due << endl;
    }
    return out;
}

bool CommunalPayment::operator==(const CommunalPayment& payment) const {
    return payment.owner_surname == owner_surname &&
           payment.address == address && payment.date == date &&
           (payment.penny > 0 || payment.days_past_due > 0 == penny > 0 || days_past_due > 0);
}

bool CommunalPayment::operator<(const CommunalPayment &payment) const {
    return (penny < payment.penny || days_past_due < payment.days_past_due);
}

bool Date::operator==(Date another) const {
    return year  == another.year  &&
           month == another.month &&
           day   == another.day;
}

std::istream & operator>>(std::istream &in, Date &date) {
    if (typeid(in) == typeid(std::ifstream)) {
        in >> date.year;
        in >> date.month;
        in >> date.day;
    } else {
        bool error = true;
        while (error) {
            cout << "Введите год: ";
            in >> date.year;
            cout << date.year << endl;
            error = date.year < 1970 || date.year > 2020;
            if (error)
                cout << "Ошибка! Повторите ввод!" << endl;
        }
        error = true;
        while (error) {
            cout << "Введите номер месяца: ";
            in >> date.month;
            cout << date.month << endl;
            error = date.month < 1 || date.month > 12;
            if (error)
                cout << "Ошибка! Повторите ввод!" << endl;
        }
        error = true;
        while (error) {
            cout << "Введите номер дня: ";
            in >> date.day;
            cout << date.day << endl;
            switch (date.month) {
                case 1: case 3: case 5:
                case 7: case 8: case 10:
                case 12:
                    error = date.day > 31;
                    break;
                case 4: case 6: case 9:
                case 11:
                    error = date.day > 30;
                    break;
                case 2:
                    error = date.day > (date.year % 4 != 0 ||
                            (date.year % 100 == 0 && date.year % 400 != 0) ? 28 : 29);
                    break;
            }
            error = error || date.day < 1;
            if (error)
                cout << "Ошибка! Повторите ввод!" << endl;
        }
    }
    return in;
}

std::ostream &operator<<(std::ostream &out, const Date &date) {
    if (typeid(out) == typeid(ofstream)) {
        out << date.year << endl;
        out << date.month << endl;
        out << date.day;
    } else {
        out << "Год: " << date.year << endl;
        out << "Месяц: " << date.month << endl;
        out << "День: " << date.day;
    }
    return out;
}

std::istream &operator>>(std::istream &in, Address &address) {
    if (typeid(in) == typeid(std::ifstream)) {
        in >> address.house;
        in >> address.flat;
    } else {
        cout << "Номер дома: ";
        in >> address.house;
        cout << address.house << endl;
        cout << "Номер квартиры: ";
        in >> address.flat;
        cout << address.flat << endl;
    }
    return in;
}

std::ostream &operator<<(std::ostream &out, const Address &address) {
    if (typeid(out) == typeid(ofstream)) {
        out << address.house << endl;
        out << address.flat;
    } else {
        out << "Номер дома: " << address.house << endl;
        out << "Номер квартиры: " << address.flat;
    }
    return out;
}

bool Address::operator==(Address t1) const {
    return house == t1.house && flat == t1.flat;
}