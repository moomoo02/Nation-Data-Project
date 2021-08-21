#ifndef RACEDEMOG_H
#define RACEDEMOG_H

#include <iostream>

class raceDemogData {
  public:
  		//default constructor
  	    raceDemogData() :
            FirstNationCount(0), AsianCount(0), BlackCount(0), LatinxCount(0), HIPacificIsleCount(0),
            MultiRaceCount(0), WhiteCount(0), WhiteNHCount(0), otherCount(0), communityCount(0) {}

        raceDemogData(int FN, int A, int B, int L, int HPI, int MR, int W, int WNH, int size) :
            FirstNationCount(FN), AsianCount(A), BlackCount(B), LatinxCount(L), HIPacificIsleCount(HPI),
            MultiRaceCount(MR), WhiteCount(W), WhiteNHCount(WNH), otherCount(0), communityCount(size) {}

            raceDemogData(int FN, int A, int B, int L, int HPI, int MR, int W, int WNH, int size, int other) :
            FirstNationCount(FN), AsianCount(A), BlackCount(B), LatinxCount(L), HIPacificIsleCount(HPI),
            MultiRaceCount(MR), WhiteCount(W), WhiteNHCount(WNH), otherCount(other), communityCount(size) {}

      double getFirstNationPercent() const  { return 100.0f*(double)(FirstNationCount)/communityCount; }
   		double getAsianPercent() const { return 100.0f*(double)(AsianCount)/communityCount; }
    	double getBlackPercent() const { return 100.0f*(double)(BlackCount)/communityCount; }
    	double getLatinxPercent() const { return 100.0f*(double)(LatinxCount)/communityCount; }
    	double getHIPacificIslePercent() const  { return 100.0f*(double)(HIPacificIsleCount)/communityCount; }
    	double getMultiRacePercent() const { return 100.0f*(double)(MultiRaceCount)/communityCount; }
    	double getWhitePercent() const { return 100.0f*(double)(WhiteCount)/communityCount; }
      double getWhiteNHPercent() const { return 100.0f*(double)(WhiteNHCount)/communityCount; }
      double getOtherPercent() const { return 100.0f*(double)(otherCount)/communityCount; }

      int getFirstNationCount() const { return FirstNationCount; }
      int getAsianCount() const { return AsianCount; }
      int getBlackCount() const { return BlackCount; }
      int getLatinxCount() const { return LatinxCount; }
      int getHIPacificIsleCount() const { return HIPacificIsleCount; }
      int getMultiRaceCount() const  { return MultiRaceCount; }
      int getWhiteCount() const { return WhiteCount; }
      int getWhiteNHCount() const { return WhiteNHCount; }
      int getOtherCount() const { return otherCount; }
      int getCommunityCount() const { return communityCount; }

      void addFirstNationCount(int inNum)  { FirstNationCount += inNum;   }
      void addAsianCount(int inNum)    { AsianCount+= inNum;  }
      void addBlackCount(int inNum)    { BlackCount+= inNum; }
      void addLatinxCount(int inNum)   { LatinxCount+= inNum; }
      void addHIPacificIsleCount(int inNum)    { HIPacificIsleCount+= inNum; }
      void addMultiRaceCount(int inNum)     { MultiRaceCount+= inNum; }
      void addWhiteCount(int inNum)    { WhiteCount+= inNum; }
      void addWhiteNHCount(int inNum)    { WhiteNHCount+= inNum; }
      void addOtherCount(int inNum)    { otherCount+= inNum; }
      void addCommunityCount(int inNum)   { communityCount+= inNum; }

      raceDemogData& operator+=(const raceDemogData rd) {
        FirstNationCount += rd.FirstNationCount;
        AsianCount += rd.AsianCount;
        BlackCount += rd.BlackCount;
        LatinxCount += rd.LatinxCount;
        HIPacificIsleCount += rd.HIPacificIsleCount;
        MultiRaceCount += rd.MultiRaceCount;
        WhiteCount += rd.WhiteCount;
        WhiteNHCount += rd.WhiteNHCount;
        otherCount += rd.otherCount;
        communityCount += rd.communityCount;

        return *(this);
    }
    raceDemogData operator+(const raceDemogData& rd) {
        raceDemogData rdd;
        rdd.FirstNationCount = this->FirstNationCount + rd.FirstNationCount;
        rdd.AsianCount = this->AsianCount + rd.AsianCount;
        rdd.BlackCount = this->BlackCount + rd.BlackCount;
        rdd.LatinxCount = this->LatinxCount + rd.LatinxCount;
        rdd.HIPacificIsleCount = this->HIPacificIsleCount + rd.HIPacificIsleCount;
        rdd.MultiRaceCount = this->MultiRaceCount + rd.MultiRaceCount;
        rdd.WhiteCount = this->WhiteCount + rd.WhiteCount;
        rdd.WhiteNHCount = this->WhiteNHCount + rd.WhiteNHCount;
        rdd.otherCount = this->otherCount + rd.otherCount;
        rdd.communityCount = this->communityCount + rd.communityCount;

        return rdd;
    }

    friend std::ostream& operator<<(std::ostream &out, const raceDemogData &SD);

  private:
  	//count of population for various racial/ethinic identifies 
  	//from US census (assumes 'alone' except LatinX, Multiracial, White)
    int FirstNationCount; //Native American/First Nation
    int AsianCount; //Asian American
    int BlackCount; //African American/Black
    int LatinxCount; //Hispanic/Latinx
    int HIPacificIsleCount; //Hawaiian Pacific Islander
    int MultiRaceCount; //Multi-racial
    int WhiteCount; //White (includes Hispanic)
    int WhiteNHCount; //White non-Hispanic
    int otherCount; //Other category used for other data sources
    //as white and multi-racial could double count this is an approximate value for some
    //racial demographics for a community
    int communityCount; //how many individuals added to community
};

#endif