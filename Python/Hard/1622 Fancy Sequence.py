class Fancy:
    def __init__(self):
        self.nums = []
        self.mult = 1
        self.inc = 0
        self.MOD = 10**9 + 7

    def append(self, val: int) -> None:
        # Store val such that (val_stored * mult + inc) == val
        # val_stored = (val - inc) * inv(mult)
        inv_mult = pow(self.mult, self.MOD - 2, self.MOD)
        self.nums.append(((val - self.inc) * inv_mult) % self.MOD)

    def addAll(self, inc: int) -> None:
        self.inc = (self.inc + inc) % self.MOD

    def multAll(self, m: int) -> None:
        self.mult = (self.mult * m) % self.MOD
        self.inc = (self.inc * m) % self.MOD

    def getIndex(self, idx: int) -> int:
        if idx >= len(self.nums):
            return -1
        return (self.nums[idx] * self.mult + self.inc) % self.MOD
