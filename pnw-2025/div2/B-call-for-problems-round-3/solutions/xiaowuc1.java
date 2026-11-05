import java.util.*;
public class xiaowuc1 {
  public static void main(String[] args) throws Exception {
    Scanner sc = new Scanner(System.in);
    int n = sc.nextInt();
    int t = sc.nextInt();
    int[] v = new int[n];
    for(int i = 0; i < n; i++) v[i] = sc.nextInt();
    Arrays.sort(v);
    int ret = 1;
    int lhs = v[0];
    for(int i = 1; i < n; i++) {
      if(v[i] - lhs >= t) {
        ret++;
        lhs = v[i];
      }
    }
    System.out.println(ret);
  }
}

