#include <iostream>
#include <fstream>
#include <map>
#include <string>

using namespace std;

map<string, int, greater<string>> readNames(const string& inputFileName, int& recordCount) {
    map<string, int, greater<string>> mapNames; 
    ifstream inputFile(inputFileName);

    if (!inputFile.is_open()) {
        cout << "Error opening input file!" << endl;
        return mapNames;
    }

    double regNumberDouble; 
    string bankName;
    recordCount = 0;
    while (inputFile >> regNumberDouble) {
        // Пропускаем точку с запятой
        inputFile.ignore(1);
        getline(inputFile, bankName);

        if (bankName.front() == '"' && bankName.back() == '"') {
            bankName = bankName.substr(1, bankName.length() - 2);
        }

        int regNumber = static_cast<int>(regNumberDouble);
        mapNames[bankName] = regNumber;
        recordCount++;
    }

    inputFile.close();
    return mapNames;
}

void writeNames(const map<string, int, greater<string>>& mapNames,
    const map<int, string>& mapNumb,
    const string& outputFileNameByName,
    const string& outputFileNameByNumb) {


    ofstream outputFileByName(outputFileNameByName);
    if (!outputFileByName.is_open()) {
        cout << "Error opening output file for names!" << endl;
        return;
    }

    for (const auto& pair : mapNames) {
        outputFileByName << pair.first << ";" << pair.second << endl;
    }
    outputFileByName.close();

    ofstream outputFileByNumb(outputFileNameByNumb);
    if (!outputFileByNumb.is_open()) {
        cout << "Error opening output file for numbers!" << endl;
        return;
    }

    for (const auto& pair : mapNumb) {
        outputFileByNumb << pair.first << ";" << pair.second << endl;
    }
    outputFileByNumb.close();
}

int main() {
    string inputFileName = "NAMES.TXT";
    string outputFileNameByName = "NAMES_name.TXT";
    string outputFileNameByNumb = "NAMES_numb.TXT";

    map<string, int, greater<string>> mapNames;
    map<int, string> mapNumb;
    int recordCount;

    mapNames = readNames(inputFileName, recordCount);

    cout << "Number of records read from NAMES.TXT: " << recordCount << endl;

    for (const auto& pair : mapNames) {
        mapNumb[pair.second] = pair.first;
    }

    writeNames(mapNames, mapNumb, outputFileNameByName, outputFileNameByNumb);

    cout << "Sorting completed. Check output files." << endl;

    return 0;
}