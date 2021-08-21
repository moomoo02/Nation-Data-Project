#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <iomanip>
#include <math.h>
#include "demogData.h"
#include "demogCombo.h"
#include "psData.h"
#include "psCombo.h"
#include "parse.h"

#include "visitorReport.h"
#include "visitorCombineState.h"
#include "visitorCombineCounty.h"
#include "visitorCombineKeyDemog.h"
#include "visitorCombineKeyPS.h"
#include "visitorCreateKey.h"
#include "stats.h"
#include "statTool.h"

static void writeToCSV(vector<double> &x, vector<double> y, string file){
    // Create an input filestream
    std::ofstream myFile(file);

    // Make sure the file is open
    if(!myFile.is_open()) {
        throw std::runtime_error("Could not open file");
    }

    if(myFile.good()) {
        for (int i=0; i < x.size(); i++){
            myFile << x.at(i) << ", " << y.at(i) << endl;
        }
    }
     // Close file
    myFile.close();
}


/* statTool:: wrapper for some useful functions to report necessary data */
/* call visitor pattern to create state data */
void statTool::createStateData(std::vector<shared_ptr<regionData>>& theData, Visitor& theStates) {

   //use visitor pattern to be able to aggregate
    for (const auto &obj : theData) {
        obj->accept((visitorCombineState&)theStates);
    }
}

/* call visitor pattern to create county data */
void statTool::createCountyData(std::vector<shared_ptr<regionData>>& theData, Visitor& theCounties) {

   //use visitor pattern to be able to aggregate
    for (const auto &obj : theData) {
        obj->accept((visitorCombineCounty&)theCounties);
    }
}

/* call visitor pattern to create key data */
void statTool::createKeys(std::vector<shared_ptr<regionData>>& theData, Visitor& theKeys) {

   //use visitor pattern to be able to aggregate
    for (const auto &obj : theData) {
        obj->accept((visitorCreateKey&)theKeys);
    }
}

/* call visitor pattern to create keyed data based on keyes generated from deomgraphic criteria*/
void statTool::createKeyedDataDemog(std::vector<shared_ptr<regionData>>& theData, Visitor& theKeyed) {

   //use visitor pattern to be able to aggregate
    for (const auto &obj : theData) {
        obj->accept((visitorCombineKeyDemog&)theKeyed);
    }
}

/* call visitor pattern to create keyed data based on keyes generated from PS criteria*/
void statTool::createKeyedDataPS(std::vector<shared_ptr<regionData>>& theData, Visitor& theKeyed) {

   //use visitor pattern to be able to aggregate
    for (const auto &obj : theData) {
        obj->accept((visitorCombineKeyPS&)theKeyed);
    }
}

/* helper functions to fill in arrays based on funciton pointers  - on mix*/
void statTool::gatherCountStats(visitorCombine* theAggregate, vector<double> &XPer, vector<double> &YPer, 
                int (demogCombo::*f1)() const, int (psCombo::*f2)() const) {
    //for all demographic data
    for (auto entry : theAggregate->getComboDemog()) {
        //make sure there is valid police shooting data!
        shared_ptr<psCombo> temp = theAggregate->getComboPoliceData(entry.first);
        psCombo *thePSData = temp.get();
        if ( thePSData != NULL ) {
            double xP = (double) ((entry.second).get()->*f1)();
            double yP = (double) (thePSData->*f2)();
            if (!isnan(xP) && !isnan(yP)) {
                YPer.push_back(yP);
                XPer.push_back(xP);
            }
        }
    }
}

/* helper functions to fill in arrays based on funciton pointers  */

