/**
 * IMS project - Epidemiological model in macro scale
 *
 * @file main.cpp
 *
 * @author Natália Holkova (xholko02)
 * @author Martina Chripkova (xchrip01)
 */

#include "main.h"

int main(int argc, char *argv[]) {
    Data data;
    //data.set_active_measures("vysoke_skoly,stredne_skoly,2_stupen_ZS");
    data.set_active_measures("");
    data.calculate_exposure_factor();
    SIR sir;
    sir.set_initial_data(&data);
    sir.print_initial_data();
    sir.run_simulation();
}