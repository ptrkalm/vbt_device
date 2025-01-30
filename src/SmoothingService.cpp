#include "SmoothingService.h"

#define AVG_WINDOW_LENGTH 40

SmoothingService::SmoothingService() : averageValue(AVG_WINDOW_LENGTH) {};

bool SmoothingService::smooth(DataPoint *smoothedDataPoint, DataPoint dataPoint) {
  averageValue.push(dataPoint.value);
  counter++;
  if (counter < 20) return false;

  timeQueue.add(dataPoint.time);
  
  if (counter < 40) return false;
  
  smoothedDataPoint -> time = timeQueue[0];
  smoothedDataPoint -> value = averageValue.average();
  
  timeQueue.removeFirst();
  
  return true;
}