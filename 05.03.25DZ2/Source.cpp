#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <numeric> 


struct NameData {
    std::string name;
    char gender; 
    int count;

    bool operator<(const NameData& other) const {
        if (gender != other.gender) return gender < other.gender;
        return name < other.name;
    }

    bool operator==(const NameData& other) const {
        return name == other.name && gender == other.gender;
    }
};


std::vector<NameData> loadData(const std::string& filename) {
    std::vector<NameData> data;
    std::ifstream file(filename);
    if (file.is_open()) {
        std::string line;
        std::getline(file, line);

        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string name, genderStr;
            int count;
            std::getline(ss, name, ',');
            std::getline(ss, genderStr, ',');
            ss >> count;
            data.push_back({ name, genderStr[0], count });
        }
        file.close();
    }
    else {
        std::cerr << "Ошибка открытия файла: " << filename << 
            std::endl;
    }
    return data;
}


void DisplayInfo() {

    std::vector<NameData> allNames = loadData("Gender_names_rus.txt");



    std::vector<NameData> femaleNames;
    std::vector<NameData> maleNames;
    for (const auto& nameData : allNames) {
        if (nameData.gender == 'f') femaleNames.push_back(nameData);
        else if (nameData.gender == 'm') maleNames.push_back(nameData);
    }


    auto mostPopular = [](const std::vector<NameData>& names) {
        if (names.empty()) return NameData{ "", ' ', 0 };
        return *std::max_element(names.begin(), names.end(), [](const NameData& a, const NameData& b) {
            return a.count < b.count;
            });
        };


    auto countZeroNames = [](const std::vector<NameData>& names) {
        return std::count_if(names.begin(), names.end(), [](const NameData& name) { return name.count == 0; });
        };


    auto calculateMedian = [](const std::vector<NameData>& names) {
        std::vector<int> counts;
        for (const auto& name : names) counts.push_back(name.count);
        std::sort(counts.begin(), counts.end());
        if (counts.size() % 2 == 0)
            return (double)(counts[counts.size() / 2 - 1] + counts[counts.size() / 2]) / 2;
        return (double)counts[counts.size() / 2];
        };


    auto calculateAverage = [](const std::vector<NameData>& names) {
        if (names.empty()) return 0.0;
        return std::accumulate(names.begin(), names.end(), 0.0, [](double sum, const NameData& name) { return sum + name.count; }) / names.size();
        };



    std::cout << "Самое популярное имя среди всех: " << mostPopular(allNames).name << " (" << mostPopular(allNames).count << ")" <<
        std::endl;
    std::cout << "Самое популярное имя среди женщин: " << mostPopular(femaleNames).name << " (" << mostPopular(femaleNames).count << ")" << 
        std::endl;
    std::cout << "Самое популярное имя среди мужчин: " << mostPopular(maleNames).name << " (" << mostPopular(maleNames).count << ")" <<
        std::endl;
    std::cout << "Количество имен без носителей (всего): " << countZeroNames(allNames) << 
        std::endl;
    std::cout << "Количество имен без носителей (женщины): " << countZeroNames(femaleNames) << 
        std::endl;
    std::cout << "Количество имен без носителей (мужчины): " << countZeroNames(maleNames) << 
        std::endl;
    std::cout << "Медиана количества носителей (всего): " << calculateMedian(allNames) <<
        std::endl;
    std::cout << "Медиана количества носителей (женщины): " << calculateMedian(femaleNames) << 
        std::endl;
    std::cout << "Медиана количества носителей (мужчины): " << calculateMedian(maleNames) << 
        std::endl;
    std::cout << "Среднее количество носителей (всего): " << calculateAverage(allNames) << 
        std::endl;
    std::cout << "Среднее количество носителей (женщины): " << calculateAverage(femaleNames) << 
        std::endl;
    std::cout << "Среднее количество носителей (мужчины): " << calculateAverage(maleNames) << 
        std::endl;



}




int main() {

    DisplayInfo();


    return 0;
}
