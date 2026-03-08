class Solution {
    public int bestClosingTime(String customers) {
        int n = customers.length();
        
        // Initially, assume shop closes at hour 0:
        // penalty = number of 'Y' (all customers come when shop is closed)
        int penalty = 0;
        for (int i = 0; i < n; i++) {
            if (customers.charAt(i) == 'Y') {
                penalty++;
            }
        }
        
        int minPenalty = penalty;
        int bestHour = 0;
        
        // Move closing hour from 0 to n - 1
        // When moving past index i:
        //  - If customers[i] == 'Y': that customer is now served (was penalty, now not) → penalty--
        //  - If customers[i] == 'N': that hour becomes open with no customers → penalty++
        for (int i = 0; i < n; i++) {
            if (customers.charAt(i) == 'Y') {
                penalty--;     // previously counted as closed-with-customer
            } else { // 'N'
                penalty++;     // now open-without-customer
            }
            
            // closing after hour i => closing time is i + 1
            if (penalty < minPenalty) {
                minPenalty = penalty;
                bestHour = i + 1;
            }
        }
        
        return bestHour;
    }
}