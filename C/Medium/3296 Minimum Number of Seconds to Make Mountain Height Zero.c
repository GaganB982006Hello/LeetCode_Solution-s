#include <math.h>

long long minNumberOfSeconds(int mountainHeight, int* workerTimes, int workerTimesSize) {
    long long l = 1;
    long long minWorkerTime = workerTimes[0];
    for (int i = 1; i < workerTimesSize; i++) {
        if (workerTimes[i] < minWorkerTime) {
            minWorkerTime = workerTimes[i];
        }
    }
    
    long long r = minWorkerTime * (long long)mountainHeight * (mountainHeight + 1) / 2;
    
    while (l < r) {
        long long mid = l + (r - l) / 2;
        long long reducedHeight = 0;
        
        for (int i = 0; i < workerTimesSize; i++) {
            reducedHeight += (long long)((-1.0 + sqrt(1.0 + 8.0 * (double)mid / workerTimes[i])) / 2.0);
        }
        
        if (reducedHeight < mountainHeight) {
            l = mid + 1;
        } else {
            r = mid;
        }
    }
    
    return l;
}
