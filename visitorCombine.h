#ifndef VCOMBO_H
#define VCOMBO_H

#include "psData.h"
#include "psCombo.h"
#include "demogData.h"
#include "demogCombo.h"
#include "visitor.h"
#include <memory>
#include <map>

//The shared combo data
class visitorCombine : public Visitor {
public:
    visitorCombine() {}

    //hust a helper to print out various fields
    void printAllCombo(int (demogData::*f1)() const, int (psCombo::*f2)() const) {
        //stay tuned may be provided
    }
    void printAllCombo() {
        cout << "Combo Demographic Info: ";
        for (auto const& entry : allComboDemogData) {
            cout << "name: " << entry.first << endl;
            cout << *(entry.second) << "\n";
            if(allComboPoliceData.count(entry.first) != 0) cout << *(allComboPoliceData[entry.first]) << '\n';
        }

        for (auto const& entry : allComboPoliceData) {
            cout << "key: " << entry.first << endl;
            cout << *(entry.second) << "\n";
            if(allComboDemogData.count(entry.first) != 0) cout << *(allComboDemogData[entry.first]) << '\n';
        }   
    }

    shared_ptr<demogCombo> getComboDemogData(string regionName) { return allComboDemogData[regionName]; } //fill in
    shared_ptr<psCombo> getComboPoliceData(string regionName) { return allComboPoliceData[regionName]; } //fill in

	std::map<string, shared_ptr<demogCombo> >& getComboDemog()  { return allComboDemogData; } //fill in
    std::map<string, shared_ptr<psCombo> > & getComboPolice() { return allComboPoliceData; } //fill in

    //Add demogData to a demogCombo data
    void add(string key, shared_ptr<demogData> dd){
        *allComboDemogData[key] += *dd;
    }
    //Add police shooting data to a police combo data
    void add(string key, shared_ptr<psData> ps){
        allComboPoliceData[key]->add(*ps);
    }
    void visit(psData *ps){}
    void visit(demogData *dd){}
    void visit(psCombo * pc){}
    // std::ostream& operator<<(std::ostream &out) {
    //     out << "Combo Demographic Info: ";
    //     for (auto const& entry : allComboDemogData) {
    //         out << "key: " << entry.first << endl;
    //         out << *(entry.second) << "\n";
    //     }

    //     for (auto const& entry : allComboPoliceData) {
    //         out << "key: " << entry.first << endl;
    //         out << *(entry.second) << "\n";
    //     }

    //   return out;
    // }
    protected:
       std::map<string, shared_ptr<demogCombo> > allComboDemogData;
       std::map<string, shared_ptr<psCombo> > allComboPoliceData;
};

#endif
