#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <iomanip>

using namespace std;

// ================= ����������� ���� "���������" =================
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
        cout << "�����: " << brand << ", г�: " << year << ", ֳ��: " << price << " $, ������������: " << configuration
            << ", ��������: " << manufacturer << ", ���� �������: " << saleDate << ", ��������: " << buyerName << endl;
    }

    virtual void saveToFile(ofstream& file) const {
        file << brand << "," << year << "," << price << "," << configuration << "," << manufacturer << "," << saleDate << "," << buyerName;
    }

    const string& getBrand() const { return brand; }
    int getYear() const { return year; }
    double getPrice() const { return price; }
    const string& getBuyerName() const { return buyerName; }
};

// ================= ������� ���� "�������� ���������" =================
class UsedCar : public Car {
private:
    double mileage;
    double condition;

public:
    UsedCar(const string& brand, int year, double price, const string& configuration, const string& manufacturer, const string& saleDate, const string& buyerName, double mileage, double condition)
        : Car(brand, year, price, configuration, manufacturer, saleDate, buyerName), mileage(mileage), condition(condition) {}

    void display() const override {
        Car::display();
        cout << "�����: " << mileage << " ��, ����: " << condition << "%" << endl;
    }

    void saveToFile(ofstream& file) const override {
        Car::saveToFile(file);
        file << "," << mileage << "," << condition << endl;
    }
};

// ================= ������� ���� "���������� ���������" =================
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
        cout << "����� �� 100 ��/���: " << acceleration << " ���, ��'�� �������: " << engineVolume << " �, ���������: " << horsepower << " �.�." << endl;
    }

    void saveToFile(ofstream& file) const override {
        Car::saveToFile(file);
        file << "," << acceleration << "," << engineVolume << "," << horsepower << endl;
    }
};

// ================= ������� ���� "����������" =================
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
        cout << "���: " << type << ", ����: " << weight << " �, ��������: " << dimensions << endl;
    }

    void saveToFile(ofstream& file) const override {
        Car::saveToFile(file);
        file << "," << type << "," << weight << "," << dimensions << endl;
    }
};

// ================= ������� ��� ������ � ����������� =================
void addCar(vector<Car*>& cars) {
    int choice;
    cout << "������ ��� ��������� ��� ���������:\n1. �������� ���������\n2. ���������� ���������\n3. ����������\n��� ����: ";
    cin >> choice;

    string brand, configuration, manufacturer, saleDate, buyerName;
    int year;
    double price;

    cout << "������ �����: ";
    cin >> brand;
    cout << "������ �� �������: ";
    cin >> year;
    cout << "������ ����: ";
    cin >> price;
    cout << "������ ������������: ";
    cin >> configuration;
    cout << "������ ���������: ";
    cin >> manufacturer;
    cout << "������ ���� ������� (YYYY-MM-DD): ";
    cin >> saleDate;
    cout << "������ ϲ� �������: ";
    cin.ignore();
    getline(cin, buyerName);

    if (choice == 1) {
        double mileage, condition;
        cout << "������ ����� (��): ";
        cin >> mileage;
        cout << "������ ���� (%) : ";
        cin >> condition;
        cars.push_back(new UsedCar(brand, year, price, configuration, manufacturer, saleDate, buyerName, mileage, condition));
    }
    else if (choice == 2) {
        double acceleration, engineVolume, horsepower;
        cout << "������ ��� ������� �� 100 ��/��� (���): ";
        cin >> acceleration;
        cout << "������ ��'�� ������� (�): ";
        cin >> engineVolume;
        cout << "������ ��������� (�.�.): ";
        cin >> horsepower;
        cars.push_back(new SportsCar(brand, year, price, configuration, manufacturer, saleDate, buyerName, acceleration, engineVolume, horsepower));
    }
    else if (choice == 3) {
        string type;
        double weight;
        string dimensions;
        cout << "������ ���: ";
        cin >> type;
        cout << "������ ���� (�����): ";
        cin >> weight;
        cout << "������ ��������: ";
        cin >> dimensions;
        cars.push_back(new SpecialCar(brand, year, price, configuration, manufacturer, saleDate, buyerName, type, weight, dimensions));
    }
    else {
        cout << "����������� ����!" << endl;
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
        cout << "������� �������� �����!" << endl;
        return;
    }

    for (const auto& car : cars) {
        car->saveToFile(file);
        file << endl;
    }
    file.close();
    cout << "��� ������ ��������� � ���� " << filename << endl;
}