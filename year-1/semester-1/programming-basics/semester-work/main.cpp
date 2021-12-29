#include <iostream>
#include <windows.h>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;


/////////// Structures ///////////
struct Date {
    int day, month, year;
};

struct Class {
    float price;
    int passengers;
};

struct Ship {
    string name;
    string captainName;
    Class firstClass{};
    Class secondClass{};
};

struct Cruise {
    vector<string> route;
    Ship ship;
    Date startDate{};
    Date endDate{};
};

/////////// Constants ///////////
const int MAX_CRUISES = 100;


/////////// Prototypes ///////////
int addCruise(Cruise cruises[], int &currentCruisesCount);

void addCruises(Cruise cruises[], int &currentCruisesCount);

void editCruise(Cruise cruises[], int &currentCruisesCount, Date current);

bool compareDates(const Date &date1, const Date &date2);

void printFoundCruise(Cruise cruises[], int &currentCruisesCount);

void filterCruises(Cruise cruises[], int &currentCruisesCount, const string &criteria);

void printCruise(Cruise cruises[], int &currentCruisesCount, int cruise);

void fillTestData(Cruise cruises[], int &currentCruisesCount);

bool cruisesExist(int &currentCruisesCount);

bool cruiseExists(int &currentCruisesCount, int &cruise);

void getCurrentDate(int &day, int &month, int &year);

int main() {
    setlocale(LC_ALL, "BG");
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    // Get current time
    Date currentDate{};
    getCurrentDate(currentDate.day, currentDate.month, currentDate.year);

    int currentCruisesCount = 0;
    Cruise cruises[MAX_CRUISES];

    int selected;
    do {
        printf("==============================================\n");
        printf("Избери една от следните опции: \n");
        printf("0. Излез от менюто\n");
        printf("1. Въвеждане на тестови круизи\n");
        printf("2. Добавяне на едно ново морско пътуване\n");
        printf("3. Добавяне на списък от пътувания\n");
        printf("4. Показване на информация за кораб\n");
        printf("5. Извеждане на пътуванията с най-ранна дата на тръгване\n");
        printf("6. Извеждане на пътуванията към определена дестинация\n");
        printf("7. Корекция на данни за пътуване\n");
        printf("Избрана опция: ");

        cin >> selected;
        switch (selected) {
            case 0:
                break;
            case 1:
                fillTestData(cruises, currentCruisesCount);
                break;
            case 2:
                addCruise(cruises, currentCruisesCount);
                break;
            case 3:
                addCruises(cruises, currentCruisesCount);
                break;
            case 4:
                printFoundCruise(cruises, currentCruisesCount);
                break;
            case 5:
                filterCruises(cruises, currentCruisesCount, "startDate");
                break;
            case 6:
                filterCruises(cruises, currentCruisesCount, "destination");
                break;
            case 7:
                editCruise(cruises, currentCruisesCount, currentDate);
                break;
            default:
                printf("Невалидна опция!\n");
        }
    } while (selected != 0);
}

