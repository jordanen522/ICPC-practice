import java.io.*;
import java.util.*;
public class xiaowuc1 {
  public static void main(String[] args) throws Exception {
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    PrintWriter pw = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));
    StringTokenizer st = new StringTokenizer(br.readLine());
    int n = Integer.parseInt(st.nextToken());
    int k = Integer.parseInt(st.nextToken());
    int m = Integer.parseInt(st.nextToken());
    int c = Integer.parseInt(st.nextToken());
    int[] rows = new int[m];
    st = new StringTokenizer(br.readLine());
    for(int i = 0; i < m; i++) rows[i] = Integer.parseInt(st.nextToken());
    int[] used = new int[n+1];
    TreeSet<Integer>[] dp = new TreeSet[k];
    for(int i = 0; i < k; i++) {
      dp[i] = new TreeSet<>();
    }
    for(int i = 1; i <= n; i++) dp[0].add(i);
    int[] ret = new int[m];
    int lhs = 0;
    for(int i = 0; i < m; i++) {
      long[] best = new long[]{0, 1, -1}; // <num, denom, idx>
      while(dp[lhs].size() == 0) lhs++;
      for(int x = lhs; x <= lhs + 30 && x < k; x++) {
        Integer crow = dp[x].ceiling(rows[i]);
        if(crow != null) {
          upd(best, c - Math.abs(crow - rows[i]), 1 << (x - lhs), crow);
        }
        crow = dp[x].lower(rows[i]);
        if(crow != null) {
          upd(best, c - Math.abs(crow - rows[i]), 1 << (x - lhs), crow);
        }
      }
      int cand = (int)best[2];
      ret[i] = cand;
      dp[used[cand]].remove(cand);
      if(++used[cand] < k) dp[used[cand]].add(cand);
    }
    for(int i = 0; i < m; i++) {
      pw.print(ret[i]);
      if(i == m-1) pw.println();
      else pw.print(' ');
    }
    pw.close();
  }
  private static void upd(long[] best, long num, long denom, int idx) {
    if(num*best[1] > denom*best[0] || (num*best[1] == denom*best[0] && idx < best[2])) {
      best[0] = num;
      best[1] = denom;
      best[2] = idx;
    }
  }
}
