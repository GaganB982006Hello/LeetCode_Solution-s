class Solution:
    def decodeCiphertext(self, encodedText: str, rows: int) -> str:
        if not encodedText:
            return ""
        
        n = len(encodedText)
        cols = n // rows
        res = []
        
        # We start each diagonal from the first row (row 0)
        # and move shifted to the right by 'i'
        for i in range(cols):
            r, c = 0, i
            while r < rows and c < cols:
                res.append(encodedText[r * cols + c])
                r += 1
                c += 1
        
        # Join and trim trailing spaces only
        return "".join(res).rstrip()
