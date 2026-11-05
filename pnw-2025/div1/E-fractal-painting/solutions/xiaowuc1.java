import java.util.*;
public class xiaowuc1 {
  public static void main(String[] args) throws Exception {
    Scanner sc = new Scanner(System.in);
    int n = sc.nextInt();
    for(int i = 0; i < n; i++) {
      long xa, ya, xb, yb, xc, yc;
      xa = sc.nextLong();
      ya = sc.nextLong();
      xb = sc.nextLong();
      yb = sc.nextLong();
      xc = sc.nextLong();
      yc = sc.nextLong();
      long orig = xa*xa+ya*ya;
      long bdist = (xb-xa)*(xb-xa)+(yb-ya)*(yb-ya);
      long cdist = (xc-xa)*(xc-xa)+(yc-ya)*(yc-ya);
      if(bdist > orig || cdist > orig) System.out.println("NO");
      else if(bdist == orig && 2*xa==xb && 2*ya==yb) System.out.println("NO");
      else if(cdist == orig && 2*xa==xc && 2*ya==yc) System.out.println("NO");
      else if(bdist == orig && cdist == orig) System.out.println("NO");
      else System.out.println("YES");
    }
  }
}
