import java.io.*;
import java.math.*;
import java.util.*;

public class xiaowuc1_close_to_exact {
  public static void main(String[] args) throws Exception {
    Scanner sc = new Scanner(System.in);
    int n = sc.nextInt();
    int a = sc.nextInt();
    int b = sc.nextInt();
    BigInteger num = BigInteger.ONE;
    BigInteger denom = BigInteger.ONE;
    for(int i = 0; i < n; i++) {
      int lhs = sc.nextInt();
      int rhs = sc.nextInt();
      lhs = Math.max(lhs, a);
      rhs = Math.min(rhs, b);
      if(lhs > rhs) {
        System.out.println(1);
        return;
      }
      num = num.multiply(BigInteger.valueOf(rhs - lhs));
      denom = denom.multiply(BigInteger.valueOf(b - a));
    }
    num = denom.subtract(num);
    if(num.equals(BigInteger.ZERO)) {
      System.out.println(0);
      return;
    }
    System.out.println(new BigDecimal(num).divide(new BigDecimal(denom), new MathContext(1000)).toPlainString());
  }
}
