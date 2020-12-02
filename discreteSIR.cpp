/**
 * IMS project - Epidemiological model in macro scale
 *
 * @file discreteSIR.cpp
 *
 * @author Natália Holkova (xholko02)
 * @author Martina Chripkova (xchrip01)
 */

#include "discreteSIR.h"

SIR::SIR() {
    this->beta = 0.1;//0.01; // test value
    this->gamma = 0.04; // test value
    this->max_t =  30; // days
}

void SIR::set_initial_data(Data *data) {
    this->N = data->get_total_population();
    this->I0 = data->get_infected() / this->N;
    this->R0 = data->get_recovered() / this->N;
    this->S0 = 1 - this->I0 - this->R0;
    this->exposure_factor = data->calculate_exposure_factor();
}

void SIR::print_initial_data() {
    std::cout << "SIR model initial data:" << std::endl;
    std::cout << "S0 = " << this->S0 << std::endl;
    std::cout << "I0 = " << this->I0 << std::endl;
    std::cout << "R0 = " << this->R0 << std::endl;
    std::cout << "exposure_factor = " << this->exposure_factor << std::endl;
}

void SIR::output_data() {
    //std::cout << this->t;
    //std::cout << "\t" << this->S * this->N;
    //std::cout << "\t" << this->I * this->N;
    //std::cout << "\t" << this->R * this->N << std::endl;
    printf("%d\t%d\t%d\t%d|%f\t%f\t%f\n", this->t, (int)round(this->S * this->N), (int)round(this->I * this->N), (int)round(this->R * this->N),
           dS * N, dI * N, dR * N);
}

void SIR::run_simulation() {
    // set up initial conditions
    double prevS = this->S0;
    double prevI = this->I0;
    double prevR = this->R0;

    //double dS, dI, dR;
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
