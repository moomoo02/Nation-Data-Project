#ifndef VCOMBOKP_H
#define VCOMBOKP_H

#include "psData.h"
#include "psCombo.h"
#include "demogData.h"
#include "demogCombo.h"
#include "visitorCombine.h"
#include <memory>


class visitorCombineKeyPS : public visitorCombine {
public:
    visitorCombineKeyPS(string (*psf)(shared_ptr<psData>), const std::map<string, string>& mp) {
      psFunc = psf;
      //probably want to assert the map is legit and store it
      assert(mp.size() > 0);
      mapPSToKey = mp;
   }

  //based on stored key
	void visit(shared_ptr<demogData> obj) {
       string county = obj->getRegionName();
        if(county.find(" County") != string::npos){
          county.erase(county.find(" County"),7);
        }
        county += obj->getState();
        string key = mapPSToKey[county];
        if(getComboDemog().count(key) == 0){
            auto DCptr = make_shared<demogCombo>(*obj);
            DCptr->setRegionName("comboData");
            allComboDemogData[key] = DCptr;
        }else{
          add(key,obj);
        }
  }
    
  //store based on function
  void visit(shared_ptr<psData> obj) {
       string county = obj->getRegionName();
        if(county.find(" County") != string::npos){
          county.erase(county.find(" County"),7);
        }
        county += obj->getState();
        string key = mapPSToKey[county];
        if(getComboPolice().count(key) == 0){
            auto PSptr = make_shared<psCombo>();
             PSptr->setRegionName("comboData");
            allComboPoliceData[key] = PSptr;
        }
        add(key,obj);
  }

  private:
    //the function pointers to the key functions
    string (*psFunc)(shared_ptr<psData>);
    std::map<string, string> mapPSToKey;
    //data to help region to key for mapping between the two dataTypes

};

#endif
