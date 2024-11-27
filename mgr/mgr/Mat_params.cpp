#include "Mat_params.h"
using namespace std;

Mat_params::Mat_params() {}


Mat_params::Mat_params(string& filename)
{

    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "File cannot be open: " << filename << std::endl;
        return;
    }

    unordered_map<string, double*> variableMap = {
        {"epsilon:", &epsilon},
        {"T:", &T}, // Temperature
        {"D:", &D},
        {"mi:", &mi},
        {"ro_poprzednie:", &ro_poprzednie},
        {"ro_t_tcr:", &ro_t_tcr},
        {"t_poprzednie:", &t_poprzednie},
        {"Q:", &Q},
        {"b:", &b},
        {"tcr_start:", &tcr_start},
        {"R:", &R},
    };

    string line;
    while (getline(file, line)) {
        istringstream lineStream(line);
        string key;
        double value;

        if (lineStream >> key >> value) {
            if (variableMap.find(key) != variableMap.end()) {
                *variableMap[key] = value;
            }
            else {
                cerr << "Niepoprawny format lub nieznana zmienna w linii: " << line << endl;
            }
        }
    }

    file.close();
    Z = count_Z();

    //if (D == NULL)
    //{
    //    std::cerr << "Argument D has not been provided\n";
    //    return;
    //}
}

double Mat_params::count_Z()
{
    return epsilon * exp(Q / (T * 8.314));
}