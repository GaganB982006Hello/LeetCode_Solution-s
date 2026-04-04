class Solution {
    public String decodeCiphertext(String encodedText, int rows) {
        if (encodedText.length() == 0) return "";
        
        int n = encodedText.length();
        int cols = n / rows;
        StringBuilder sb = new StringBuilder();
        
        for (int i = 0; i < cols; i++) {
            for (int r = 0, c = i; r < rows && c < cols; r++, c++) {
                sb.append(encodedText.charAt(r * cols + c));
            }
        }
        
        // Trim only trailing spaces
        int last = sb.length() - 1;
        while (last >= 0 && sb.charAt(last) == ' ') {
            last--;
        }
        return sb.substring(0, last + 1);
    }
}
