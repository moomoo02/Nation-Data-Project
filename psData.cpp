#include <sstream>
#include "psData.h"
#include "visitor.h"
/* print police data - fill in*/
std::ostream& operator<<(std::ostream &out, const psData &PD) {
    out << "Police Shotting Info: " << PD.state;
    out << "\nPerson name: " << PD.name;
    out << "\nAge: " << PD.age;
    out << "\nGender: " << PD.gender;
    out << "\nRace:" << PD.race;
    out << "\nMental Illness:" << PD.signOfMentalIllness;
    out << "\nFleeing:" << PD.flee;
    return out;
}
void psData::accept(class Visitor &v){
    shared_ptr<psData> ps = getPtr();
    v.visit(ps);
}
