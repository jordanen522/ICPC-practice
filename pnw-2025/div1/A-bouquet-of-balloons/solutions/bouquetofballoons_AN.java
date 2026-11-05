import java.util.*;

public class bouquetofballoons_AN {
  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);
    int n = s.nextInt();
    long d = s.nextLong(), m = s.nextLong();
    long target = m * d;
    int[] arr = new int[n];
    for (int i = 0; i < n; i++) arr[i] = s.nextInt();
    Arrays.sort(arr);
    int ans = 0;
    int time = 0;
    long accum = 0;
    while (ans < n && time < d) {
      accum += d - time;
      time += arr[ans];
      ans++;
      if (accum >= target) {
        System.out.println(ans);
        return;
      }
    }
    System.out.println(-1);
  }
}
