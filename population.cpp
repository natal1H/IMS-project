/**
 * IMS project - Epidemiological model in macro scale
 *
 * @file population.cpp
 *
 * @author Natália Holkova (xholko02)
 * @author Martina Chripkova (xchrip01)
 */


#include "population.h"

Population::Population() {
    this->population_filename = "population.csv";
    this->measures_filename = "measures.csv";
    this->load_population_data();
    this->load_measures_data();
}

Population::Population(std::string population_filename, std::string measures_filename) {
    this->population_filename = population_filename;
    this->measures_filename = measures_filename;
    this->load_population_data();
    this->load_measures_data();
}

void Population::load_population_data() {
    std::ifstream myFile(this->population_filename); // Create an input filestream
    if(!myFile.is_open()) throw std::runtime_error("Could not open file"); // Make sure the file is open

    std::string line;

    std::getline(myFile, line); // Extract the first line (population size) in the file
    this->size = std::stoi(line);

    // Read data, line by line
    while (std::getline(myFile, line)) {
        std::vector<std::string> values = split(line, ';');
        std::vector<int>::size_type sz = values.size();

        std::string name = values[0]; // population class name
        double perc_size = stod(values[1]); // population class size in %
        std::map<std::string, double> affecting_measures;
        for (unsigned i=2; i < sz; i++) {
            std::vector<std::string> measure = split(values[i], ':');
            affecting_measures[measure[0]] = stod(measure[1]);
        }

        this->populationClassesMap[name] = new PopulationClass(name, perc_size, affecting_measures);
    }

    myFile.close(); // Close file
}

void Population::load_measures_data() {
    std::ifstream myFile(this->measures_filename); // Create an input filestream
    if(!myFile.is_open()) throw std::runtime_error("Could not open file"); // Make sure the file is open

    std::string line;

    // Read data, line by line
    while (std::getline(myFile, line)) {
        std::vector<std::string> values = split(line, ';');

        std::string name = values[0]; // population class name
        int contacts_normal = std::stoi(values[1]);
        int contacts_active = std::stoi(values[2]);

        this->measuresMap[name] = new Measure(name, contacts_normal, contacts_active);
    }

    myFile.close(); // Close file
}

PopulationClass::PopulationClass(std::string name, double perc_size, std::map<std::string, double> affecting_measures) {
    this->name = name;
    this->perc_size = perc_size;
    this->affecting_measures = affecting_measures;
}

std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> result;
    std::stringstream ss (s);
    std::string item;

    while (getline (ss, item, delim)) {
        result.push_back (item);
    }

    return result;
}