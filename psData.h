#ifndef POLICE_H
#define POLICE_H

#include <string>
#include <iostream>
#include <utility>
#include <ostream>
#include <memory>
#include "regionData.h"
using namespace std;

/*
  class to represent police shooting data
  from CORGIS
*/
class psData : public regionData {
  public:
    //add appropriate function paramaters to constructor once you add data
    psData(string inState,string n, int a, string g, string r, string c, string sml, string f) : state(inState), name(n), 
    age(a), gender(g), race(r), city(c), signOfMentalIllness(sml), flee(f), regionData{c,inState} {}

    string getName() const { return name; }
    int getAge() const { return age; }
    string getGender() const {return gender; }
    string getRace() const {return race; }
    string getCity() const {return city;}
    string getSignOfMentalIllness() const { return signOfMentalIllness; }
    string getFlee() const{return flee;}

    shared_ptr<psData> getPtr() { return static_pointer_cast<psData>(shared_from_this()); }
    
   friend std::ostream& operator<<(std::ostream &out, const psData &PD);
   void toString(ostream& os) const override {
    os << "Police Shotting Info: " << state;
    os << "\nPerson name: " << name;
    os << "\nAge: " << age;
    os << "\nGender: " << gender;
    os << "\nRace:" << race;
    os << "\nMental Illness:" << signOfMentalIllness;
    os << "\nFleeing:" << flee;
   };

  void accept(class Visitor &v) override;
private:
    const string state;
    const string name;
    const int age;
    const string gender;
    const string race;
    const string city;
    const string signOfMentalIllness;
    const string flee;
    //add others

};

#endif
