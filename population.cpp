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
    this->filename = "population.csv";
    this->load_data();
}

Population::Population(std::string filename) {
    this->filename = filename;
    this->load_data();
}

void Population::load_data() {
    std::ifstream myFile(this->filename); // Create an input filestream
    if(!myFile.is_open()) throw std::runtime_error("Could not open file"); // Make sure the file is open

    std::string line;

    std::getline(myFile, line); // Extract the first line (population size) in the file
    this->size = std::stoi(line);

    // Read data, line by line
    while (std::getline(myFile, line)) {
        auto start = 0U;
        auto end = line.find(";");

        std::string name = line.substr(start, end - start);
        double perc_size = stod(line.substr(end - start + 1));

        this->populationClasses.push_back(PopulationClass(name, perc_size));
    }

    myFile.close(); // Close file
}

PopulationClass::PopulationClass(std::string name, double perc_size) {
    this->name = name;
    this->perc_size = perc_size;
}