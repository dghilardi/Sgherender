#include "printutils.h"

PrintUtils::PrintUtils()
{
}

void PrintUtils::printPercentage(int status, int total, const string *lbl){
    cout.flush();
    stringstream str;
    int perc = status*100/total;
    str << perc << "% "<< (lbl==0?"":*lbl) <<"\t[";
    for(int i=0; i<50; ++i) str << (i*2<perc?"#":i*2==perc?"+":"-");
    str << "]\r";
    string percentage = str.str();
    cout << percentage;
}
