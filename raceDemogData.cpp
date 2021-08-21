#include "raceDemogData.h"
#include <iostream>
#include <iomanip>

std::ostream& operator<<(std::ostream &out, const raceDemogData &DD) {
    out << "Racial Demographics Info: ";
    out << std::setprecision(2) << std::fixed;
    out << "\n\% American Indian and Alaska Native";
    if (DD.getFirstNationCount() > 0)
        out << " percent: " << DD.getFirstNationPercent();
    out << " count: " << DD.getFirstNationCount();
    out << "\n\% Asian American";
    if (DD.getAsianCount() > 0)
        out << " percent: " << DD.getAsianPercent();
    out << " count: " <<  DD.getAsianCount();
    out << "\n\% Black/African American";
    if (DD.getBlackCount() > 0)
        out << " percent: " << DD.getBlackPercent();
    out << " count: " << DD.getBlackCount();
    out << "\n\% Hispanic or Latinx";
    if (DD.getLatinxCount() > 0)
        out << " percent: " << DD.getLatinxPercent();
    out << " count: " << DD.getLatinxCount();
    out << "\n\% Native Hawaiian and Other Pacific Islander";
    if (DD.getHIPacificIsleCount() > 0)
        out << " percent: " << DD.getHIPacificIslePercent();
    out << " count: " << DD.getHIPacificIsleCount();
    out << "\n\% Two or More Races";
    if (DD.getMultiRaceCount() > 0)
        out << " percent: " << DD.getMultiRacePercent();
    out << " count: " << DD.getMultiRaceCount();
    out << "\n\% White (inclusive)";
    if (DD.getWhiteCount() > 0)
        out << " percent: " << DD.getWhitePercent();
    out << " count: " << DD.getWhiteCount();
    out << "\n\% White (nonHispanic)";
    if (DD.getWhiteNHCount() > 0)
        out << " percent: " << DD.getWhiteNHPercent();
    out << " count: " << DD.getWhiteNHCount();
    if (DD.otherCount >0) {
      out << "\n\% Other";
      out << " percent: " << DD.getOtherPercent();
      out << " count: " << DD.getOtherCount();
    }
    out << "\ntotal Racial Demographic Count: " << DD.communityCount;
    return out;
}