void statTool::gatherMixRaceProportionStats(visitorCombine* theAggregate, vector<double> &XPer, vector<double> &YPer, 
                int (raceDemogData::*f1)() const, int (raceDemogData::*f2)() const) {
    //for all  data
    for (auto entry : theAggregate->getComboDemog()) {
        //make sure there is valid police shooting data!
        shared_ptr<psCombo> temp = theAggregate->getComboPoliceData(entry.first);
        psCombo *thePSData = temp.get();
        if ( thePSData != NULL ) {
          double xP = (double) (((entry.second).get()->getCommunityRaceMix().*f1)())/(entry.second).get()->getPop();
          double yP = (double) ((thePSData->getRacialData().*f2)())/thePSData->getNumberOfCases();
          if (!isnan(xP) && !isnan(yP)) {
            YPer.push_back(yP);
            XPer.push_back(xP);
          }
      }
    }
}


/* helper functions to fill in arrays based on funciton pointers  - on police hsooting only*/
void statTool::gatherCountStats(visitorCombine* theAggregate, vector<double> &XPer, vector<double> &YPer, 
                int (psCombo::*f1)() const, int (psCombo::*f2)() const) {
    //for all demographic data
    for (auto entry : theAggregate->getComboPolice()) {
        psCombo *thePSData = entry.second.get();
        if ( thePSData != NULL ) {
          double xP = (thePSData->*f1)();
          double yP = (thePSData->*f2)();
          if (!isnan(xP) && !isnan(yP)) {
            YPer.push_back(yP);
            XPer.push_back(xP);
          }
      }
    }
}

/* helper functions to fill in arrays based on funciton pointers  - on demog percentages*/
void statTool::gatherPerStats(visitorCombine*  theAggregate, vector<double> &XPer, vector<double> &YPer, 
                        double (demogCombo::*f1)() const, double (demogCombo::*f2)() const) {
    //for all demographic data
    for (auto entry : theAggregate->getComboDemog()) {
        double xP = ((entry.second).get()->*f1)();
        double yP = ((entry.second).get()->*f2)();
        if (!isnan(xP) && !isnan(yP)) {
            YPer.push_back(yP);
            XPer.push_back(xP);
        }
    }
}

 /* percents and counts on demog */
int statTool::gatherBothStats(visitorCombine*  theAggregate, vector<double> &XPer, vector<double> &YPer,
                                    vector<double> &XCount, vector<double> &Ycount,
                                    double (demogCombo::*f1)() const, double (demogCombo::*f2)() const,
                                    int (demogCombo::*f3)() const, int (demogCombo::*f4)() const) {

    //first functions for percentages
    gatherPerStats(theAggregate, XPer, YPer, f1, f2);

    //now fill in the counts
    int totPop = 0;
    for (auto entry : theAggregate->getComboDemog()) {
        shared_ptr<demogCombo> demogForC = entry.second;
        double xC = ((entry.second).get()->*f3)();
        double yC = ((entry.second).get()->*f4)();
        if (!isnan(xC) && !isnan(yC)) {
            XCount.push_back(xC);
            Ycount.push_back(yC);
            totPop += (entry.second)->getPop();
        }
    }
    return totPop;
}


/* compute statistics for demographic data for a given region expects, 
  the region and function pointers for the methods to fill in - two demog fields */
void statTool::computeStatsDemogRegionData(visitorCombine*  theRegions, 
                                double  (demogCombo::*f1)()const, double(demogCombo::*f2)() const,
                                int (demogCombo::*f3)() const, int (demogCombo::*f4)() const) {
    //data for both percents and counts
    vector<double> dataXcount;
    vector<double> dataYcount;
    vector<double> dataXpercent;
    vector<double> dataYpercent;

    //fill in the data
    int totPop = gatherBothStats(theRegions, dataXpercent, dataYpercent, 
        dataXcount, dataYcount, f1, f2, f3, f4);

    double mX = stats::computePopMean(dataXcount, totPop); 
    double mY = stats::computePopMean(dataYcount, totPop);  
    cout << "REGION demographic statistics:" << endl;
    cout << "stats mean X: " << mX    << " size of vector: " << dataXcount.size() << endl;
    cout << "stats mean Y: " << mY << " size of vector: " << dataYcount.size() << endl;

    cout << "std dev mean X: " << stats::computeStdDevPop(dataXpercent, mX) << endl;
    cout << "std dev mean Y: " << stats::computeStdDevPop(dataYpercent, mY) << endl;
    //cout << "Pearson Coeff: "<<stats::computeCorCoeff(dataXpercent, dataYpercent)<< endl;
    cout << "Population Coeff: " <<stats::computeCorCoeffPop(dataXpercent, dataYpercent, mX, mY)<< endl;


    writeToCSV(dataXcount, dataYcount, "DemogCounts.csv");
    writeToCSV(dataXpercent, dataYpercent, "DemogPercents.csv");
    
}

  /* compute statistics for demographic data for a given region expects, 
  the region and function pointers for the methods to fill in - mix ps and demog */
