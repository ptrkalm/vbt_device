#ifndef SMOOTHING_SERVICE_H
#define SMOOTHING_SERVICE_H

#include <AverageValue.h>
#include <List.hpp>

struct DataPoint {
  float time;
  float value;

  DataPoint() : time(NULL), value(NULL) {}
  DataPoint(float t, float v) : time(t), value(v) {}
};

class SmoothingService {
  public:
    SmoothingService();
    bool smooth(DataPoint *smoothedDataPoint, DataPoint dataPoint);

  private:
    AverageValue<float> averageValue;
    List<float> timeQueue;
    int counter = 0;
};

#endif