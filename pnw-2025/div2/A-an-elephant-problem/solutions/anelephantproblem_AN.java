import java.util.*;

public class anelephantproblem_AN {
  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);
    int m = s.nextInt(), d = s.nextInt(), p = 1;
    while (m * p < d) p++;
    System.out.println(p);
  }
}
