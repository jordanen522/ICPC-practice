import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.util.*;

public class kthking_AN2 {
  public static void main(String[] args) throws Exception {
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    PrintWriter pw = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));
    int n = Integer.parseInt(br.readLine());
    long[] arr = new long[n];
    for (int i = 0; i < n; i++) arr[i] = Integer.parseInt(br.readLine());
    Arrays.sort(arr);
    long[] prefix = new long[n];
    prefix[0] = arr[0];
    for (int i = 1; i < n; i++) prefix[i] = prefix[i - 1] + arr[i];
    for (int i = 0; i < n - 1; i++) {
      int hi = n - i - 1;
      int mid = (n - i) / 2;
      long median = arr[mid];
      long loShift = mid * median - prefix[mid - 1];
      long hiShift = prefix[hi] - prefix[mid] - (hi - mid) * median;
      pw.println(loShift + hiShift);
    }
    pw.println(0);
    pw.close();
  }
}
