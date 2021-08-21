#ifndef REGION_H
#define REGION_H

#include <string>
#include <iostream>
#include <vector>
#include <set>
#include <memory>
using namespace std;

class Visitor;
  
/* very general data type for any kind of regional data*/
class regionData :  public enable_shared_from_this<regionData> {
  public:
    regionData(const string inN, const string inS, const int pop) : regionName(inN), population(pop) {
      stateS.insert(inS);
    }

    regionData(const string inN, const string inS) : 
    regionName(inN), population(0) {
      stateS.insert(inS);
    }

    regionData(const string inS) {
      stateS.insert(inS);
    }

    regionData() : regionName(""), population(0) {}
    string getRegionName() const { return regionName; }
    void setRegionName(string n)  { regionName = n; }
    virtual const string getState() const { if (stateS.size() == 1) return *(stateS.begin()); else return "many";  }
    int getSetSize() const { return stateS.size();}
    void addState(string inS) {stateS.insert(inS);}
    string printState() const { 
      string s;
      for (std::set<string>::iterator it=stateS.begin(); it != stateS.end(); it++) s+=*it+", "; 
      s+= "total states: " + std::to_string(stateS.size());
      return s;
    }
    void setName(string inN) {regionName = inN;}
    int getPop() const { return population; }
    void setPop(int inPop) { population = inPop; }
    virtual void toString(ostream& os) const = 0;
    friend std::ostream& operator<<(std::ostream &out, const regionData &RD){
      RD.toString(out);
      return out;
    }

    virtual void accept(class Visitor &v) = 0;

  protected:
  	string regionName; //city or county or place name
    //region data could be more than one state
    std::set<string> stateS; //all regions should have identifying state in US
  	int population; //region population
  	
};
#endif
