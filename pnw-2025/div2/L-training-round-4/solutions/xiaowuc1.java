import java.util.*;
public class xiaowuc1 {
  public static void main(String[] args) throws Exception {
    Scanner sc = new Scanner(System.in);
    int n = sc.nextInt();
    int aa = 0, bb = 0;
    int extra = 0;
    for(int i = 0; i < n; i++) {
      int a = sc.nextInt();
      int b = sc.nextInt();
      if(a > aa) {
        int use = Math.min(a - aa, extra);
        extra -= use;
        aa += use;
        aa = Math.max(a, aa);
      }
      if(b > bb) {
        int use = Math.min(b - bb, extra);
        extra -= use;
        bb += use;
        bb = Math.max(b, bb);
      }
      extra++;
    }
    System.out.println(aa+bb+extra-n);
  }
}
