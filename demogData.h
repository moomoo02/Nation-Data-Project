#ifndef DEMOG_H
#define DEMOG_H

#include <string>
#include<iostream>
#include <cmath>
#include <memory>
#include "raceDemogData.h"
#include "regionData.h"
using namespace std;

/*
  class to represent county demographic data
  from CORGIS
*/
class demogData : public regionData {
  public:
    demogData(string inN, string inS, double in65, double in18,double in5, int totPop14) :
            name(inN), state(inS), popOver65(in65), popUnder18(in18),
            popUnder5(in5), totalPopulation2014(totPop14), popUndergrad(0), popHighSchool(0),
            popOver65Count(in65/100.0 * totalPopulation2014),popUnder18Count(in18/100.0* totalPopulation2014),
            popUnder5Count(in5/100.0 * totalPopulation2014),BAupCount(0), 
            HSupCount(0),popUnderPov(0),popUnderPovCount(0),rDD(),regionData{inN,inS,totPop14} {}
  
    demogData(string inN, string inS, double in65, double in18, double in5, double u, double h, int totPop14) :
            name(inN), state(inS), popOver65(in65), popUnder18(in18),
            popUnder5(in5), popUndergrad(u), popHighSchool(h),totalPopulation2014(totPop14),
            popOver65Count(in65/100.0 * totalPopulation2014),popUnder18Count(in18/100.0* totalPopulation2014),
            popUnder5Count(in5/100.0* totalPopulation2014),BAupCount(u/100.0* totalPopulation2014), 
            HSupCount(h/100.0* totalPopulation2014), popUnderPov(0),popUnderPovCount(0),rDD(),regionData{inN,inS,totPop14}  {}
    demogData(string inN, string inS, double in65, double in18, double in5, double u, double h, int totPop14, double pup,raceDemogData rdd) :
            name(inN), state(inS), popOver65(in65), popUnder18(in18),
            popUnder5(in5), popUndergrad(u), popHighSchool(h),totalPopulation2014(totPop14),
            popOver65Count(in65/100.0 * totalPopulation2014),popUnder18Count(in18/100.0* totalPopulation2014),
            popUnder5Count(in5/100.0* totalPopulation2014),BAupCount(u/100.0* totalPopulation2014), 
            HSupCount(h/100.0* totalPopulation2014), popUnderPov(pup), popUnderPovCount(round(pup/100.0* totalPopulation2014)),rDD(rdd),regionData{inN,inS,totPop14}  {} 
    demogData(string inN, string inS, double in65, double in18, double in5, double u, double h, int totPop14, int pup,raceDemogData rdd) :
            name(inN), state(inS), popOver65(in65), popUnder18(in18),
            popUnder5(in5), popUndergrad(u), popHighSchool(h),totalPopulation2014(totPop14),
            popOver65Count(in65/100.0 * totalPopulation2014),popUnder18Count(in18/100.0* totalPopulation2014),
            popUnder5Count(in5/100.0* totalPopulation2014),BAupCount(u/100.0* totalPopulation2014), 
            HSupCount(h/100.0* totalPopulation2014), popUnderPov(100.0f*((double)(pup))/totPop14), popUnderPovCount(pup),rDD(rdd),regionData{inN,inS,totPop14}  {}
demogData(string inN, string inS, double in65, double in18, double in5, int u, double h, int totPop14, int pup,raceDemogData rdd) :
            name(inN), state(inS), popOver65(in65), popUnder18(in18),
            popUnder5(in5), popUndergrad(100.0f*(double)u/totalPopulation2014), popHighSchool(h),totalPopulation2014(totPop14),
            popOver65Count(in65/100.0 * totalPopulation2014),popUnder18Count(in18/100.0* totalPopulation2014),
            popUnder5Count(in5/100.0* totalPopulation2014),BAupCount(u), 
            HSupCount(h/100.0* totalPopulation2014), popUnderPov(100.0f*((double)(pup))/totPop14), popUnderPovCount(pup),rDD(rdd),regionData{inN,inS,totPop14}  {}              
  
