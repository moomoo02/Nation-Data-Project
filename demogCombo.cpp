#include "demogCombo.h"
#include "demogData.h"
#include <sstream>
#include <string>
#include <assert.h>
#include <iomanip>

//add member functions here

/* print state data - as aggregate of all the county data */
std::ostream& operator<<(std::ostream &out, const demogCombo &SD) {
    out << std::fixed;
    std::cout.precision(2);
    if(SD.getSetSize() > 1){
        out << "Combo Info: ";
        out << SD.printState(); 
    }else{
        out << "State Info: " << SD.getState();
    }
    out << "\nNumber of Counties: " << SD.getCounties();
    out <<  " County Demographics Info: " << SD.getRegionName() << ", " << SD.getState();
    out << "\nPopulation info: \n(over 65): " << SD.getpopOver65();
    out << "% and total: " << SD.getpopOver65Count();
    out << "\n(under 18): " << SD.getpopUnder18(); 
    out << "% and total: " << SD.getpopUnder18Count();
    out << "\n(under 5): " << SD.getpopUnder5();
    out <<  "% and total: " <<  SD.getpopUnder5Count();
    out << "\nEducation info: ";
    out << "\n(Bachelor or more): " << SD.getBAup();
    out <<  "% and total: " <<  SD.getBAupCount();
    out << "\n(high school or more): " << SD.getHSup();
    out <<  "% and total: " <<  SD.getHSupCount();
    out << "\npersons below poverty: " << SD.getpopUnderPov();
    out << "% and total: " << SD.getpopUnderPovCount();
    out << "\nTotal population: " << SD.getPop();
    out << "\n" << SD.getRaceDemogData();
    //whyyyww
    return out;
}