void statTool::computeStatsMixRegionData(visitorCombine*  theRegions, 
        int(demogCombo::*f1)() const, int (psCombo::*f2)() const) {

    vector<double> dataX;
    vector<double> dataY;

    gatherCountStats(theRegions, dataX, dataY, f1, f2);

    double mX = stats::computeMean(dataX); 
    double mY = stats::computeMean(dataY);  
    cout << "REGION stats comparing demographic and police shooting data " << endl;
    cout << "stats mean X: " << mX    << " size of vector: " << dataX.size() << endl;
    cout << "stats mean Y: " << mY << " size of vector: " << dataY.size() << endl;

    cout << "std dev mean X: " << stats::computeStdDevSample(dataX) << endl;
    cout << "std dev mean Y: " << stats::computeStdDevSample(dataY) << endl;
    cout << "Correlation Coeff (sample): " <<stats::computeCorCoeffSample(dataX, dataY)<< endl;

   writeToCSV(dataX, dataY, "MixCounts.csv");
}

  /* compute statistics for demographic data for a given region expects, 
  the region and function pointers for the methods to fill in - two police shooting fields */
void statTool::computeStatsPSData(visitorCombine*  theRegions, 
                                int (psCombo::*f1)()const, int (psCombo::*f2)() const) {

    vector<double> dataX;
    vector<double> dataY;

    gatherCountStats(theRegions, dataX, dataY, f1, f2);

    double mX = stats::computeMean(dataX); 
    double mY = stats::computeMean(dataY);  
    cout << "REGION stats comparing police shooting data two variables " << endl;
    cout << "stats mean X: " << mX    << " size of vector: " << dataX.size() << endl;
    cout << "stats mean Y: " << mY << " size of vector: " << dataY.size() << endl;

    cout << "std dev mean X: " << stats::computeStdDevSample(dataX) << endl;
    cout << "std dev mean Y: " << stats::computeStdDevSample(dataY) << endl;
    cout << "Correlation Coeff (sample): " <<stats::computeCorCoeffSample(dataX, dataY)<< endl;

   writeToCSV(dataX, dataY, "PSCounts.csv");
}

  /* compute statistics for mixed demographic data and police shooting data for racial demographics, expects 
  the region and function pointers for the methods to fill in - note computes proportions */
void statTool::computeStatsRaceProportion(visitorCombine*  theRegions, 
                                int (raceDemogData::*f1)()const, int (raceDemogData::*f2)() const) {

    vector<double> dataX;
    vector<double> dataY;

    gatherMixRaceProportionStats(theRegions, dataX, dataY, f1, f2);

    double mX = stats::computeMean(dataX); 
    double mY = stats::computeMean(dataY);  
    cout << "REGION stats comparing demographic data proportions to police shooting data proportions " << endl;
    cout << "demog stats mean X: " << mX    << " size of vector: " << dataX.size() << endl;
    cout << "ps stats mean Y: " << mY << " size of vector: " << dataY.size() << endl;

    cout << "demog std dev mean X: " << stats::computeStdDevSample(dataX) << endl;
    cout << "ps std dev mean Y: " << stats::computeStdDevSample(dataY) << endl;

   writeToCSV(dataX, dataY, "Proportions.csv");
}


