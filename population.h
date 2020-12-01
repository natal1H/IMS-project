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

    #include "measures.h"

    class PopulationClass {
        private:
            double perc_size; // Size of class in % from total population
            std::string name; // population class name (e.g. "Working")
        public:

    };

    class Population {
        private:
            int size; // Total size of population
            std::vector<PopulationClass> populationClasses;
        public:
    };

#endif