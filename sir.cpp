/**
 * IMS project - Epidemiological model in macro scale
 *
 * @file sir.cpp
 *
 * @author Natália Holkova (xholko02)
 * @author Martina Chripkova (xchrip01)
 */

#include "sir.h"

SIR::SIR() {
    //this->beta = 520.0/365.0; // TODO - tmp
    //this->gamma = 1.0/7.0;
    this->beta = 6.7e-7;
    this->gamma = 0.04;

    this->max_t =  60; // 60 days
}

void SIR::run_simulation() {
    double step, every;

    // set up initial conditions
    this->S=this->S0;
    this->I=this->I0;
    this->R=1-this->S-this->I;

    printf("beta=%g\ngamma=%g\nInitial S=%g\nInitial I=%g\nRuns until time %g\n\n",this->beta,this->gamma,S0,I0,this->max_t);

    //step = 1.0; // step is single day
    step = 0.01 / ((this->beta + this->gamma) * this->S0);

    every = pow(10,floor(log10((1.0/((this->beta + this->gamma) * this->S0)))));
    while(this->max_t / every > 10000) {
        every *= 10.0;
    }
    //every = 1.0;
    printf("Using a time step of %g and outputing data every %g\n\n", step, every);


    printf("Using a time step of %g\n\n",step);

    // main iteration routine
    this->t=0;

    printf("t\tS\tI\tR\n");
    this->output_data();

    do {
        this->runge_kutta(step);
        this->t += step;

        if( floor(this->t / every) > floor((this->t - step) / every)) {
            this->output_data();
        }

    }
    while(this->t < this->max_t);


    this->output_data();
}

void SIR::runge_kutta(double step) {
    double dPop1[3], dPop2[3], dPop3[3], dPop4[3];
    double tmpPop[3], initPop[3];

    initPop[0]=this->S; initPop[1]=this->I; initPop[2]=this->R;

    this->diff(initPop);
    for(int i=0 ; i < 3; i++) {
        dPop1[i] = this->dPop[i];
        tmpPop[i] = initPop[i] + step * dPop1[i] / 2;
    }

    this->diff(tmpPop);
    for(int i = 0; i < 3; i++) {
        dPop2[i]= this->dPop[i];
        tmpPop[i] = initPop[i] + step * dPop2[i] / 2;
    }

    this->diff(tmpPop);
    for(int i = 0; i < 3; i++) {
        dPop3[i] = this->dPop[i];
        tmpPop[i] = initPop[i] + step * dPop3[i];
    }

    this->diff(tmpPop);
    for(int i = 0; i < 3; i++) {
        dPop4[i]= this->dPop[i];
        tmpPop[i]= initPop[i] + (dPop1[i] / 6 + dPop2[i] / 3 + dPop3[i] / 3 + dPop4[i] / 6) * step;
    }

    this->S=tmpPop[0];
    this->I=tmpPop[1];
    this->R=tmpPop[2];
}

void SIR::diff(double population[3]) {
    this->dPop[0] = - this->beta * this->exposure_factor * population[0] * population[1]; // dS/dt = -beta * exposure_factor * S * I
    this->dPop[1] = this->beta * this->exposure_factor * population[0] * population[1] - this->gamma * population[1]; // dI/dt = beta * exposure_factor * S * I - gamma * I
    this->dPop[2] = this->gamma * population[1]; // dR/dt = gamma * I
}

void SIR::output_data() {
    printf("%g\t%g\t%g\t%g\n", this->t ,this->S, this->I, this->R);
}

void SIR::set_initial_data(Data *data) {
    this->I0 = data->get_infected() / data->get_total_population();
    this->R0 = data->get_recovered() / data->get_total_population();
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