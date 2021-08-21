#ifndef VCOMBOC_H
#define VCOMBOC_H

#include "psData.h"
#include "psCombo.h"
#include "demogData.h"
#include "demogCombo.h"
#include "visitorCombine.h"
#include "parse.h"
#include <memory>
#include <fstream>
#include <cassert>

class visitorCombineCounty : public visitorCombine {
public:
    visitorCombineCounty() {
    }

    //store demographic data by county name
	void visit(shared_ptr<demogData> obj) {
        string county = obj->getRegionName();
        if(county.find(" County") != string::npos){
            county.erase(county.find(" County"),7);
        }
        county += obj->getState();
        //cout << "demogData: " << county << '\n';
        //if(getComboDemog().count(county) == 0){
            auto DCptr = make_shared<demogCombo>(*obj);
            DCptr->setRegionName(county);
            allComboDemogData[county] = DCptr;
        //}

    }
    
    //aggregate police shooting data by county
    void visit(shared_ptr<psData> obj) {
        string county = obj->getRegionName();
        if(county.find(" County") != string::npos){
            county.erase(county.find(" County"),7);
        }
        county += obj->getState();
        //cout << "psData: " << county << '\n';
        if(getComboPolice().count(county) == 0){
            auto PSptr = make_shared<psCombo>();
            PSptr->setRegionName(county);
            allComboPoliceData[county] = PSptr;
        }
        add(county,obj);
    }

    private:
        //only inherited data at this point
};

#endif
