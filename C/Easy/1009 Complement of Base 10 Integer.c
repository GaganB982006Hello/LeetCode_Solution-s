int bitwiseComplement(int n) {
    if (n == 0) return 1;

    int mask = 0;
    int m = n;
    while (m != 0) {
        mask = (mask << 1) | 1;
        m >>= 1;
    }

    return (~n) & mask;
}
