#ifndef POLICECOMBODATA_H
#define POLICECOMBODATA_H

#include "regionData.h"
#include "raceDemogData.h"
#include "psData.h"
#include <memory>
#include <cassert>
#include <iomanip>
using namespace std;
class psData;
class psCombo : public regionData  {
public:
    psCombo(string inS,int mc, int fc, int co65, int co18, int nm, int fm, int nc) : state(inS), 
    numMentalI(mc), fleeingCount(fc), casesOver65(co65), casesUnder18(co18), 
    numMales(nm), numFemales(fm), numberOfCases(nc), racialData(), regionData{inS} {} //add
    psCombo(string inS,int mc, int fc, int co65, int co18, int nm, int fm, int nc, raceDemogData rdd) : state(inS), 
    numMentalI(mc), fleeingCount(fc), casesOver65(co65), casesUnder18(co18), 
    numMales(nm), numFemales(fm), numberOfCases(nc),racialData(rdd), regionData{inS} {} //add
    psCombo() : state(""), numMentalI(0), fleeingCount(0), casesOver65(0), casesUnder18(0), 
    numMales(0), numFemales(0), numberOfCases(0),racialData(), regionData{} {} //add
    //complete these
    int getNumMentalI() const {return numMentalI;}
    int getFleeingCount() const {return fleeingCount;}
    int getCasesOver65() const {return casesOver65;}
    int getCasesUnder18() const {return casesUnder18;}
    raceDemogData getRacialData() const{ return racialData; };
    int getnumMales() const {return numMales;}
    int getnumFemales() const {return numFemales;}
    int getNumberOfCases() const {return numberOfCases;}
    const string getState() const {return state; } 

    friend std::ostream& operator<<(std::ostream &out, const psCombo& PD);
    void toString(ostream& out) const override {
        out << "State Info: " << state;
        out << "\nNumber of incidents: " << numberOfCases;
        out << std::setprecision(2) << std::fixed;
        out << "\nIncidents with age \n(over 65): " << casesOver65;
        out << "\n(19 to 64): " << numberOfCases - casesOver65 - casesUnder18;
        out << "\n(under 18): " << casesUnder18;
        out << "\nIncidents involving fleeing: "<< fleeingCount;
        out << "\nIncidents involving mental illness: " << numMentalI;
        out << "\nMale incidents: " <<  numMales << " female incidents: " << numFemales;
        out << "\nRacial demographics of state incidents: " << racialData;
   }
   //Adds data used for aggregating by key
    void add(psData& pd,string key){
        this->numMentalI += (pd.getSignOfMentalIllness() == "True");
        this->fleeingCount += (pd.getFlee() == "Foot" || pd.getFlee() == "Car" || pd.getFlee() == "Other");
        this->casesOver65 += (pd.getAge() >= 65);
        this->casesUnder18 += (pd.getAge() <= 18);
        this->numMales += (pd.getGender() == "M");
        this->numFemales += (pd.getGender() == "F");
        this->numberOfCases += 1;
        int WhiteNH = 0,White = 0, Black = 0, Asian = 0, FirstNation = 0, Latinx = 0, other = 0;
        if(key == "KeyWhiteVictim"){
            WhiteNH++;
            White++;
        }
        if(key == "KeyAsianVictim")Asian++;
        if(key == "KeyHispanicVictim")Latinx++;
        if(key == "KeyNativeAmericanVictim")FirstNation++;
        if(key == "KeyAfricanAmericanVictim")Black++;
        if(key == "KeyOtherRaceVictim") other++;
        shared_ptr<raceDemogData> rdd = make_shared<raceDemogData>(FirstNation,Asian,Black,Latinx,
        0,0,White,WhiteNH,1,other);
        this->racialData += *rdd;
        this->addState(pd.getState());
    }
    //Adds data used for aggregating by state
    void add(psData& pd){
        this->numMentalI += (pd.getSignOfMentalIllness() == "True");
        this->fleeingCount += (pd.getFlee() == "Foot" || pd.getFlee() == "Car" || pd.getFlee() == "Other");
        this->casesOver65 += (pd.getAge() >= 65);
        this->casesUnder18 += (pd.getAge() <= 18);
        this->numMales += (pd.getGender() == "M");
        this->numFemales += (pd.getGender() == "F");
        this->numberOfCases += 1;
        int WhiteNH = 0,White = 0, Black = 0, Asian = 0, FirstNation = 0, Latinx = 0, other = 0;
        if(pd.getRace() != "" && pd.getRace() != ")"){
            string r = pd.getRace();
            if(r == "W"){
                WhiteNH++;
                White++;
            }else if(r == "B"){
                Black++;
            }else if(r == "A"){
                Asian++;
            }else if(r == "N"){
                FirstNation++;
            }else if(r == "H"){
                Latinx++;
            }else{
                other++;
            }
        }
        shared_ptr<raceDemogData> rdd = make_shared<raceDemogData>(FirstNation,Asian,Black,Latinx,
        0,0,White,WhiteNH,1,other);
        this->racialData += *rdd;
        this->addState(pd.getState());
    }

    

    void accept(class Visitor &v) override;
protected:
    const string state;
    int numMentalI;
    int fleeingCount;
    int casesOver65;
    int casesUnder18;
    int numMales;
    int numFemales;
    int numberOfCases;
    raceDemogData racialData;
    //fill in
};

#endif