/**
 * IMS project - Epidemiological model in macro scale
 *
 * @file measures.h
 *
 * @author Natália Holkova (xholko02)
 * @author Martina Chripkova (xchrip01)
 */


#ifndef  _MEASURES_H
    #define _MEASURES_H

    #include <string>

    class Measure {
        private:
            std::string name;
            int contacts_normal; // number of social contacts in normal state (measure not active)
            int contacts_active; // number of social contacts when measure is active
        public:
    };
#endif