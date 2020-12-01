/**
 * IMS project - Epidemiological model in macro scale
 *
 * @file measures.cpp
 *
 * @author Natália Holkova (xholko02)
 * @author Martina Chripkova (xchrip01)
 */

#include "measures.h"

Measure::Measure(std::string name, int contacts_normal, int contacts_active) {
    this->name = name;
    this->contacts_normal = contacts_normal;
    this->contacts_active = contacts_active;
}
