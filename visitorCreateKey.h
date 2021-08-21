#ifndef VCOMBOK_H
#define VCOMBOK_H

#include "psData.h"
#include "psCombo.h"
#include "demogData.h"
#include "demogCombo.h"
#include "visitorCombine.h"
#include <memory>


class visitorCreateKey : public Visitor {
public:
  visitorCreateKey(string (*df)(shared_ptr<demogData>), string (*psf)(shared_ptr<psData>)) {
      demogFunc = df;
      psFunc =psf; 
   }
  void visit(shared_ptr<demogData> obj){
    string key = (*demogFunc)(obj);
    string county = obj->getRegionName();
    if(county.find(" County") != string::npos){
        county.erase(county.find(" County"),7);
    }
    county += obj->getState();
    demogRegionToKey[county] = key;
  }
  
  void visit(shared_ptr<psData> obj){
    string key = (*psFunc)(obj);
    string county = obj->getRegionName();
    if(county.find(" County") != string::npos){
        county.erase(county.find(" County"),7);
    }
    county += obj->getState();
    psRegionToKey[county] = key;
  }
  
	void visit(demogData* obj) {
  }
  void visit(psData* obj) {}
  void visit(psCombo * pc){}
  //add getters as needed
  const map<string,string> getDemogRegionToKey() { return demogRegionToKey; }
  const map<string,string> getPsRegionToKey() { return psRegionToKey; }
    private:
      //the function pointers to the key functions
      string (*demogFunc)(shared_ptr<demogData>);
      string (*psFunc)(shared_ptr<psData>);

      //ADD data to map between location and key
      map<string,string> demogRegionToKey;
      map<string,string> psRegionToKey;
};

#endif
