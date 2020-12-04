/**
 * IMS project - Epidemiological model in macro scale
 *
 * @file discreteSIR.cpp
 *
 * @author Natália Holkova (xholko02)
 * @author Martina Chripkova (xchrip01)
 */

#include "discreteSIR.h"

/**
 * Create object with default
 */
SIR::SIR() {
    this->beta = 0.05634007047; // calculated beforehand
    this->gamma = 0.05524861878; // calculated beforehand
    this->max_t =  30; // days
}

/**
 * Set initial values N, S0, I0, R0, exposure_factor for simulation
 * @param data Object from where values are taken
 */
void SIR::set_initial_data(Data *data) {
    this->N = data->get_total_population();
    this->I0 = data->get_infected() / this->N;
    this->R0 = data->get_recovered() / this->N;
    this->S0 = 1 - this->I0 - this->R0;
    this->exposure_factor = data->calculate_exposure_factor();
}

/**
 * Prints initial values S0, I0, R0 and parameters beta, gamma, exposure_factor
 */
void SIR::print_initial_data() {
    std::cout << "SIR model initial data:" << std::endl;
    std::cout << "S0 = " << this->S0 << std::endl;
    std::cout << "I0 = " << this->I0 << std::endl;
    std::cout << "R0 = " << this->R0 << std::endl;
    std::cout << "beta = " << this->beta << std::endl;
    std::cout << "gamma = " << this->gamma << std::endl;
    std::cout << "exposure_factor = " << this->exposure_factor << std::endl;
}

/**
 * Outputs current values S, I, R
 */
void SIR::output_data() {
    printf("%d\t%d\t%d\t%d|%f\t%f\t%f\n", this->t, (int)round(this->S * this->N), (int)round(this->I * this->N), (int)round(this->R * this->N),
           dS * N, dI * N, dR * N);
}

/**
 * Run the simulation
 */
void SIR::run_simulation() {
    // set up initial conditions
    double prevS = this->S0;
    double prevI = this->I0;
    double prevR = this->R0;

    for (this->t = 1; this->t <= this->max_t; this->t++) {
        dS = -this->beta * exposure_factor * prevS * prevI;
        dI = this->beta * exposure_factor * prevS * prevI - this->gamma * prevI;
        dR = this->gamma * prevI;

        this->S = prevS + dS;
        this->I = prevI + dI;
        this->R = prevR + dR;
        output_data();

        prevS = this->S;
        prevI = this->I;
        prevR = this->R;
    }
}
