import java.util.*;

public class honkaistressrelief_AN {
  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);
    int n = s.nextInt(), a = s.nextInt(), b = s.nextInt();
    double logProb = 0;
    for (int i = 0; i < n; i++) {
      int S = s.nextInt(), E = s.nextInt();
      int num = Math.min(E, b) - Math.max(S, a);
      if (num <= 0) {
        System.out.println(1);
        return;
      }
      int denom = b - a;
      logProb += Math.log(num) - Math.log(denom);
    }
    System.out.println(1 - Math.exp(logProb));
  }
}
