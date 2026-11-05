import java.util.*;

public class gpacomputation_AN {
  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);
    int n = s.nextInt();
    double points = 0;
    double bonus = 0;
    for (int i = 0; i < n; i++) {
      String grade = s.next();
      points += 'E' - grade.charAt(0);
      if (grade.charAt(0) <= 'C') {
        bonus += (0.025) * ('3' - grade.charAt(1));
      }
    }
    System.out.println(bonus + points / n);
  }
}
