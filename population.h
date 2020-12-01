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
    #include <fstream>
    #include <sstream>
    #include <iostream>

    #include "measures.h"

    class PopulationClass {
        private:
            double perc_size; // Size of class in % from total population
            std::string name; // population class name (e.g. "Working")
        public:
            PopulationClass(std::string name, double perc_size);
    };

    class Population {
        private:
            std::string filename; // .csv file with population data
            int size; // Total size of population
            std::vector<PopulationClass> populationClasses;
        public:
            Population(); // using default filename
            Population(std::string filename); // set data source
            void load_data();
    };

#endif