import java.util.*;
public class xiaowuc1 {
  static int[] dx = new int[]{-1,0,1,0};
  static int[] dy = new int[]{0,1,0,-1};
  static final int MOD = 998244353;
  public static void main(String[] args) throws Exception {
    Scanner sc = new Scanner(System.in);
    int r = sc.nextInt();
    int c = sc.nextInt();
    char[][] g = new char[r][c];
    for(int i = 0; i < r; i++) {
      String s = sc.next();
      for(int j = 0; j < c; j++) g[i][j] = s.charAt(j);
    }
    if(c > r) {
      char[][] ng = new char[c][r];
      for(int i = 0; i < r; i++) for(int j = 0; j < c; j++) {
        ng[j][i] = g[i][j];
      }
      g = ng;
      r = g.length;
      c = g[0].length;
    }
    for(int i = 0; i < r; i++) for(int j = 0; j < c; j++) {
      if(g[i][j] == '2') {
        for(int k = 0; k < 4; k++) {
          int nx = i + dx[k];
          int ny = j + dy[k];
          if(nx >= 0 && nx < r && ny >= 0 && ny < c) g[nx][ny] = '0';
        }
      }
    }
    int[][] dpret = new int[2][1 << c];
    int[][] waysret = new int[2][1 << c];
    Arrays.fill(dpret[0], -(1 << 30));
    dpret[0][0] = 0;
    waysret[0][0] = 1;
    int src = 0;
    int dst = 1;
    for(int i = 0; i < r; i++) for(int j = 0; j < c; j++) {
      Arrays.fill(dpret[dst], -(1 << 30));
      for(int k = 0; k < (1<<c); k++) {
        // do not use
        int nk = (k << 1) & ((1 << c) - 1);
        if(dpret[dst][nk] < dpret[src][k]) {
          dpret[dst][nk] = dpret[src][k];
          waysret[dst][nk] = 0;
        }
        if(dpret[dst][nk] == dpret[src][k]) {
          waysret[dst][nk] += waysret[src][k];
          if(waysret[dst][nk] >= MOD) waysret[dst][nk] -= MOD;
        }
        // use
        boolean canuse = g[i][j] == '1';
        if((j > 0) && (k & 1) == 1) canuse = false;
        if((k & (1 << (c - 1))) > 0) canuse = false;
        if(canuse) {
          nk |= 1;
          if(dpret[dst][nk] < dpret[src][k] + 1) {
            dpret[dst][nk] = dpret[src][k] + 1;
            waysret[dst][nk] = 0;
          }
          if(dpret[dst][nk] == dpret[src][k] + 1) {
            waysret[dst][nk] += waysret[src][k];
            if(waysret[dst][nk] >= MOD) waysret[dst][nk] -= MOD;
          }
        }
      }
      src ^= 1; dst ^= 1;
    }
    int amt = 0;
    int ret = 0;
    for(int mask = 0; mask < (1<<c); mask++) {
      if(dpret[src][mask] > amt) {
        amt = dpret[src][mask];
        ret = 0;
      }
      if(dpret[src][mask] == amt) {
        ret += waysret[src][mask];
        if(ret >= MOD) ret -= MOD;
      }
    }
    System.out.println(amt + " " + ret);
  }
}
