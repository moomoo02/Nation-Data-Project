// Vince Nguyen, Kevin Lu 
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "demogData.h"
#include "parse.h"
#include "regionData.h"
#include "visitorCombineState.h"
#include "visitorCombineCounty.h"
#include "visitorCombineKeyDemog.h"
#include "visitorCombineKeyPS.h"
#include "visitorCreateKey.h"
#include "stats.h"
#include "statTool.h"
using namespace std;


string makeKeyDemog(shared_ptr<demogData> theData) {

  string theKey = "Key";

  if (theData->getCommunityRaceMix().getBlackPercent() > 20) {
    theKey += "AfriAmerTwentyPer";
  } else if (theData->getCommunityRaceMix().getLatinxPercent() > 20) {
    theKey += "LatinxPerTwentyPer";
  } else if (theData->getCommunityRaceMix().getFirstNationPercent() > 20) {
    theKey += "FirstNationTwentyPer";
  } else if (theData->getCommunityRaceMix().getAsianPercent() > 20) {
    theKey += "AsianTwentyPer";
  } else {
    theKey += "Other";
  }

  return theKey;
}

string makeKeyPS(shared_ptr<psData> theData) {

  string theKey = "Key";
  if (theData->getRace() == "W") {
    theKey += "WhiteVictim";
  } else if (theData->getRace() == "A") {
    theKey += "AsianVictim";
  } else if (theData->getRace() == "H") {
    theKey += "HispanicVictim";
  } else if (theData->getRace() == "N") {
    theKey += "NativeAmericanVictim";
  } else if (theData->getRace() == "B") {
    theKey += "AfricanAmericanVictim";
  } else if (theData->getRace() == "O") {
    theKey += "OtherRace";
  } else {
    theKey += "RaceUnspecified";
  }
  return theKey;
}

int main() {
    std::vector<shared_ptr<regionData>> pileOfData;

    //read police shooting data
    read_csv(pileOfData, "police_shootings_cleaned.csv", POLICE);
   
    //read in the demographic data
    read_csv(pileOfData, "county_demographics.csv", DEMOG); 
    //create a visitor to combine the state data
    auto theStates = make_shared<visitorCombineState>();
    //create the state demographic data
    statTool::createStateData(pileOfData, *theStates);

    //create a visitor to combine the county data (need aux map city-> county)
    auto theCounties = make_shared<visitorCombineCounty>();
    statTool::createCountyData(pileOfData, *theCounties);



    visitorCreateKey theKeys(&makeKeyDemog, &makeKeyPS);
    statTool::createKeys(pileOfData, theKeys);

    visitorCombineKeyDemog theKeyedDemog(&makeKeyDemog, theKeys.getDemogRegionToKey());
    statTool::createKeyedDataDemog(pileOfData, theKeyedDemog);
    theKeyedDemog.printAllCombo();

    visitorCombineKeyPS theKeyedPS(&makeKeyPS, theKeys.getPsRegionToKey());
    statTool::createKeyedDataPS(pileOfData, theKeyedPS);
    theKeyedPS.printAllCombo();
    return 0;
}

