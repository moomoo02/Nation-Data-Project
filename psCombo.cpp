#include <iomanip>
#include "psCombo.h"
#include "visitor.h"


/* print state data - as aggregate of all incidents in this state */
std::ostream& operator<<(std::ostream &out, const psCombo& PD) {
    out << "State Info: " << PD.printState();
    out << "\nNumber of incidents: " << PD.numberOfCases;
    out << std::setprecision(2) << std::fixed;
    out << "\nIncidents with age \n(over 65): " << PD.casesOver65 << " %: " << 100.0f*(double)(PD.casesOver65)/PD.numberOfCases;
    out << "\n(19 to 64): " << PD.numberOfCases - PD.casesOver65 - PD.casesUnder18 << " %: " << 100.0f*(double)(PD.numberOfCases - PD.casesOver65 - PD.casesUnder18)/PD.numberOfCases;
    out << "\n(under 18): " << PD.casesUnder18 << " %: " << 100.0f*(double)(PD.casesUnder18)/PD.numberOfCases;
    out << "\nIncidents involving fleeing: "<< PD.fleeingCount << " %: " << 100.0f*(double)(PD.fleeingCount)/PD.numberOfCases;
    out << "\nIncidents involving mental illness: " << PD.numMentalI << " %: " << 100.0f*(double)(PD.numMentalI)/PD.numberOfCases;
    out << "\nMale incidents: " <<  PD.numMales << " female incidents: " << PD.numFemales;
    out << "\nRacial demographics of state incidents: " << PD.racialData << '\n';
    return out;
}
void psCombo::accept(class Visitor &v){
    v.visit(this);
}