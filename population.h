/**
 * IMS project - Epidemiological model in macro scale
 *
 * @file population.h
 *
 * @author Natália Holkova (xholko02)
 * @author Martina Chripkova (xchrip01)
 */


#ifndef  _POPULATION_H
    #define _POPULATION_H

    #include <string>
    #include <vector>
    #include <map>
    #include <fstream>
    #include <sstream>
    #include <iostream>

    #include "measures.h"

    class PopulationClass {
        private:
            double perc_size; // Size of class in % from total population
            std::string name; // population class name (e.g. "Working")
            std::map<std::string, double> affecting_measures;
        public:
            PopulationClass(std::string name, double perc_size, std::map<std::string, double> affecting_measures);
    };

    class Population {
        private:
            std::string population_filename; // .csv file with population data
            std::string measures_filename; // .csv file with measures data
            int size; // Total size of population
            std::map<std::string, PopulationClass*> populationClassesMap;
            std::map<std::string, Measure*> measuresMap;
        public:
            Population(); // using default filename
            Population(std::string population_filename, std::string measures_filename); // set data source
            void load_population_data();
            void load_measures_data();
    };

    std::vector<std::string> split(const std::string &s, char delim);

#endif