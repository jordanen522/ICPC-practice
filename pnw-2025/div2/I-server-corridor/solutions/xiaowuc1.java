import java.util.*;
public class xiaowuc1 {
  public static void main(String[] args) throws Exception {
    Scanner sc = new Scanner(System.in);
    int n = sc.nextInt();
    String s = sc.next();
    int ret = 0;
    boolean can = true;
    for(int i = 0; i < s.length(); i++) {
      if(can && s.charAt(i) == '1' && (i+1 == n || s.charAt(i+1) != '2')) {
        ret++; can = false;
      }
      else if(s.charAt(i) != '2') can = true;
      else can = false;
    }
    System.out.println(ret);
  }
}
