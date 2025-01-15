#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <iomanip>

using namespace std;

// ================= Батьківський клас "Автомобіль" =================
class Car {
protected:
    string brand;
    int year;
    double price;
    string configuration;
    string manufacturer;
    string saleDate;
    string buyerName;

public:
    Car(const string& brand, int year, double price, const string& configuration, const string& manufacturer, const string& saleDate, const string& buyerName)
        : brand(brand), year(year), price(price), configuration(configuration), manufacturer(manufacturer), saleDate(saleDate), buyerName(buyerName) {}

    virtual ~Car() {}

    virtual void display() const {
        cout << "Марка: " << brand << ", Рік: " << year << ", Ціна: " << price << " $, Комплектація: " << configuration
            << ", Виробник: " << manufacturer << ", Дата продажу: " << saleDate << ", Покупець: " << buyerName << endl;
    }

    virtual void saveToFile(ofstream& file) const {
        file << brand << "," << year << "," << price << "," << configuration << "," << manufacturer << "," << saleDate << "," << buyerName;
    }

    const string& getBrand() const { return brand; }
    int getYear() const { return year; }
    double getPrice() const { return price; }
    const string& getBuyerName() const { return buyerName; }
};

// ================= Дочірній клас "Уживаний автомобіль" =================
class UsedCar : public Car {
private:
    double mileage;
    double condition;

public:
    UsedCar(const string& brand, int year, double price, const string& configuration, const string& manufacturer, const string& saleDate, const string& buyerName, double mileage, double condition)
        : Car(brand, year, price, configuration, manufacturer, saleDate, buyerName), mileage(mileage), condition(condition) {}

    void display() const override {
        Car::display();
        cout << "Пробіг: " << mileage << " км, Стан: " << condition << "%" << endl;
    }

    void saveToFile(ofstream& file) const override {
        Car::saveToFile(file);
        file << "," << mileage << "," << condition << endl;
    }
};

// ================= Дочірній клас "Спортивний автомобіль" =================
class SportsCar : public Car {
private:
    double acceleration;
    double engineVolume;
    double horsepower;

public:
    SportsCar(const string& brand, int year, double price, const string& configuration, const string& manufacturer, const string& saleDate, const string& buyerName, double acceleration, double engineVolume, double horsepower)
        : Car(brand, year, price, configuration, manufacturer, saleDate, buyerName), acceleration(acceleration), engineVolume(engineVolume), horsepower(horsepower) {}

    void display() const override {
        Car::display();
        cout << "Розгін до 100 км/год: " << acceleration << " сек, Об'єм двигуна: " << engineVolume << " л, Потужність: " << horsepower << " к.с." << endl;
    }

    void saveToFile(ofstream& file) const override {
        Car::saveToFile(file);
        file << "," << acceleration << "," << engineVolume << "," << horsepower << endl;
    }
};

// ================= Дочірній клас "Спецтехніка" =================
class SpecialCar : public Car {
private:
    string type;
    double weight;
    string dimensions;

public:
    SpecialCar(const string& brand, int year, double price, const string& configuration, const string& manufacturer, const string& saleDate, const string& buyerName, const string& type, double weight, const string& dimensions)
        : Car(brand, year, price, configuration, manufacturer, saleDate, buyerName), type(type), weight(weight), dimensions(dimensions) {}

    void display() const override {
        Car::display();
        cout << "Тип: " << type << ", Вага: " << weight << " т, Габарити: " << dimensions << endl;
    }

    void saveToFile(ofstream& file) const override {
        Car::saveToFile(file);
        file << "," << type << "," << weight << "," << dimensions << endl;
    }
};

// ================= Функції для роботи з автомобілями =================
void addCar(vector<Car*>& cars) {
    int choice;
    cout << "Оберіть тип автомобіля для додавання:\n1. Уживаний автомобіль\n2. Спортивний автомобіль\n3. Спецтехніка\nВаш вибір: ";
    cin >> choice;

    string brand, configuration, manufacturer, saleDate, buyerName;
    int year;
    double price;

    cout << "Введіть марку: ";
    cin >> brand;
    cout << "Введіть рік випуску: ";
    cin >> year;
    cout << "Введіть ціну: ";
    cin >> price;
    cout << "Введіть комплектацію: ";
    cin >> configuration;
    cout << "Введіть виробника: ";
    cin >> manufacturer;
    cout << "Введіть дату продажу (YYYY-MM-DD): ";
    cin >> saleDate;
    cout << "Введіть ПІБ покупця: ";
    cin.ignore();
    getline(cin, buyerName);

    if (choice == 1) {
        double mileage, condition;
        cout << "Введіть пробіг (км): ";
        cin >> mileage;
        cout << "Введіть стан (%) : ";
        cin >> condition;
        cars.push_back(new UsedCar(brand, year, price, configuration, manufacturer, saleDate, buyerName, mileage, condition));
    }
    else if (choice == 2) {
        double acceleration, engineVolume, horsepower;
        cout << "Введіть час розгону до 100 км/год (сек): ";
        cin >> acceleration;
        cout << "Введіть об'єм двигуна (л): ";
        cin >> engineVolume;
        cout << "Введіть потужність (к.с.): ";
        cin >> horsepower;
        cars.push_back(new SportsCar(brand, year, price, configuration, manufacturer, saleDate, buyerName, acceleration, engineVolume, horsepower));
    }
    else if (choice == 3) {
        string type;
        double weight;
        string dimensions;
        cout << "Введіть тип: ";
        cin >> type;
        cout << "Введіть вагу (тонни): ";
        cin >> weight;
        cout << "Введіть габарити: ";
        cin >> dimensions;
        cars.push_back(new SpecialCar(brand, year, price, configuration, manufacturer, saleDate, buyerName, type, weight, dimensions));
    }
    else {
        cout << "Некоректний вибір!" << endl;
    }
}

void displayCars(const vector<Car*>& cars) {
    for (const auto& car : cars) {
        car->display();
        cout << "--------------------" << endl;
    }
}

void saveCarsToFile(const vector<Car*>& cars, const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "Помилка відкриття файлу!" << endl;
        return;
    }

    for (const auto& car : cars) {
        car->saveToFile(file);
        file << endl;
    }
    file.close();
    cout << "Дані успішно збережено у файл " << filename << endl;
}