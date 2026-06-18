/*
Given two numbers, hour and minutes, return the smaller angle (in degrees) formed between the hour and the minute hand.

Answers within 10-5 of the actual value will be accepted as correct.

 

Example 1:


Input: hour = 12, minutes = 30
Output: 165
Example 2:


Input: hour = 3, minutes = 30
Output: 75
Example 3:


Input: hour = 3, minutes = 15
Output: 7.5
 

Constraints:

1 <= hour <= 12
0 <= minutes <= 59
  */

#include <math.h>

double angleClock(int hour, int minutes) {
    // Calculate the angle of the minute hand
    double minuteAngle = minutes * 6.0;
    
    // Calculate the angle of the hour hand
    double hourAngle = (hour % 12) * 30.0 + minutes * 0.5;
    
    // Find the absolute difference
    double diff = fabs(hourAngle - minuteAngle);
    
    // Return the smaller angle
    return fmin(diff, 360.0 - diff);
}
