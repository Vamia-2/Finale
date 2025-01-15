#include"Car.h"

int main() {
    vector<Car*> cars;
    int choice;

    do {
        cout << "Меню:\n1. Додати автомобіль\n2. Показати автомобілі\n3. Зберегти у файл\n4. Вийти\nВаш вибір: ";
        cin >> choice;

        switch (choice) {
        case 1:
            addCar(cars);
            break;
        case 2:
            displayCars(cars);
            break;
        case 3:
            saveCarsToFile(cars, "cars.txt");
            break;
        case 4:
            cout << "Завершення програми." << endl;
            break;
        default:
            cout << "Некоректний вибір!" << endl;
        }
    } while (choice != 4);

    for (auto& car : cars) {
        delete car;
    }
    return 0;
}
