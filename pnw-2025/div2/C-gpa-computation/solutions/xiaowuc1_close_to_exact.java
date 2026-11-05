import java.io.*;
import java.math.*;
import java.util.*;

public class xiaowuc1_close_to_exact {
  public static void main(String[] args) throws Exception {
    Scanner sc = new Scanner(System.in);
    int n = sc.nextInt();
    BigInteger num = BigInteger.ZERO;
    BigInteger denom = BigInteger.valueOf(40*n);
    for(int i = 0; i < n; i++) {
      String s = sc.next();
      if(s.charAt(0) >= 'A' && s.charAt(0) <= 'C') {
        if(s.charAt(1) == '1') num = num.add(BigInteger.valueOf(2*n));
        if(s.charAt(1) == '2') num = num.add(BigInteger.valueOf(n));
      }
      if(s.charAt(0) == 'A') num = num.add(BigInteger.valueOf(160));
      if(s.charAt(0) == 'B') num = num.add(BigInteger.valueOf(120));
      if(s.charAt(0) == 'C') num = num.add(BigInteger.valueOf(80));
      if(s.charAt(0) == 'D') num = num.add(BigInteger.valueOf(40));
    }
    System.out.println(new BigDecimal(num).divide(new BigDecimal(denom), new MathContext(1000)).toPlainString());
  }
}
