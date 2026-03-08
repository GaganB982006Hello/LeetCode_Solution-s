class Solution {
    public int countCollisions(String directions) {
        int n = directions.length();
        char[] s = directions.toCharArray();

        int left = 0;
        // skip all leading 'L' cars
        while (left < n && s[left] == 'L') {
            left++;
        }

        int right = n - 1;
        // skip all trailing 'R' cars
        while (right >= 0 && s[right] == 'R') {
            right--;
        }

        // Now [left, right] is the effective collision zone
        int collisions = 0;
        for (int i = left; i <= right; i++) {
            if (s[i] != 'S') {
                collisions++;  // every moving car here will collide once
            }
        }

        return collisions;
    }
}