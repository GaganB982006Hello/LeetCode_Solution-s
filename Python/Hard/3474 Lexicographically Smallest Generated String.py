class Solution:
    def generateString(self, str1: str, str2: str) -> str:
        n, m = len(str1), len(str2)
        total_len = n + m - 1
        res = [None] * total_len
        fixed = [False] * total_len

        # Step 1: Satisfy all 'T' conditions
        for i in range(n):
            if str1[i] == 'T':
                for j in range(m):
                    if res[i + j] is not None and res[i + j] != str2[j]:
                        return ""  # Contradiction found
                    res[i + j] = str2[j]
                    fixed[i + j] = True

        # Step 2: Fill remaining gaps with 'a' for lexicographical smallness
        for i in range(total_len):
            if res[i] is None:
                res[i] = 'a'

        # Step 3: Handle 'F' conditions
        for i in range(n):
            if str1[i] == 'F':
                # Check if the current substring matches str2
                if "".join(res[i : i + m]) == str2:
                    changed = False
                    # Try to change the rightmost non-fixed character to 'b'
                    for j in range(m - 1, -1, -1):
                        if not fixed[i + j]:
                            res[i + j] = 'b'
                            changed = True
                            break
                    
                    if not changed:
                        return "" # All characters in this 'F' range are fixed by 'T's
            else:
                # Double check 'T' conditions (safety check for contradictions)
                if "".join(res[i : i + m]) != str2:
                    return ""

        return "".join(res)
