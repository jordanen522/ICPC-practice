import java.util.*;
public class xiaowuc1 {
  public static void main(String[] args) throws Exception {
    Scanner sc = new Scanner(System.in);
    int n = sc.nextInt();
    int m = sc.nextInt();
    int p = sc.nextInt();
    long ret = 0;
    if(n == 1 && m == 1) {
      System.out.println(1%p);
      return;
    }
    if(n == 1 || m == 1) {
      ret = 1;
      for(int i = 2; i <= Math.max(n, m); i++) {
        ret *= i;
        ret %= p;
      }
      System.out.println(ret);
      return;
    }
    long[][][] dp = new long[n+1][m+1][2];
    dp[2][1][0] = 2 % p;
    dp[1][2][1] = 2 % p;
    for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) {
      if(i+1 <= n) {
        dp[i+1][j][0] += dp[i][j][1];
        dp[i+1][j][0] %= p;
      }
      if(j+1 <= m) {
        dp[i][j+1][1] += dp[i][j][1] * (i+j);
        dp[i][j+1][1] %= p;
      }
      if(i+1 <= n) {
        dp[i+1][j][0] += dp[i][j][0] * (i+j);
        dp[i+1][j][0] %= p;
      }
      if(j+1 <= m) {
        dp[i][j+1][1] += dp[i][j][0] * (i+j);
        dp[i][j+1][1] %= p;
      }
    }
    System.out.println((dp[n][m][0] + dp[n][m][1])%p);
  }
}
