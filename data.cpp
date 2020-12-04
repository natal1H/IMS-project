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
    size = 5457873;
    measuresMap["bohosluzby_zakaz"] = 0.1147147511;
    measuresMap["svadby_obrad"] = 0.0369882462;
    measuresMap["pohreby_rodina"] = 0.00245849672;
    measuresMap["obchody_zakladne"] = 0.1205198201;
    measuresMap["obchody_centra_zatvorene"] = 0.2709192562;
    measuresMap["detske_ihriska"] = 0.02125702324;
    measuresMap["skolky_1_stupen_ZS"] = 0.08389847476;
    measuresMap["2_stupen_ZS"] = 0.04934454367;
    measuresMap["stredne_skoly"] = 0.08912619128;
    measuresMap["vysoke_skoly"] = 0.02460851919;
    measuresMap["internaty_zatvorene"] = 0.04746532298;
    measuresMap["hromadne_podujatia_zakaz"] = 0;
    measuresMap["kina_zatvorene"] = 0;
    measuresMap["divadla_zatvorene"] = 0.003328146411;
    measuresMap["posilnovne_zatvorene"] = 0;
    measuresMap["restauracie_kaviarne_6_osob"] = 0;

    // default infected and recovered (to date 29.11.2020)
    recovered = 816 + 64197;
    infected = 105733 - recovered;
}

/**
 * Set active counter covid measures
 * @param active String containing names of measures separated by ','
 */
void Data::set_active_measures(std::string active) {
    std::vector<std::string> values = split(active, ',');
    for(auto item: values)
        activeMeasures.push_back(item);
}

/**
 * Calculate exposure factor based on selected counter measures
 * @return double exposure factor
 */
double Data::calculate_exposure_factor() {
    double exposure_factor = 1.0;
    for (auto measure: activeMeasures) {
        exposure_factor -= measuresMap[measure];
    }
    return exposure_factor;
}

/**
 * Get number of infected people
 * @return number of infected
 */
int Data::get_infected() {
    return infected;
}

/**
 * Get number of recovered + dead people
 * @return number of recovered + dead
 */
int Data::get_recovered() {
    return recovered;
}

/**
 * Get total population of state
 * @return number of people in state
 */
double Data::get_total_population() {
    return size;
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