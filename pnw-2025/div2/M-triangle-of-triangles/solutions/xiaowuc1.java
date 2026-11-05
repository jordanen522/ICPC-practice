import java.util.*;
public class xiaowuc1 {
  public static void main(String[] args) throws Exception {
    Scanner sc = new Scanner(System.in);
    int t = sc.nextInt();
    while(t-- > 0) {
      int[][] g = new int[3][3];
      for(int i = 0; i < 3; i++) for(int j = 0; j < 3; j++) g[i][j] = sc.nextInt();
      if(can(g[0], g[1], g[2]) || can(g[0], g[1], g[1]) || can(g[0], g[2], g[2])) System.out.println("YES");
      else System.out.println("NO");
    }
  }
  public static boolean can(int[] have, int[] a, int[] b) {
    int[][] ap = genperm(a);
    int[][] bp = genperm(b);
    for(int[] aa: ap) for(int[] bb: bp) {
      if(aa[0] + bb[0] != 180) continue;
      int[] now = new int[]{aa[1], bb[1], aa[2] + bb[2]};
      if(same(have, now)) return true;
    }
    return false;
  }
  public static boolean same(int[] a, int[] b) {
    int[] c = new int[]{a[0], a[1], a[2]};
    Arrays.sort(c);
    int[] d = new int[]{b[0], b[1], b[2]};
    Arrays.sort(d);
    return c[0] == d[0] && c[1] == d[1] && c[2] == d[2];
  }
  public static int[][] genperm(int[] a) {
    int[][] ret = new int[6][];
    ret[0] = new int[]{a[0], a[1], a[2]};
    ret[1] = new int[]{a[0], a[2], a[1]};
    ret[2] = new int[]{a[1], a[0], a[2]};
    ret[3] = new int[]{a[1], a[2], a[0]};
    ret[4] = new int[]{a[2], a[0], a[1]};
    ret[5] = new int[]{a[2], a[1], a[0]};
    return ret;
  }
}
