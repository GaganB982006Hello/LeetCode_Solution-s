/*
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
 
 */

import java.util.TreeMap;

class SummaryRanges {
    // Key: start of interval, Value: [start, end]
    private TreeMap<Integer, int[]> tree;

    public SummaryRanges() {
        tree = new TreeMap<>();
    }
    
    public void addNum(int value) {
        if (tree.containsKey(value)) {
            return;
        }
        
        // Find the closest interval starting before 'value'
        Integer lower = tree.lowerKey(value);
        // Find the closest interval starting after 'value'
        Integer higher = tree.higherKey(value);
        
        // Check if value is already inside the lower interval
        if (lower != null && lower <= value && value <= tree.get(lower)[1]) {
            return;
        }
        
        boolean mergeLower = (lower != null && tree.get(lower)[1] == value - 1);
        boolean mergeHigher = (higher != null && higher == value + 1);
        
        if (mergeLower && mergeHigher) {
            // Connect lower and higher intervals
            tree.get(lower)[1] = tree.get(higher)[1];
            tree.remove(higher);
        } else if (mergeLower) {
            // Extend lower interval
            tree.get(lower)[1] = value;
        } else if (mergeHigher) {
            // Extend higher interval by replacing the key
            int[] highInterval = tree.get(higher);
            tree.remove(higher);
            tree.put(value, new int[]{value, highInterval[1]});
        } else {
            // Create a new independent interval
            tree.put(value, new int[]{value, value});
        }
    }
    
    public int[][] getIntervals() {
        int[][] res = new int[tree.size()][2];
        int i = 0;
        for (int[] interval : tree.values()) {
            res[i++] = interval;
        }
        return res;
    }
}
