class Solution {
    private static final int MOD = 1_000_000_007;

    public int numberOfWays(String corridor) {
        int n = corridor.length();
        int seatCount = 0;

        // Count total seats
        for (int i = 0; i < n; i++) {
            if (corridor.charAt(i) == 'S') {
                seatCount++;
            }
        }

        // If no seats or odd number of seats, no valid division
        if (seatCount == 0 || (seatCount & 1) == 1) {
            return 0;
        }

        long ways = 1;
        int seatsInCurrentSection = 0;
        int plantsBetweenPairs = 0;
        boolean inPair = false;

        for (int i = 0; i < n; i++) {
            char c = corridor.charAt(i);
            if (c == 'S') {
                seatsInCurrentSection++;

                if (seatsInCurrentSection == 2) {
                    // Finished one section (exactly 2 seats)
                    if (inPair) {
                        // For every completed pair after the first,
                        // choices = plantsBetweenPairs + 1
                        ways = (ways * (plantsBetweenPairs + 1)) % MOD;
                    }
                    inPair = true;
                    plantsBetweenPairs = 0;
                    seatsInCurrentSection = 0; // reset for the next section
                }
            } else { // 'P'
                // Count plants only when we are between completed pairs
                if (inPair && seatsInCurrentSection == 0) {
                    plantsBetweenPairs++;
                }
            }
        }

        return (int) ways;
    }
}