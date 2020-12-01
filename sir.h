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

    class SIR {
        private:
            double growth_rate; // growth rate
            double recovery_rate; // recovery and death rate
            double exposure_factor; // Factor describing active countermeasures
            int t; // time
            double S0;
            double I0;
            double R0;
        public:
    };
#endif