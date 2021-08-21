#ifndef VCOMBOS_H
#define VCOMBOS_H


#include "visitorCombine.h"
#include <memory>

class visitorCombineState : public visitorCombine {
public:
    visitorCombineState() {}

	void visit(shared_ptr<demogData> obj) {
        // cout << "Adding " << obj->getRegionName() << "...\n";
        string state = obj->getState();
        if(getComboDemog().count(state) == 0){
            auto DCptr = make_shared<demogCombo>(*obj);
            DCptr->setRegionName("comboData");
            allComboDemogData[state] = DCptr;
        }else{
            add(state,obj);
        }
    }
    
    void visit(shared_ptr<psData> obj) {
        string state = obj->getState();
        if(getComboPolice().count(state) == 0){
            auto PSptr = make_shared<psCombo>();
            PSptr->setRegionName("comboData");
            allComboPoliceData[state] = PSptr;
        }
        add(state,obj);
    }

    private:
       //inherited
};

#endif
