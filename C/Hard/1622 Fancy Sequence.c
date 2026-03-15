#include <stdlib.h>
#include <stdio.h>

#define MOD 1000000007

typedef struct {
    long long *nums;
    int size;
    int capacity;
    long long multiplier;
    long long increment;
} Fancy;

// Helper: Power function for Modular Inverse (Fermat's Little Theorem)
long long power(long long base, long long exp) {
    long long res = 1;
    base %= MOD;
    while (exp > 0) {
        if (exp % 2 == 1) res = (res * base) % MOD;
        base = (base * base) % MOD;
        exp /= 2;
    }
    return res;
}

long long modInverse(long long n) {
    return power(n, MOD - 2);
}

Fancy* fancyCreate() {
    Fancy* obj = (Fancy*)malloc(sizeof(Fancy));
    obj->capacity = 100;
    obj->nums = (long long*)malloc(sizeof(long long) * obj->capacity);
    obj->size = 0;
    obj->multiplier = 1;
    obj->increment = 0;
    return obj;
}

void fancyAppend(Fancy* obj, int val) {
    if (obj->size == obj->capacity) {
        obj->capacity *= 2;
        obj->nums = (long long*)realloc(obj->nums, sizeof(long long) * obj->capacity);
    }
    
    // Reverse the transformation: x = (val - inc) * inv(mult)
    long long transformed = (val - obj->increment + MOD) % MOD;
    transformed = (transformed * modInverse(obj->multiplier)) % MOD;
    
    obj->nums[obj->size++] = transformed;
}

void fancyAddAll(Fancy* obj, int inc) {
    obj->increment = (obj->increment + inc) % MOD;
}

void fancyMultAll(Fancy* obj, int m) {
    obj->multiplier = (obj->multiplier * m) % MOD;
    obj->increment = (obj->increment * m) % MOD;
}

int fancyGetIndex(Fancy* obj, int idx) {
    if (idx >= obj->size) return -1;
    
    // Apply the current transformation: (stored_val * mult + inc)
    long long res = (obj->nums[idx] * obj->multiplier) % MOD;
    res = (res + obj->increment) % MOD;
    return (int)res;
}

void fancyFree(Fancy* obj) {
    free(obj->nums);
    free(obj);
}
