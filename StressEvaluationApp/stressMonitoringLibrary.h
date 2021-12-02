#ifndef STRESSMONITORINGLIBRARY_H
#define STRESSMONITORINGLIBRARY_H

#include "QVector"
#include "QVectorIterator"

QVector<double> ECGHeartRatePeakFinder(QVector<double> ecg);
QVector<double> PCGHeartRatePeakFinder(QVector<double> pcg);
double HeartRateAverage(QVector<double> heartRateData);
double MostRecentRMSSD(QVector<double> heartRateData);

#endif // STRESSMONITORINGLIBRARY_H
