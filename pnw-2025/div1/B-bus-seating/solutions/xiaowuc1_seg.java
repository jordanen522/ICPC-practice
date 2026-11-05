import java.io.*;
import java.util.*;
public class xiaowuc1_seg {
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
    SegmentTree[] dp = new SegmentTree[k];
    for(int i = 0; i < k; i++) {
      dp[i] = new SegmentTree(n+1);
    }
    for(int i = 1; i <= n; i++) dp[0].upd(i, 1);
    int[] ret = new int[m];
    int lhs = 0;
    for(int i = 0; i < m; i++) {
      long[] best = new long[]{0, 1, -1}; // <num, denom, idx>
      while(dp[lhs].root.val == 0) lhs++;
      for(int x = lhs; x <= lhs + 30 && x < k; x++) {
        Integer crow = dp[x].qrysmall(rows[i], n);
        if(crow != -1) {
          upd(best, c - Math.abs(crow - rows[i]), 1 << (x - lhs), crow);
        }
        crow = dp[x].qrylarge(1, rows[i]-1);
        if(crow != -1) {
          upd(best, c - Math.abs(crow - rows[i]), 1 << (x - lhs), crow);
        }
      }
      int cand = (int)best[2];
      ret[i] = cand;
      dp[used[cand]].upd(cand, 0);
      if(++used[cand] < k) dp[used[cand]].upd(cand, 1);
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
  static class Node {
    public int start, sz, val;
    public Node lhs, rhs;
    public Node(int a, int b, int c) {
      start = a;
      sz = b;
      val = c;
    }
    public int qrysmall(int lhsi, int rhsi) {
      int end = start + sz - 1;
      if(val == 0 || end < lhsi || start > rhsi) return -1;
      if(sz == 1) return start;
      if(lhs != null) {
        int ret = lhs.qrysmall(lhsi, rhsi);
        if(ret != -1) return ret;
      }
      if(rhs != null) {
        int ret = rhs.qrysmall(lhsi, rhsi);
        if(ret != -1) return ret;
      }
      return -1;
    }
    public int qrylarge(int lhsi, int rhsi) {
      int end = start + sz - 1;
      if(val == 0 || end < lhsi || start > rhsi) return -1;
      if(sz == 1) return start;
      if(rhs != null) {
        int ret = rhs.qrylarge(lhsi, rhsi);
        if(ret != -1) return ret;
      }
      if(lhs != null) {
        int ret = lhs.qrylarge(lhsi, rhsi);
        if(ret != -1) return ret;
      }
      return -1;
    }
    public void upd(int idx, int vali) {
      if(idx < start || idx >= start + sz) return;
      if(sz == 1) {
        val = vali;
        return;
      }
      if(idx >= start && idx < start + sz / 2) {
        if(lhs == null) {
          lhs = new Node(start, sz/2, 0);
        }
        lhs.upd(idx, vali);
      }
      else {
        if(rhs == null) {
          rhs = new Node(start + sz/2, sz/2, 0);
        }
        rhs.upd(idx, vali);
      }
      val = 0;
      if(lhs != null) val += lhs.val;
      if(rhs != null) val += rhs.val;
    }
  }
  static class SegmentTree {
    Node root;
    int SZ;
    public SegmentTree(int n) {
      SZ = 1;
      while(SZ < n) SZ *= 2;
      root = new Node(0, SZ, 0);
    }
    public void upd(int idx, int val) {
      root.upd(idx, val);
    }
    public int qrysmall(int lhs, int rhs) {
      return root.qrysmall(lhs, rhs);
    }
    public int qrylarge(int lhs, int rhs) {
      return root.qrylarge(lhs, rhs);
    }
  }
}
