#ifndef VCOMBOKD_H
#define VCOMBOKD_H

#include "psData.h"
#include "psCombo.h"
#include "demogData.h"
#include "demogCombo.h"
#include "visitorCombine.h"
#include <memory>


class visitorCombineKeyDemog : public visitorCombine {
public:
    visitorCombineKeyDemog(string (*df)(shared_ptr<demogData>), const std::map<string, string>& mp) {
      demogFunc = df;
      //probably want to assert the map is legit and store it
      assert(mp.size() > 0);
      mapDemogToKey = mp;
   }


  //just store based on function
	void visit(shared_ptr<demogData> obj) {
       string county = obj->getRegionName();
        if(county.find(" County") != string::npos){
          county.erase(county.find(" County"),7);
        }
        county += obj->getState();
        string key = mapDemogToKey[county];
        if(getComboDemog().count(key) == 0){
            auto DCptr = make_shared<demogCombo>(*obj);
            DCptr->setRegionName("comboData");
            allComboDemogData[key] = DCptr;
        }else{
            add(key,obj);
        }
    }
    
    //store based on demog key
    void visit(shared_ptr<psData> obj) {
        string county = obj->getRegionName();
        if(county.find(" County") != string::npos){
          county.erase(county.find(" County"),7);
        }
        county += obj->getState();
        string key = mapDemogToKey[county];
        if(getComboPolice().count(key) == 0){
            auto PSptr = make_shared<psCombo>();
            PSptr->setRegionName("comboData");
            allComboPoliceData[key] = PSptr;
        }
        add(key,obj);
    }

    private:
      //the function pointers to the key functions
      string (*demogFunc)(shared_ptr<demogData>);
      std::map<string, string> mapDemogToKey;
      //want a way to keep region to key for mapping between the two dataTypes

};

#endif
