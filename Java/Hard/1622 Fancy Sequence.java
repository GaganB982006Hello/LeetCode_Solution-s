class Fancy {
    private List<Long> nums;
    private long multiplier = 1;
    private long increment = 0;
    private static final int MOD = 1_000_000_007;

    public Fancy() {
        nums = new ArrayList<>();
    }
    
    public void append(int val) {
        // Reverse the current transformation: (val - increment) / multiplier
        long transformed = (val - increment + MOD) % MOD;
        transformed = (transformed * modInverse(multiplier, MOD)) % MOD;
        nums.add(transformed);
    }
    
    public void addAll(int inc) {
        increment = (increment + inc) % MOD;
    }
    
    public void multAll(int m) {
        multiplier = (multiplier * m) % MOD;
        increment = (increment * m) % MOD;
    }
    
    public int getIndex(int idx) {
        if (idx >= nums.size()) return -1;
        // Apply the current transformation: (transformed_val * multiplier) + increment
        long res = (nums.get(idx) * multiplier) % MOD;
        res = (res + increment) % MOD;
        return (int) res;
    }

    private long modInverse(long n, int mod) {
        return power(n, mod - 2, mod);
    }

    private long power(long x, int y, int m) {
        long res = 1;
        x %= m;
        while (y > 0) {
            if (y % 2 == 1) res = (res * x) % m;
            y = y >> 1;
            x = (x * x) % m;
        }
        return res;
    }
}
