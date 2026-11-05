import java.util.*;
public class xiaowuc1 {
  static final String WANT = "shh";
  public static int getNext(String s) {
    for(int len = Math.min(s.length(), WANT.length()); len > 0; len--) {
      if(s.substring(s.length() - len).equals(WANT.substring(0, len))) {
        return len;
      }
    }
    return 0;
  }
  static final long MOD = 67;
  public static void main(String[] args) throws Exception {
    Scanner sc = new Scanner(System.in);
    int n = sc.nextInt();
    int k = sc.nextInt();
    String s = sc.next();
    long[][][] dp = new long[k+1][3][2];
    for(int a = 0; a <= k; a++) for(int b = 0; b < 3; b++) dp[a][b][0] = 1 << 25;
    dp[0][0][0] = 0;
    dp[0][0][1] = 1;
    for(int i = 0; i < n; i++) {
      long[][][] ndp = new long[k+1][3][2];
      for(int a = 0; a <= k; a++) for(int b = 0; b < 3; b++) ndp[a][b][0] = 1 << 25;
      for(int a = 0; a <= k; a++) for(int b = 0; b < 3; b++) {
        if(dp[a][b][0] == 1 << 25) continue;
        String have = WANT.substring(0, b);
        for(char c = 'a'; c <= 'z'; c++) {
          String nhave = have + c;
          int na = a;
          int nb = getNext(nhave);
          long nchange = dp[a][b][0];
          if(c != s.charAt(i)) nchange++;
          long nways = dp[a][b][1];
          if(nb == 3) {
            na++; nb = 0;
          }
          if(na <= k) {
            if(nchange < ndp[na][nb][0]) {
              ndp[na][nb][0] = nchange;
              ndp[na][nb][1] = 0;
            }
            if(nchange == ndp[na][nb][0]) {
              ndp[na][nb][1] += nways;
              ndp[na][nb][1] %= MOD;
            }
          }
        }
      }
      dp = ndp;
    }
    long minchange = 1 << 25;
    long minways = 0;
    for(int i = 0; i < 3; i++) {
      if(dp[k][i][0] < minchange) {
        minchange = dp[k][i][0];
        minways = 0;
      }
      if(dp[k][i][0] == minchange) {
        minways += dp[k][i][1];
      }
    }
    System.out.println(minchange + " " + minways%MOD);
  }
}
