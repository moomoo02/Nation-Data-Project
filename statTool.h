
#ifndef STATTOOL_H
#define STATTOOL_H

#include "demogCombo.h"
#include "psCombo.h"

#include "visitor.h"
#include "stats.h"

/* wrapper for some useful functions to report necessary data */
class statTool {

public:

  /* call visitor pattern to create state data */
  static void createStateData(std::vector<shared_ptr<regionData> >& theData, Visitor& theStates);

  /* call visitor pattern to create county data */
  static  void createCountyData(std::vector<shared_ptr<regionData> >& theData, Visitor& theCounties);
  
  /*create the keyes */
  static void createKeys(std::vector<shared_ptr<regionData>>& theData, Visitor& theKeyes);

  //these could be simplified in future
  /* call visitor pattern to create aggregate data using a specific criteria */
  static  void createKeyedDataDemog(std::vector<shared_ptr<regionData>>& theData, Visitor& theKeyed);

  /* call visitor pattern to create keyed data based on keyes generated from PS criteria*/
  static  void createKeyedDataPS(std::vector<shared_ptr<regionData>>& theData, Visitor& theKeyed);

  /* helper functions to fill in arrays based on funciton pointers  - on mix*/
  static void gatherCountStats(visitorCombine* theAggregate, vector<double> &XPer, vector<double> &YPer, 
                int (demogCombo::*f1)() const, int (psCombo::*f2)() const);

  /* helper functions to fill in arrays based on funciton pointers  - on police hsooting only*/
  static void gatherCountStats(visitorCombine* theAggregate, vector<double> &XPer, vector<double> &YPer, 
                int (psCombo::*f1)() const, int (psCombo::*f2)() const);

  /* helper functions to fill in arrays based on funciton pointers  - on demog percentages*/
  static void gatherPerStats(visitorCombine*  theAggregate, vector<double> &XPer, vector<double> &YPer, 
                        double (demogCombo::*f1)() const, double (demogCombo::*f2)() const);

  /* percents and counts on demog */
  static int gatherBothStats(visitorCombine*  theAggregate, vector<double> &XPer, vector<double> &YPer,
                                    vector<double> &XCount, vector<double> &Ycount,
                                    double (demogCombo::*f1)() const, double (demogCombo::*f2)() const,
                                    int (demogCombo::*f3)() const, int (demogCombo::*f4)() const);

  static void gatherMixRaceProportionStats(visitorCombine* theAggregate, vector<double> &XPer, vector<double> &YPer, 
                int (raceDemogData::*f1)() const, int (raceDemogData::*f2)() const);
  
  /* compute statistics for demographic data for a given region expects, 
  the region and function pointers for the methods to fill in - mix ps and demog */
  static void computeStatsMixRegionData(visitorCombine*  theRegions, 
        int (demogCombo::*f1)() const, int (psCombo::*f2)() const);

  /* compute statistics for demographic data for a given region expects, 
  the region and function pointers for the methods to fill in - two demog fields */
  static void computeStatsDemogRegionData(visitorCombine*  theRegions, 
                                double  (demogCombo::*f1)()const, double(demogCombo::*f2)() const,
                                int (demogCombo::*f3)() const, int (demogCombo::*f4)() const);

  /* compute statistics for demographic data for a given region expects, 
  the region and function pointers for the methods to fill in - two police shooting fields */
  static void computeStatsPSData(visitorCombine*  theRegions, 
                                int (psCombo::*f1)()const, int (psCombo::*f2)() const);


  /* compute statistics for mixed demographic data and police shooting data for racial demographics, expects 
  the region and function pointers for the methods to fill in - note computes proportions */
  static void computeStatsRaceProportion(visitorCombine*  theRegions, 
                                int (raceDemogData::*f1)()const, int (raceDemogData::*f2)() const);

};
#endif




