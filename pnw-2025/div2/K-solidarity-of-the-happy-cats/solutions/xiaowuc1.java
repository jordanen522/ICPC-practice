import java.util.*;
public class xiaowuc1 {
  public static void main(String[] args) throws Exception {
    Scanner sc = new Scanner(System.in);
    int n = sc.nextInt();
    int m = sc.nextInt();
    int[] radiusv = new int[n];
    int[] typev = new int[n];
    for(int i = 0; i < n; i++) {
      radiusv[i] = sc.nextInt();
      typev[i] = sc.nextInt()-1;
    }
    char[][] g = new char[m][m];
    for(int i = 0; i < m; i++) {
      String s = sc.next();
      for(int j = 0; j < m; j++) g[i][j] = s.charAt(j);
    }
    long[] dp = new long[n];
    for(int i = 1; i < n; i++) dp[i] = i;
    for(int i = 0; i < n; i++) for(int j = i+1; j < n; j++) {
      if(g[typev[i]][typev[j]] == '0') dp[j] = Math.max(dp[j], dp[i] + radiusv[j] + 1);
      if(g[typev[j]][typev[i]] == '0') dp[j] = Math.max(dp[j], dp[i] + radiusv[i] + 1);
      dp[j] = Math.max(dp[j], dp[i] + j - i);
    }
    System.out.println(dp[n-1]+1);
  }
}