int addCruise(Cruise cruises[], int &currentCruisesCount) {
    if (currentCruisesCount >= MAX_CRUISES) {
        printf("==============================================\n");
        printf("Достигнат е максималният брой от круизи!\n");
        return 1;
    }


    printf("============{ ДОБАВЯНЕ НА КРУИЗ %d }============\n", currentCruisesCount + 1);

    // Въвеждане на дестинации
    printf("==={ ВЪВЕЖДАНЕ НА ДЕСТИНАЦИИ }===\n");
    string destination;
    for (int i = 0;; i++) {
        if (i == 0) {
            printf("Въведи начална дестинация: ");
        } else {
            printf("Въведи дестинация %d: ", i + 1);
        }
        cin.ignore();
        getline(cin, destination);
        cruises[currentCruisesCount].route.push_back(destination);

        char final = 0;
        while (final != 'y' && final != 'n') {
            printf("Това крайна дестинация ли е? [y/n]: ");
            cin >> final;
        }
        if (final == 'y') {
            break;
        }
    }

    //TODO Валидации на датите
    // method validateDate
    // ДНИ 0 / 31
    // МЕСЕЦИ  > 0 && < 13
    // ГОДИНА В БЪДЕЩЕТО
    printf("==={ ВЪВЕЖДАНЕ НА ПЕРИОД ПЪТУВАНЕ }===\n");

    // Въвеждане на дата потегляне
    printf("Въведи дата потегляне [формат: 01.01.2022]: ");
    string startDate;
    cin >> startDate;
    cruises[currentCruisesCount].startDate.day = stoi(startDate.substr(0, 2));
    cruises[currentCruisesCount].startDate.month = stoi(startDate.substr(3, 2));
    cruises[currentCruisesCount].startDate.year = stoi(startDate.substr(6, 4));

    // Въвеждане на дата връщане
    printf("Въведи дата връщане   [формат: 01.01.2022]: ");
    string endDate;
    cin >> endDate;
    cruises[currentCruisesCount].endDate.day = stoi(endDate.substr(0, 2));
    cruises[currentCruisesCount].endDate.month = stoi(endDate.substr(3, 2));
    cruises[currentCruisesCount].endDate.year = stoi(endDate.substr(6, 4));

    printf("==={ ВЪВЕЖДАНЕ НА ИНФОРМАЦИЯ ЗА КОРАБА }===\n");

    // Въвеждане на име на кораб
    printf("Въведи име на кораб: ");
    cin.ignore();
    getline(cin, cruises[currentCruisesCount].ship.name);

    // Въвеждане на име на кипитан на кораб
    printf("Въведи име на капитан на кораб: ");
    getline(cin, cruises[currentCruisesCount].ship.captainName);

    printf("==={ ВЪВЕЖДАНЕ НА ИНФОРМАЦИЯ ЗА КЛАСИТЕ ПЪТНИЦИ }===\n");

    printf("==={ 1-ВА КЛАСА }===\n");
    printf("Въведи цена: ");
    cin >> cruises[currentCruisesCount].ship.firstClass.price;

    printf("Въведи брой пътници: ");
    cin >> cruises[currentCruisesCount].ship.firstClass.passengers;

    printf("==={ 2-РА КЛАСА }===\n");
    printf("Въведи цена: ");
    cin >> cruises[currentCruisesCount].ship.secondClass.price;

    printf("Въведи брой пътници: ");
    cin >> cruises[currentCruisesCount].ship.secondClass.passengers;

    // Завършване на добавянето
    printf("============{ УСПЕШНО ДОБАВЯНЕ НА КРУИЗ %d }============\n", currentCruisesCount + 1);
    currentCruisesCount++;

    return 0;
}

void addCruises(Cruise cruises[], int &currentCruisesCount) {
    printf("============{ ДОБАВЯНЕ НА КРУИЗИ }============\n");
    int count;
    printf("Въведи колко круизи да бъдат добавени: ");
    cin >> count;

    for (int i = 0; i < count; i++) {
        if (addCruise(cruises, currentCruisesCount) == 1) break;
    }
}

