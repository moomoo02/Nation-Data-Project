#include "demogData.h"
#include "visitor.h"
#include <sstream>
#include <string>
#include <assert.h>
#include <iomanip>


/* print county demographic data */
const std::ostream& operator<<(std::ostream &os, const demogData &DD) {
    // out << std::setprecision(2) << std::fixed;
    // out << "County Demographics Info: " << DD.getRegionName() << ", " << DD.getState();
    // out << " total population: " << DD.getPop();
    // //consider re-writing with getters....
    // out << "\nPopulation info: \n(\% over 65): " << DD.getpopOver65();
    // out << "% and total: " << DD.getpopOver65Count();
    // out << "\n(\% under 18): " << DD.getpopUnder18(); 
    // out << "% and total: " << DD.getpopUnder18Count();
    // out << "\n(\% under 5): " << DD.getpopUnder5();
    // out <<  "% and total: " <<  DD.getpopUnder5Count();
    // out << "\nEducation info: ";
    // out << "\n(\% Bachelor degree or more): " << DD.getBAup();
    // out <<  "% and total: " <<  DD.getBAupCount();
    // out << "\n(\% high school or more): " << DD.getHSup();
    // out <<  "% and total: " <<  DD.getHSupCount();
    // out << "\npersons below poverty: " << DD.getpopUnderPov();
    // out << "% and total: " << DD.getpopUnderPovCount();
    // out << DD.getRaceDemogData();
        os << std::setprecision(2) << std::fixed;
        os << "Region info: " << DD.name << ", " << DD.state;
        os << "\nEducation info:";
        os << "\n(Bachelor or more): " << DD.popUndergrad;
        os <<  "% and total: " <<  DD.BAupCount;
        os << "\n(high school or more): " << DD.popHighSchool;
        os <<  "% and total: " <<  DD.HSupCount;
        os << "\nTotal population: " << DD.totalPopulation2014 << '\n';
        os << DD.rDD << '\n';
    return os;
}
void demogData::accept(class Visitor &v){
    // cout << "Accepted\n";
    shared_ptr<demogData> d = getPtr();
    v.visit(d);
}