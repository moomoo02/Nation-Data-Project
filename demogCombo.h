#ifndef COMBODEMOG_H
#define COMBODEMOG_H

#include <memory>
#include <string>
#include <iostream>
#include "demogData.h"
#include "raceDemogData.h"

/*
  class to represent combined demographic data 
*/
class demogCombo : public demogData {
  public:
    //write demogCombo constructor
    demogCombo(string state, int pO65, int pU18, int pU5, int b, int hs, int pp, int tot,int c, raceDemogData rdd) :
            demogData{"comboData", state, (double)(pO65) * 100.0 / tot, (double)(pU18) * 100.0 / tot, (double)(pU5) * 100.0 / tot, (int)b, 
            (double)(hs) * 100.0 / tot, tot, pp,rdd}, counties(c) {}
    demogCombo(demogData dd) : demogData{dd}, counties(1) {}
    //fill in
  int getCounties() const {return counties; }

  demogCombo& operator+=(const demogData& dd){
    int pO65 = 0, pU18 = 0, pU5 = 0, b = 0, hs = 0, pp = 0, tot = 0;
    raceDemogData rdd = this->getRaceDemogData() + dd.getRaceDemogData();
    pO65 = this->getpopOver65Count() + dd.getpopOver65Count();
    pU18 = this->getpopUnder18Count() + dd.getpopUnder18Count();
    pU5 = this->getpopUnder5Count() + dd.getpopUnder5Count();
    b = this->getBAupCount() + dd.getBAupCount();
    hs = this->getHSupCount() + dd.getHSupCount();
    pp = this->getpopUnderPovCount() + dd.getpopUnderPovCount();
    tot = this->getPop() + dd.getPop();
    counties = this->getCounties() + 1;
    //cout << "AHHHHH  " << dd.getState() << '\n';
    //cout << "Adding..";
    this->addState(dd.getState());
    //cout << "Size is now: " << this->getSetSize() << '\n';
    this->setDemogData(tot,pO65,pU18,pU5,b,hs,pp,rdd);
    return *this;
  }
  friend std::ostream& operator<<(std::ostream &out, const demogCombo &SD);

private:
    //fill in
    int counties;
};
#endif
