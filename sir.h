/**
 * IMS project - Epidemiological model in macro scale
 *
 * @file sir.h
 *
 * @author Natália Holkova (xholko02)
 * @author Martina Chripkova (xchrip01)
 */

#ifndef  _SIR_H
    #define _SIR_H

    #include <cmath>
    #include <cstdio> // TODO remove

    class SIR {
        private:
            double beta; // growth rate
            double gamma; // recovery and death rate
            double exposure_factor; // Factor describing active countermeasures
            double t; // time
            double S;
            double S0;
            double I;
            double I0;
            double R;
            double R0;
            double dPop[3];
            double pop[3];
            double max_t; // max time - in days
        public:
            SIR();
            void run_simulation();
            void output_data();
            void runge_kutta(double step);
            void diff(double population[3]);
    };
#endif