void editCruise(Cruise cruises[], int &currentCruisesCount, Date current) {
    if (!cruisesExist(currentCruisesCount)) return;

    int cruise;
    printf("Въведи номер на круиз: ");
    cin >> cruise;

    if (!cruiseExists(currentCruisesCount, cruise)) return;

    if (compareDates(cruises[cruise].startDate, current)) {
        printf("==============================================\n");
        printf("Не можете да редактирате минал круиз!\n");
        return;
    }

    printf("============{ РЕДАКЦИЯ НА КРУИЗ %d }============\n", cruise);
    char answer;

    printf("Искате ли да редактирате датата на потегляне? [y/n] ");
    cin >> answer;
    if (answer == 'y') {
        printf("Въведи дата потегляне [формат: 01.01.2022]: ");
        string startDate;
        cin >> startDate;
        cruises[cruise].startDate.day = stoi(startDate.substr(0, 2));
        cruises[cruise].startDate.month = stoi(startDate.substr(3, 2));
        cruises[cruise].startDate.year = stoi(startDate.substr(6, 4));
    }

    printf("Искате ли да редактирате датата на връщане? [y/n] ");
    cin >> answer;
    if (answer == 'y') {
        printf("Въведи нова дата връщане [формат: 01.01.2022]: ");
        string endDate;
        cin >> endDate;
        cruises[cruise].startDate.day = stoi(endDate.substr(0, 2));
        cruises[cruise].startDate.month = stoi(endDate.substr(3, 2));
        cruises[cruise].startDate.year = stoi(endDate.substr(6, 4));
    }

    printf("Искате ли да редактирате името на кораба? [y/n] ");
    cin >> answer;
    if (answer == 'y') {
        do {
            printf("Въведи ново име на кораба: ");
            cin.ignore();
            getline(cin, cruises[cruise].ship.name);
        } while (cruises[cruise].ship.name[0] == '\0');
    }

    printf("Искате ли да редактирате името на капитана на кораба? [y/n] ");
    cin >> answer;
    if (answer == 'y') {
        do {
            printf("Въведи ново име на капитана на кораба: ");
            cin.ignore();
            getline(cin, cruises[cruise].ship.captainName);
        } while (cruises[cruise].ship.captainName[0] == '\0');
    }

    printf("Искате ли да редактирате първа класа? [y/n] ");
    cin >> answer;
    if (answer == 'y') {
        printf("Въведи нова цена: ");
        cin >> cruises[cruise].ship.firstClass.price;
        printf("Въведи нов брой пътници: ");
        cin >> cruises[cruise].ship.firstClass.passengers;
    }

    printf("Искате ли да редактирате втора класа? [y/n] ");
    cin >> answer;
    if (answer == 'y') {
        printf("Въведи нова цена: ");
        cin >> cruises[cruise].ship.secondClass.price;
        printf("Въведи нов брой пътници: ");
        cin >> cruises[cruise].ship.secondClass.passengers;
    }
}

bool compareDates(const Date &date1, const Date &date2) {
    if (date1.year < date2.year)
        return true;
    if (date1.year == date2.year && date1.month < date2.month)
        return true;
    if (date1.year == date2.year && date1.month == date2.month && date1.day < date2.day)
        return true;

    return false;
}

void printFoundCruise(Cruise cruises[], int &currentCruisesCount) {
    if (!cruisesExist(currentCruisesCount)) return;

    int cruise;
    printf("Въведи номер на круиз: ");
    cin >> cruise;

    if (!cruiseExists(currentCruisesCount, cruise)) return;

    printCruise(cruises, currentCruisesCount, cruise);
}

void printCruise(Cruise cruises[], int &currentCruisesCount, int cruise) {
    Cruise current = cruises[cruise];
    printf("============{ КРУИЗ %d }============\n", cruise);
    printf("Маршрут: ");
    int routeSize = (int) current.route.size();
    for (int i = 0; i < routeSize; i++) {
        printf("%s %s", current.route.at(i).c_str(), i < routeSize - 1 ? "-> " : "\n");
    }
    printf("Дата потегляне: %02d.%02d.%04d\n", current.startDate.day, current.startDate.month, current.startDate.year);
    printf("Дата връщане:   %02d.%02d.%04d\n", current.endDate.day, current.endDate.month, current.endDate.year);
    printf("Име на кораб:   %s\n", current.ship.name.c_str());
    printf("Име на капитан: %s\n", current.ship.captainName.c_str());
    printf("1-ВА КЛАСА: \tЦЕНА: %g\t\tБРОЙ ПЪТНИЦИ: %d\n", current.ship.firstClass.price,
           current.ship.firstClass.passengers);
    printf("2-РА КЛАСА: \tЦЕНА: %g\t\tБРОЙ ПЪТНИЦИ: %d\n", current.ship.secondClass.price,
           current.ship.secondClass.passengers);
}

