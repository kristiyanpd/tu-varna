#include <iostream>
#include <windows.h>
#include <string>
#include <algorithm>
#include <vector>
#include <unordered_map>

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

void printCruise(Cruise cruises[], int &currentCruisesCount, int cruise);

void printFoundCruise(Cruise cruises[], int &currentCruisesCount);

void printAllCruises(Cruise cruises[], int &currentCruisesCount);

void filterCruises(Cruise cruises[], int &currentCruisesCount, const string &criteria);

void sortCruises(Cruise cruises[], int &currentCruisesCount, const string &criteria);

void sortAlgorithm(Cruise cruises[], int &currentCruisesCount, const string &criteria);

/////////// Helper Methods ///////////
void getCurrentDate(int &day, int &month, int &year);

void fillTestData(Cruise cruises[], int &currentCruisesCount);

bool cruisesExist(int &currentCruisesCount);

bool cruiseExists(int &currentCruisesCount, int &cruise);

int compareDates(const Date &date1, const Date &date2);

int compareNames(string &str1, string &str2);

bool periodCheck(Date start, Date end, const Cruise &cruise);

Date inputDate(string &dateInput);

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
        printf("0. Излез от менюто.\n");
        printf("1. Въвеждане на тестови круизи.\n");
        printf("2. Добавяне на едно ново морско пътуване.\n");
        printf("3. Добавяне на списък от пътувания.\n");
        printf("4. Показване на информация за кораб.\n");
        printf("5. Извеждане на пътуванията с най-ранна дата на тръгване.\n");
        printf("6. Извеждане на пътуванията към определена дестинация.\n");
        printf("7. Корекция на данни за пътуване.\n");
        printf("8. Извеждане на пътуване на най-ниска обща цена.\n");
        printf("9. Извеждане на пътуване с най-много пътници.\n");
        printf("10. Извеждане на кораб с най-много круизи.\n");
        printf("11. Одит на морските пътувания.\n");
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
            case 8:
                filterCruises(cruises, currentCruisesCount, "minPrice");
                break;
            case 9:
                filterCruises(cruises, currentCruisesCount, "maxPassengers");
                break;
            case 10:
                filterCruises(cruises, currentCruisesCount, "maxCruisesShip");
                break;
            case 11:
                int selectedSubmenu;
                do {
                    printf("============{ ОДИТ НА КРУИЗИТЕ }============\n");
                    printf("0. Излез от подменюто.\n");
                    printf("1. Извеждане на пътувания, сортирани по име на кораб.\n");
                    printf("2. Извеждане на пътувания за период, сортирани по ден на тръгване.\n");
                    printf("3. Извеждане на пътувания по дестинация и ден на тръгване, сортирани по ден на тръгване.\n");
                    printf("Избрана опция: ");

                    cin >> selectedSubmenu;
                    switch (selectedSubmenu) {
                        case 0:
                            break;
                        case 1:
                            sortCruises(cruises, currentCruisesCount, "shipName");
                            break;
                        case 2:
                            filterCruises(cruises, currentCruisesCount, "period");
                            break;
                        case 3:
                            filterCruises(cruises, currentCruisesCount, "destinationAndStartDate");
                            break;
                        default:
                            printf("Невалидна опция!\n");
                    }
                } while (selectedSubmenu != 0);
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

    printf("==={ ВЪВЕЖДАНЕ НА ПЕРИОД ПЪТУВАНЕ }===\n");

    // Въвеждане на дата потегляне
    printf("Въведи дата потегляне [формат: 01.01.2022]: ");
    string startDate;
    cin >> startDate;
    cruises[currentCruisesCount].startDate = inputDate(startDate);

    // Въвеждане на дата връщане
    printf("Въведи дата връщане   [формат: 01.01.2022]: ");
    string endDate;
    cin >> endDate;
    cruises[currentCruisesCount].endDate = inputDate(endDate);

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
    printf("============{ УСПЕШНО ДОБАВЯНЕ НА КРУИЗ %d }============\n", currentCruisesCount);
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

    if (compareDates(cruises[cruise].startDate, current) > 0) {
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
        cruises[currentCruisesCount].startDate = inputDate(startDate);
    }

    printf("Искате ли да редактирате датата на връщане? [y/n] ");
    cin >> answer;
    if (answer == 'y') {
        printf("Въведи нова дата връщане [формат: 01.01.2022]: ");
        string endDate;
        cin >> endDate;
        cruises[currentCruisesCount].endDate = inputDate(endDate);
    }

    printf("Искате ли да редактирате името на кораба? [y/n] ");
    cin >> answer;
    if (answer == 'y') {
        cin.ignore();
        do {
            printf("Въведи ново име на кораба: ");
            getline(cin, cruises[cruise].ship.name);
        } while (cruises[cruise].ship.name[0] == '\0');
    }

    printf("Искате ли да редактирате името на капитана на кораба? [y/n] ");
    cin >> answer;
    if (answer == 'y') {
        cin.ignore();
        do {
            printf("Въведи ново име на капитана на кораба: ");
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

void printFoundCruise(Cruise cruises[], int &currentCruisesCount) {
    if (!cruisesExist(currentCruisesCount)) return;

    int cruise;
    printf("Въведи номер на круиз: ");
    cin >> cruise;

    if (!cruiseExists(currentCruisesCount, cruise)) return;

    printCruise(cruises, currentCruisesCount, cruise);
}

void printAllCruises(Cruise cruises[], int &currentCruisesCount) {
    for (int i = 0; i < currentCruisesCount; i++) printCruise(cruises, currentCruisesCount, i);
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
    } else if (criteria == "minPrice") {
        printf("======{ КРУИЗ С НАЙ-НИСКА ОБЩА ЦЕНА }======\n");
        float minPrice = cruises[0].ship.firstClass.price + cruises[0].ship.secondClass.price;
        int cruiseId = 0;
        for (int i = 1; i < currentCruisesCount; i++) {
            Cruise current = cruises[i];
            float calculatedPrice = current.ship.firstClass.price + current.ship.secondClass.price;
            if (calculatedPrice < minPrice) {
                minPrice = calculatedPrice;
                cruiseId = i;
            }
        }
        printCruise(cruises, currentCruisesCount, cruiseId);
    } else if (criteria == "maxPassengers") {
        printf("======{ КРУИЗ С НАЙ-МНОГО ПЪТНИЦИ }======\n");
        int passengersCount = cruises[0].ship.firstClass.passengers + cruises[0].ship.secondClass.passengers;
        int cruiseId = 0;
        for (int i = 1; i < currentCruisesCount; i++) {
            Cruise current = cruises[i];
            int passengers = current.ship.firstClass.passengers + current.ship.secondClass.passengers;
            if (passengers > passengersCount) {
                passengersCount = passengers;
                cruiseId = i;
            }
        }
        printCruise(cruises, currentCruisesCount, cruiseId);
    } else if (criteria == "maxCruisesShip") {
        printf("======{ НАЙ-МНОГО КРУИЗИ }======\n");
        unordered_map<string, int> shipCruisesCount;
        for (int i = 0; i < currentCruisesCount; i++) {
            shipCruisesCount[cruises[i].ship.name] += 1;
        }

        string shipName = to_string(shipCruisesCount[cruises[0].ship.name]);
        int maxOccurrences = shipCruisesCount[shipName];
        for (const auto &pair: shipCruisesCount) {
            if (pair.second > maxOccurrences) {
                shipName = pair.first;
                maxOccurrences = pair.second;
            }
        }
        printf("Корабът \"%s\" е използван най-много!\n", shipName.c_str());
    } else if (criteria == "period") {
        printf("======{ КРУИЗИ ПО ПЕРИОД }======\n");
        string startDateStr, endDateStr;
        printf("Въведи начална дата [01.01.2022]: ");
        cin >> startDateStr;
        Date startDate = inputDate(startDateStr);
        printf("Въведи крайна дата [01.01.2022]: ");
        cin >> endDateStr;
        Date endDate = inputDate(endDateStr);
        vector<Cruise> filtered;

        for (int i = 0; i < currentCruisesCount; i++) {
            if (periodCheck(startDate, endDate, cruises[i])) {
                filtered.push_back(cruises[i]);
            }
        }
        int size = (int) filtered.size();
        Cruise *copy = &filtered[0];
        sortCruises(copy, size, "startDate");
    } else if (criteria == "destinationAndStartDate") {
        printf("======{ КРУИЗИ ПО ДЕСТИНАЦИЯ И ДЕН НА ТРЪГВАНЕ }======\n");
        string destination, startDateStr;
        printf("Въведи дестинация: ");
        cin >> destination;
        printf("Въведи начална дата [01.01.2022]: ");
        cin >> startDateStr;
        Date startDate = inputDate(startDateStr);
        vector<Cruise> filtered;

        for (int i = 0; i < currentCruisesCount; i++) {
            if (compareDates(startDate, cruises[i].startDate) == 0) {
                for (int j = 0; j < cruises[i].route.size(); j++) {
                    if (cruises[i].route[j] == destination) {
                        filtered.push_back(cruises[i]);
                        break;
                    }
                }
            }
        }
        int size = (int) filtered.size();
        Cruise *copy = &filtered[0];
        sortCruises(copy, size, "startDate");
    }
}

void sortCruises(Cruise cruises[], int &currentCruisesCount, const string &criteria) {
    if (!cruisesExist(currentCruisesCount)) return;

    auto *copy = new Cruise[currentCruisesCount];
    for (int i = 0; i < currentCruisesCount; i++) {
        copy[i] = cruises[i];
    }

    sortAlgorithm(copy, currentCruisesCount, criteria);
    printAllCruises(copy, currentCruisesCount);
}

void sortAlgorithm(Cruise cruises[], int &currentCruisesCount, const string &criteria) {
    bool swapped;
    for (int i = 0; i < currentCruisesCount - 1; i++) {
        swapped = false;
        for (int j = 0; j < currentCruisesCount - i - 1; j++) {
            if (criteria == "shipName") {
                if (compareNames(cruises[j].ship.name, cruises[j + 1].ship.name) == 1) {
                    Cruise temp = cruises[j];
                    cruises[j] = cruises[j + 1];
                    cruises[j + 1] = temp;
                    swapped = true;
                }
            } else if (criteria == "startDate") {
                if (compareDates(cruises[j].startDate, cruises[j + 1].startDate) < 0) {
                    Cruise temp = cruises[j];
                    cruises[j] = cruises[j + 1];
                    cruises[j + 1] = temp;
                    swapped = true;
                }
            }
        }
        if (!swapped) break;
    }
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

void fillTestData(Cruise cruises[], int &currentCruisesCount) {
    vector<string> route1{"Варна", "Рим", "Лисабон", "Берген", "Норвежки фьорди", "Санкт Петербург", "Варна"};
    vector<string> route2{"Варна", "Рим", "Ню Йорк", "Флорида", "Лос Анджелис", "Варна"};
    vector<string> route3{"Пекин", "Токио", "Пхенян", "Пекин"};
    vector<string> route4{"Бриджтаун", "Розо", "Тортола", "Сейнт Джоунс", "Сен Маартен", "Бриджтаун"};
    vector<string> route5{"Хамбург", "Северен Атлантически океан"};

    Ship symphonyOfTheSeas{"Symphony of The Seas", "Rob Hempstead", {2499.99, 1500}, {1499.99, 3500}};
    Ship harmonyOfTheSeas{"Harmony of The Seas", "Johnny Faevelen", {2249.99, 1400}, {1249.99, 3000}};
    Ship oasisOfTheSeas{"Oasis of The Seas", "Thore Thorolvsen", {1999.99, 1000}, {999.99, 2500}};
    Ship allureOfTheSeas{"Allure of The Seas", "Hernan Zini", {1749.99, 900}, {749.99, 2100}};
    Ship bismarck{"Bismarck", "Otto Ernst Lindemann", {4999.99, 103}, {9.99, 1962}};

    cruises[currentCruisesCount++] = {route1, symphonyOfTheSeas, {14, 2, 2021}, {14, 3, 2022}};
    cruises[currentCruisesCount++] = {route2, harmonyOfTheSeas, {7, 1, 2022}, {14, 1, 2022}};
    cruises[currentCruisesCount++] = {route2, bismarck, {14, 2, 2021}, {14, 1, 2022}};
    cruises[currentCruisesCount++] = {route3, oasisOfTheSeas, {5, 8, 2022}, {15, 8, 2022}};
    cruises[currentCruisesCount++] = {route4, allureOfTheSeas, {3, 3, 2022}, {10, 3, 2022}};
    cruises[currentCruisesCount++] = {route2, allureOfTheSeas, {5, 7, 2022}, {10, 7, 2022}};
    cruises[currentCruisesCount++] = {route5, bismarck, {1, 2, 1939}, {27, 5, 1940}};
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

int compareDates(const Date &date1, const Date &date2) {
    if (date1.year < date2.year)
        return 1;
    else if (date1.year > date2.year)
        return -1;
    if (date1.year == date2.year && date1.month < date2.month)
        return 1;
    if (date1.year == date2.year && date1.month > date2.month)
        return -1;
    if (date1.year == date2.year && date1.month == date2.month && date1.day < date2.day)
        return 1;
    if (date1.year == date2.year && date1.month == date2.month && date1.day > date2.day)
        return -1;

    return 0;
}

int compareNames(string &str1, string &str2) {
    for (int i = 0; i < str1.size(); i++) {
        if (str1[i] > str2[i]) return 1;
        else if (str1[i] < str2[i]) return 0;
    }
    return 0;
}

bool periodCheck(Date start, Date end, const Cruise &cruise) {
    return compareDates(cruise.startDate, start) <= 0 && compareDates(cruise.endDate, end) >= 0;
}

Date inputDate(string &dateInput) {
    Date validation{};
    try {
        validation.day = stoi(dateInput.substr(0, 2));
        validation.month = stoi(dateInput.substr(3, 2));
        validation.year = stoi(dateInput.substr(6, 4));
    } catch (exception &err) {
        printf("Невалиден формат! Моля въведи дата в този формат [01.01.2022]: ");
        cin >> dateInput;
        validation = inputDate(dateInput);
    }

    while (validation.year < 1900 || validation.year > 2100) {
        printf("Моля въведи година между 1900 и 2100: ");
        cin >> validation.year;
    }

    while (validation.month < 1 || validation.month > 12) {
        printf("Моля въведи месец между 1 и 12: ");
        cin >> validation.month;
    }

    int maxDays;
    if (validation.month != 2) {
        if (validation.month < 8) {
            maxDays = (validation.month % 2 == 0) ? 30 : 31;
        } else {
            maxDays = (validation.month % 2 == 0) ? 31 : 30;
        }
    } else {
        maxDays = (validation.year % 4 == 0 && (validation.year % 100 != 0 || validation.year % 400 == 0)) ? 28 : 27;
    }

    while (validation.day < 1 || validation.day > maxDays) {
        printf("Моля въведи ден между 1 и %d: ", maxDays);
        cin >> validation.day;
    }

    return validation;
}