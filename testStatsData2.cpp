

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include "demogData.h"
#include "parse.h"
#include "regionData.h"
#include "visitorCombineState.h"
#include "visitorCombineCounty.h"
#include "stats.h"
#include "statTool.h"
#include "tddFuncs.h"

using namespace std;

int main() {

  cout << "Testing stats on Data - new tools" << endl;

  std::vector<shared_ptr<regionData>> pileOfData;

  //read police shooting data
  read_csv(pileOfData, "police_shootings_cleaned.csv", POLICE);
   
  //read in the demographic data
  read_csv(pileOfData, "county_demographics.csv", DEMOG); 
  
  visitorCombineCounty theCounties;
  //use visitor pattern to be able to aggregate
  statTool::createCountyData(pileOfData, theCounties);

  theCounties.printAllCombo(&demogData::getpopUnderPovCount, &psCombo::getNumberOfCases);

  vector<double> dataX;
  vector<double> dataY;

  statTool::gatherCountStats(&theCounties, dataX, dataY, &demogData::getpopUnderPovCount, &psCombo::getNumberOfCases);

  double mX = stats::computeMean(dataX); 
  double mY = stats::computeMean(dataY);  
  double cc = stats::computeCorCoeffSample(dataX, dataY);

  ASSERT_EQUALS(31010.874, mX);
  ASSERT_EQUALS(4.451,mY);
  ASSERT_EQUALS(0.872, cc);

  return 0;
}