void filterCruises(Cruise cruises[], int &currentCruisesCount, const string &criteria) {
    if (!cruisesExist(currentCruisesCount)) return;

    if (criteria == "startDate") {
        printf("======{ НАЙ-СКОРОШНИ КРУИЗИ }======\n");
        vector<Date> dates(currentCruisesCount);
        for (int i = 0; i < currentCruisesCount; i++) {
            dates[i] = cruises[i].startDate;
        }
        sort(dates.begin(), dates.end(), compareDates);

        for (int i = 0; i < currentCruisesCount; i++) {
            if (cruises[i].startDate.day == dates[0].day && cruises[i].startDate.month == dates[0].month &&
                cruises[i].startDate.year == dates[0].year) {
                printCruise(cruises, currentCruisesCount, i + 1);
            }
        }
    } else if (criteria == "destination") {
        printf("======{ ТЪРСЕНЕ НА КРУИЗИ ПО ДЕСТИНАЦИЯ }======\n");
        string location;
        printf("Въведи локация: ");
        cin >> location;

        for (int i = 0; i < currentCruisesCount; i++) {
            for (int y = 0; y < cruises[i].route.size(); i++) {
                if (location == cruises[i].route[y]) {
                    printCruise(cruises, currentCruisesCount, i + 1);
                    break;
                }
            }
        }
    }
}

void fillTestData(Cruise cruises[], int &currentCruisesCount) {
    vector<string> route1{"Варна", "Рим", "Лисабон", "Берген", "Норвежки фьорди", "Санкт Петербург", "Варна"};
    vector<string> route2{"Варна", "Рим", "Ню Йорк", "Флорида", "Лос Анджелис", "Варна"};
    vector<string> route3{"Пекин", "Токио", "Пхенян", "Пекин"};
    vector<string> route4{"Бриджтаун", "Розо", "Тортола", "Сейнт Джоунс", "Сен Маартен", "Бриджтаун"};
    cruises[currentCruisesCount++] = {route1,
                                      {"Symphony of the Seas", "Rob Hempstead", {2499.99, 1500}, {1499.99, 3500}},
                                      {14, 2, 2021}, {14, 3, 2022}};
    cruises[currentCruisesCount++] = {route2,
                                      {"Harmony of the Seas", "Johnny Faevelen", {2249.99, 1400}, {1249.99, 3000}},
                                      {7, 1, 2022}, {14, 1, 2022}};
    cruises[currentCruisesCount++] = {route3,
                                      {"Oasis of the Seas", "Thore Thorolvsen", {1999.99, 1000}, {999.99, 2500}},
                                      {5, 8, 2022}, {15, 8, 2022}};
    cruises[currentCruisesCount++] = {route4, {"Allure of the Seas", "Hernan Zini", {1749.99, 900}, {749.99, 2100}},
                                      {3, 3, 2022}, {10, 3, 2022}};
}

bool cruisesExist(int &currentCruisesCount) {
    if (currentCruisesCount < 1) {
        printf("==============================================\n");
        printf("Няма въведени круизи!\n");
        return false;
    }
    return true;
}

bool cruiseExists(int &currentCruisesCount, int &cruise) {
    if (cruise >= currentCruisesCount || cruise < 0) {
        printf("==============================================\n");
        printf("Няма такъв круиз!\n");
        return false;
    }
    return true;
}

void getCurrentDate(int &day, int &month, int &year) {
    time_t currentTime;
    struct tm *localTime;

    time(&currentTime);
    localTime = localtime(&currentTime);

    day = localTime->tm_mday;
    month = localTime->tm_mon + 1;
    year = localTime->tm_year + 1900;
}