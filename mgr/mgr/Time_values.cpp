#include "Time_values.h"
Time_values::Time_values(std::string filename)
{
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "File cannot be open: " << filename << std::endl;
        return;
    }

    std::unordered_map<std::string, double*> variableMap = {
        {"start:",  &start},
        {"delta:",  &delta},
        {"end:",    &end},
        {"y0:",     &y0}
    };

    std::string line;
    while (getline(file, line)) {
        std::istringstream lineStream(line);
        std::string key;
        double value;

        if (lineStream >> key >> value) {
            if (variableMap.find(key) != variableMap.end()) {
                *variableMap[key] = value;
            }
            else {
                std::cerr << "Niepoprawny format lub nieznana zmienna w linii: " << line << std::endl;
            }
        }
    }

    file.close();
}
