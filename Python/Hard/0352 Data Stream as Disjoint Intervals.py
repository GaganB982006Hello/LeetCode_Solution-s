'''
Given a data stream input of non-negative integers a1, a2, ..., an, summarize the numbers seen so far as a list of disjoint intervals.

Implement the SummaryRanges class:

SummaryRanges() Initializes the object with an empty stream.
void addNum(int value) Adds the integer value to the stream.
int[][] getIntervals() Returns a summary of the integers in the stream currently as a list of disjoint intervals [starti, endi]. The answer should be sorted by starti.
 

Example 1:

Input
["SummaryRanges", "addNum", "getIntervals", "addNum", "getIntervals", "addNum", "getIntervals", "addNum", "getIntervals", "addNum", "getIntervals"]
[[], [1], [], [3], [], [7], [], [2], [], [6], []]
Output
[null, null, [[1, 1]], null, [[1, 1], [3, 3]], null, [[1, 1], [3, 3], [7, 7]], null, [[1, 3], [7, 7]], null, [[1, 3], [6, 7]]]

Explanation
SummaryRanges summaryRanges = new SummaryRanges();
summaryRanges.addNum(1);      // arr = [1]
summaryRanges.getIntervals(); // return [[1, 1]]
summaryRanges.addNum(3);      // arr = [1, 3]
summaryRanges.getIntervals(); // return [[1, 1], [3, 3]]
summaryRanges.addNum(7);      // arr = [1, 3, 7]
summaryRanges.getIntervals(); // return [[1, 1], [3, 3], [7, 7]]
summaryRanges.addNum(2);      // arr = [1, 2, 3, 7]
summaryRanges.getIntervals(); // return [[1, 3], [7, 7]]
summaryRanges.addNum(6);      // arr = [1, 2, 3, 6, 7]
summaryRanges.getIntervals(); // return [[1, 3], [6, 7]]
 

Constraints:

0 <= value <= 104
At most 3 * 104 calls will be made to addNum and getIntervals.
At most 102 calls will be made to getIntervals.

 '''

import bisect

class SummaryRanges:
    def __init__(self):
        # Stores lists of [start, end]
        self.intervals = []

    def addNum(self, value: int) -> None:
        # Find the insertion index for the value
        idx = bisect.bisect_right(self.intervals, [value, float('inf')])
        
        left = idx - 1
        right = idx
        
        # Condition 1: Value is already inside the left interval
        if left >= 0 and self.intervals[left][0] <= value <= self.intervals[left][1]:
            return
            
        merge_left = (left >= 0 and self.intervals[left][1] == value - 1)
        merge_right = (right < len(self.intervals) and self.intervals[right][0] == value + 1)
        
        if merge_left and merge_right:
            # Connects both left and right intervals
            self.intervals[left][1] = self.intervals[right][1]
            self.intervals.pop(right)
        elif merge_left:
            # Extends the left interval
            self.intervals[left][1] = value
        elif merge_right:
            # Extends the right interval
            self.intervals[right][0] = value
        else:
            # Insert as a new distinct interval
            self.intervals.insert(right, [value, value])

    def getIntervals(self) -> list[list[int]]:
        return self.intervals
