/**
 * IMS project - Epidemiological model in macro scale
 *
 * @file data.cpp
 *
 * @author Natália Holkova (xholko02)
 * @author Martina Chripkova (xchrip01)
 */

#include "data.h"

/**
 * Create Data object with default values for Slovakia
 */
Data::Data() {
    // Use default data for Slovakia - calculated beforehand
    this->size = 5457873;
    this->measuresMap["bohosluzby_zakaz"] = 0.1147147511;
    this->measuresMap["svadby_obrad"] = 0.0369882462;
    this->measuresMap["pohreby_rodina"] = 0.00245849672;
    this->measuresMap["obchody_zakladne"] = 0.1205198201;
    this->measuresMap["obchody_centra_zatvorene"] = 0.2709192562;
    this->measuresMap["detske_ihriska"] = 0.02125702324;
    this->measuresMap["skolky_1_stupen_ZS"] = 0.08389847476;
    this->measuresMap["2_stupen_ZS"] = 0.04934454367;
    this->measuresMap["stredne_skoly"] = 0.08912619128;
    this->measuresMap["vysoke_skoly"] = 0.02460851919;
    this->measuresMap["internaty_zatvorene"] = 0.04746532298;
    this->measuresMap["hromadne_podujatia_zakaz"] = 0;
    this->measuresMap["kina_zatvorene"] = 0;
    this->measuresMap["divadla_zatvorene"] = 0.003328146411;
    this->measuresMap["posilnovne_zatvorene"] = 0;
    this->measuresMap["restauracie_kaviarne_6_osob"] = 0;

    // default infected and recovered (to date 29.11.2020)
    this->recovered = 816 + 64197;
    this->infected = 105733 - this->recovered;
}

/**
 * Set active counter covid measures
 * @param active String containing names of measures separated by ','
 */
void Data::set_active_measures(std::string active) {
    std::vector<std::string> values = split(active, ',');
    for(auto item: values)
        this->activeMeasures.push_back(item);
}

/**
 * Calculate exposure factor based on selected counter measures
 * @return double exposure factor
 */
double Data::calculate_exposure_factor() {
    double exposure_factor = 1.0;
    for (auto measure: this->activeMeasures) {
        exposure_factor -= this->measuresMap[measure];
    }
    return exposure_factor;
}

/**
 * Get number of infected people
 * @return number of infected
 */
int Data::get_infected() {
    return this->infected;
}

/**
 * Get number of recovered + dead people
 * @return number of recovered + dead
 */
int Data::get_recovered() {
    return this->recovered;
}

/**
 * Get total population of state
 * @return number of people in state
 */
double Data::get_total_population() {
    return this->size;
}

/**
 * Split string by delimeter (single character)
 * @param s string to split
 * @param delim delimeter character
 * @return Vector of strings
 */
std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> result;
    std::stringstream sstream (s);
    std::string item;

    while (getline (sstream, item, delim)) {
        result.push_back (item);
    }

    return result;
}