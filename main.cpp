#include <fstream>
#include <iostream>
#include <string>
#include <sstream> // Для разбора строк
#include <Heap/Heap.h>
#include "HashTable.h"

int getVarOrInt(std::string expretion, HashTable<int> **variables){
    int res;
    try{
        res = (*variables)->get(expretion);
    }catch (...) {
        res = std::stoi(expretion);
    }
        // std::cout << expretion << "  " << res << '\n' ;
    return res;
}

int mathExpretion(std::string expretion, HashTable<int> **variables){
    expretion.erase(remove_if(expretion.begin(), expretion.end(), isspace), expretion.end());
    size_t plusPos = expretion.find('+');
    if (plusPos != std::string::npos){
        int left = getVarOrInt(expretion.substr(0, plusPos), variables);
        int right = getVarOrInt(expretion.substr(plusPos + 1), variables);
        return left + right;
    }
    size_t minusPos = expretion.find('-');
    int left = getVarOrInt(expretion.substr(0, minusPos), variables);
    int right = getVarOrInt(expretion.substr(minusPos + 1), variables);
    return left - right;
}

int parseExpretion(std::string expretion, HashTable<int> **variables){
    if (expretion.find('+') != std::string::npos || expretion.find('-') != std::string::npos){
        return mathExpretion(expretion, variables);
    }
    return getVarOrInt(expretion, variables);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <input file>" << std::endl;
        return 1;
    }

    std::ifstream inputFile(argv[1]);
    if (!inputFile.is_open()) {
        std::cerr << "Could not open file " << argv[1] << std::endl;
        return 1;
    }

    auto heap = new Heap(1024);

    auto raw_hash_table = heap->allocate(sizeof(HashTable<int>));
    auto variables = reinterpret_cast<HashTable<int> **>(raw_hash_table);
    (*variables)->init(heap);

    std::string line;

    while (std::getline(inputFile, line)) {
        // Проверяем наличие знака равенства в строке
        size_t equalPos = line.find('=');
        if (equalPos != std::string::npos) {
            // Извлекаем имя переменной и значение
            std::string varName = line.substr(0, equalPos);
            std::string expretion = line.substr(equalPos + 1);

            // Удаляем пробелы из имени переменной, если они есть
            varName.erase(remove_if(varName.begin(), varName.end(), isspace), varName.end());
            // Добавляем переменную и её значение в хеш-таблицу

            (*variables)->set(varName.c_str(), parseExpretion(expretion, variables));
            
        }else if(line.find("print") != std::string::npos){
            std::string expretion = line.substr(6);
            std::cout << parseExpretion(expretion, variables) << '\n';

        }
    }

    heap->logUsage();

    inputFile.close();

    return 0;
}
