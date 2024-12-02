
#include <iostream>
#include <string>
#include <Windows.h>
#include <iostream>
const int TABLE_SIZE = 20;


struct BankAccount {
    int accountNumber;
    std::string name;
    std::string address;

};

/*struct BankTable {
    BankAccount table[TABLE_SIZE];
    BankTable() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            table[i].accountNumber = -1;
            table[i].name = "";
            table[i].address = "";
        }
    }

};*/

struct HashItem {
    int key;
    int accountIndex;
    bool prK; //признак включения ключа при коллизии (по условию)
};

struct HashTable {
    HashItem table[TABLE_SIZE];
    HashTable() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            table[i].key = -1;
            table[i].prK = false;
        }
    }

};


int hashFunction(int key) {
    return key % TABLE_SIZE;
}


void insert(HashTable& hashTable, BankAccount account, int ind) {
    int index = hashFunction(account.accountNumber);
    int i = 0;
    while (i < TABLE_SIZE) {
        int pos = (index + i) % TABLE_SIZE;
        if (hashTable.table[pos].key < 1) {
            hashTable.table[pos].key = account.accountNumber;
            hashTable.table[pos].accountIndex = ind;
            if (i != 0) {
                hashTable.table[pos].prK = true;
            }
            break;
        }
        else if (hashTable.table[pos].key == account.accountNumber) {
            //std::cout << "Такая запись уже существует!" << std::endl;
            break;
        }
        i++;
    }

}

void find(HashTable& hashTable, BankAccount accounts[], int accountNumber) {
    int index = hashFunction(accountNumber);
    int i = 0;
    while (i < TABLE_SIZE) {
        int pos = (index + i) % TABLE_SIZE;
        if (hashTable.table[pos].key == accountNumber) {
            std::cout << "Ключ: " << hashTable.table[pos].key << std::endl;
            std::cout << "Имя: " << accounts[hashTable.table[pos].accountIndex].name << std::endl;
            std::cout << "Адрес:  " << accounts[hashTable.table[pos].accountIndex].address << std::endl;
            return;
        }
        i++;
    }
    std::cout << "Ничего не нашлось!" << std::endl;
}

void printAllInfo(HashTable& hashTable, BankAccount accounts[]) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        int index = hashFunction(accounts[i].accountNumber);
        int j = 0;
        while (j < TABLE_SIZE) {
            int pos = (index + j) % TABLE_SIZE;
            if (hashTable.table[pos].key > 0) {
                std::cout << "Пользователь "<< (i + 1) << ": " << std::endl;
                std::cout << "Ключ: " << hashTable.table[pos].key << std::endl;
                std::cout << "Имя: " << accounts[hashTable.table[pos].accountIndex].name << std::endl;
                std::cout << "Адрес:  " << accounts[hashTable.table[pos].accountIndex].address << std::endl;
                break;
            }
            else if (!(hashTable.table[pos].prK)) { break; }
            
            j++; 
            }
    }
        
}

void printAccounts(BankAccount accounts[]) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        std::cout << "Индекс пользователя: " << i << std::endl;
        std::cout << "Номер аккаунта: " << accounts[i].accountNumber << std::endl;
        std::cout << "Адрес: "<< accounts[i].address << std::endl;
        std::cout << "Имя: " << accounts[i].name << std::endl;

    }
}

void remove(HashTable& hashTable, int accountKey) {
    int index = hashFunction(accountKey);
    int i = 0;
    while (i < TABLE_SIZE) {
        int pos = (index + i) % TABLE_SIZE;
        if (hashTable.table[pos].key == accountKey) {
            hashTable.table[pos].key = -1;
            std::cout << "Удалил!" << std::endl;
            break;
        }
        else if (hashTable.table[pos].key == -1) {
            std:: cout << "Не могу удалить того, чего не существует!" << std::endl;
        }
        i++;
    }
    
}


void test() {
    HashTable hashTable;
    BankAccount accounts[TABLE_SIZE] = {{1234567, "Ivanov Ivan", "Moscow"},
        {2345678, "Petrov Petr", "Saint Petersburg"},
        {3456789, "Sidorov Sid", "Novosibirsk"},
        {4567890, "Smirnov S", "Ekaterinburg"},
        {5678901, "Fedorov F", "Kazan"},
        {6789012, "Dmitriev D", "Nizhny Novgorod"},
        {7890123, "Kuznetsov K", "Chelyabinsk"},
        {8901234, "Popov P", "Ufa"},
        {9012345, "Lebedev L", "Samara"}};

    for (int i = 0; i < TABLE_SIZE; i++) {
        insert(hashTable, accounts[i], i);
    }
    //find(hashTable, accounts, 2345678);
    //printAllInfo(hashTable, accounts);
    //remove(hashTable, 2345678);
    //find(hashTable, accounts, 2345678);
    //printAllInfo(hashTable, accounts);


    
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    HashTable hashTable;
    BankAccount accounts[TABLE_SIZE] = { {1234567, "Ivanov Ivan", "Moscow"},
        {2345678, "Petrov Petr", "Saint Petersburg"},
        {3456789, "Sidorov Sid", "Novosibirsk"},
        {4567890, "Smirnov S", "Ekaterinburg"},
        {5678901, "Fedorov F", "Kazan"},
        {6789012, "Dmitriev D", "Nizhny Novgorod"},
        {7890123, "Kuznetsov K", "Chelyabinsk"},
        {8901234, "Popov P", "Ufa"},
        {9012345, "Lebedev L", "Samara"} };

    for (int i = 0; i < TABLE_SIZE; i++) {
        insert(hashTable, accounts[i], i);
    }


    
    while (true) {
        std::string command;
        std::cout << "Введи команду: ";
        std::cin >> command;
        if (command == "Вывод") {
            printAllInfo(hashTable, accounts);
        }
        if (command == "Удалить") {
            int key;
            std::cout << "Введи ключ: ";
            std::cin >> key;
            remove(hashTable, key);
        }
        if (command == "Найти") {
            int key;
            std::cout << "Введи ключ: ";
            std::cin >> key;
            find(hashTable, accounts, key);
        }
        if (command == "Вставить") {
            int key;
            std::cout << "Введи ключ: ";
            std::cin >> key;

            std::string name;
            std::cout << "Введи ФИО: ";
            std::cin >> name;

            std::string adress;
            std::cout << "Введи  адрес: ";
            std::cin >> adress;

            int accountIndex = -1;
            for (int i = 0; i < TABLE_SIZE; i++) {
                if (accounts[i].accountNumber == 0) {
                    accounts[i].accountNumber = key;
                    accounts[i].address = adress;
                    accounts[i].name = name;
                    accountIndex = i;
                    break;
                }
            }
            if (accountIndex == -1) { std::cout << "Место кончилось..." << std::endl; }
            else { insert(hashTable, { key, name, adress }, accountIndex); }
        }

        if (command == "0") {
            break;
        }
    }
   
}