    //getters
        double getpopUnder18() const{return popUnder18;}
        double getpopUnder5() const{return popUnder5;}
        double getpopOver65() const{return popOver65;}
        double getBAup() const{ return 100.0f*((double)(BAupCount))/totalPopulation2014; }
        double getHSup() const{return popHighSchool;}
        int getPop() const{return totalPopulation2014;}
        int getpopOver65Count()const{return round((popOver65 * (double)(totalPopulation2014))/(double)100.0);}
        int getpopUnder18Count()const{return round((popUnder18 * (double)(totalPopulation2014))/(double)100.0);}
        int getpopUnder5Count()const{return round((popUnder5 * (double)(totalPopulation2014))/(double)100.0);}
        int getBAupCount()const{return BAupCount;}
        int getHSupCount()const{return round((popHighSchool * (double)(totalPopulation2014))/(double)100.0);}
        double getpopUnderPov()const{return 100.0f*((double)(popUnderPovCount))/totalPopulation2014;}
        int getpopUnderPovCount()const{return popUnderPovCount;}
        int getBelowPovertyCount()const {return popUnderPovCount;};
        double getBelowPoverty()const {return 100.0f*((double)(popUnderPovCount))/totalPopulation2014; }
    raceDemogData getRaceDemogData()const{ return rDD; }
    raceDemogData getCommunityRaceMix() const {return rDD;} //Just another getter function for raceDemog Data
    shared_ptr<demogData> getPtr() { return static_pointer_cast<demogData>(shared_from_this()); }
    //Setters
    const void setDemogData(int pop, int pop65, int pop18, int pop5, int ba, int hs, int pov, raceDemogData rdd) {
        popOver65 = (double)pop65 * 100.0 / (double)pop;
        popUnder18 = (double)pop18 * 100.0 / (double)pop;
        popUnder5 = (double)pop5 * 100.0 / (double)pop;
        totalPopulation2014 = pop;
        popUndergrad = (double)ba * 100.0 / (double)pop;
        popHighSchool = (double)hs * 100.0 / (double)pop;
        popOver65Count = pop65;
        popUnder18Count = pop18;
        popUnder5Count = pop5;
        BAupCount = ba;
        HSupCount = hs;
        popUnderPov = (double)pov * 100.0 / (double)pop;
        popUnderPovCount = pov;
        rDD = rdd;
    }
    const
   friend std::ostream& operator<<(std::ostream &out, const demogData &DD);
   void toString(ostream& os) const override {
        // os << "County Demographics Info: " << name << ", " << state;
        // os << " total population: " << totalPopulation2014;
        // //consider re-writing with getters....
        // os << "\nPopulation info: \n(\% over 65): " << popOver65;
        // os << "% and total: " << popOver65Count;
        // os << "\n(\% under 18): " << popUnder18; 
        // os << "% and total: " << popUnder18Count;
        // os << "\n(\% under 5): " << popUnder5;
        // os <<  "% and total: " <<  popUnder5Count;
        // os << "\nEducation info: ";
        // os << "\n(\% Bachelor degree or more): " << popUndergrad;
        // os <<  "% and total: " <<  BAupCount;
        // os << "\n(\% high school or more): " << popHighSchool;
        // os <<  "% and total: " <<  HSupCount;
        // os << "\npersons below poverty: " << popUnderPov;
        // os << "% and total: " << popUnderPovCount;
        // os << rDD;
        os << "Region info: " << name << ", " << state;
        os << "\nEducation info: ";
        os << "\n(\% Bachelor degree or more): " << popUndergrad;
        os <<  "% and total: " <<  BAupCount;
        os << "\n(\% high school or more): " << popHighSchool;
        os << " total population: " << totalPopulation2014;
        os << rDD;
   };


    void accept(class Visitor &v) override;
private:
    const string name;
    const string state;
    double popOver65;
    double popUnder18;
    double popUnder5;
    int totalPopulation2014; 
    double popUndergrad;
    double popHighSchool;
    int popOver65Count;
    int popUnder18Count;
    int popUnder5Count;
    int BAupCount;
    int HSupCount;
    double popUnderPov;
    int popUnderPovCount;
    raceDemogData rDD;
};
#endif
