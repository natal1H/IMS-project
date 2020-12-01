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
    this->beta = 520.0/365.0; // TODO - tmp
    this->gamma = 1.0/7.0;
    //this->t = 0.0;
    this->S0 = 1.0-1e-6; // TODO - tmp
    this->I0 = 1e-6; // TODO - tmp
    //this->R0 = 0.0; // TODO - tmp
    this->max_t =  70;
}

void SIR::run_simulation() {
    double step;

    // set up initial conditions
    this->S=this->S0;
    this->I=this->I0;
    this->R=1-this->S-this->I;

    printf("beta=%g\ngamma=%g\nInitial S=%g\nInitial I=%g\nRuns until time %g\n\n",this->beta,this->gamma,S0,I0,this->max_t);

    step = 1.0; // step is single day

    printf("Using a time step of %g\n\n",step);

    // main iteration routine
    this->t=0;

    printf("t\tS\tI\tR\n");
    this->output_data();

    do {
        this->runge_kutta(step);
        this->t += step;

        this->output_data();

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
    this->dPop[0] = - this->beta * population[0] * population[1]; // dS/dt = -beta * S * I
    this->dPop[1] = this->beta * population[0] * population[1] - this->gamma * population[1]; // dI/dt = beta * S * I - gamma * I
    this->dPop[2] = this->gamma * population[1]; // dR/dt = gamma * I
}

void SIR::output_data() {
    printf("%g\t%g\t%g\t%g\n", this->t ,this->S, this->I, this->R);
}