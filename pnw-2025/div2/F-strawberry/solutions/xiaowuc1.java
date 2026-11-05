import java.util.*;
public class xiaowuc1 {
  public static void main(String[] args) throws Exception {
    Scanner sc = new Scanner(System.in);
    int[] appears = new int[26];
    String s = sc.next();
    for(int i = 0; i < s.length(); i++) {
      int idx = s.charAt(i) - 'r';
      if(idx < 0) idx += 26;
      appears[idx]++;
    }
    long ret = 0;
    long n = sc.nextLong();
    for(int i = 0; i < 26; i++) {
      long amt = n/26;
      if(n%26 > i) amt++;
      ret += amt * appears[i];
    }
    System.out.println(ret);
  }
}
