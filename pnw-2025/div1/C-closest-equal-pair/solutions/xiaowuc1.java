import java.io.*;
import java.util.*;
public class xiaowuc1 {
  public static void main(String[] args) throws Exception {
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    int n = Integer.parseInt(br.readLine());
    int[] v = new int[n];
    StringTokenizer st = new StringTokenizer(br.readLine());
    for(int i = 0; i < n; i++) v[i] = Integer.parseInt(st.nextToken());
    long ret = 0;
    int[] lhs = new int[n+1];
    Arrays.fill(lhs, 1 << 30);
    int[] sta = new int[n+1];
    int[] stb = new int[n+1];
    int stsz = 0;
    sta[stsz] = -1;
    stb[stsz] = -1;
    stsz++;
    long contrib = 0;
    for(int i = 0; i < n; i++) {
      if(lhs[v[i]] < i) {
        int aval = i - lhs[v[i]];
        int bval = lhs[v[i]];
        while(aval <= sta[stsz-1]) {
          int x = sta[stsz-1];
          int idx = stb[stsz-1];
          stsz--;
          int lidx = stb[stsz-1];
          contrib -= x * (long)(idx - lidx);
        }
        if(lhs[v[i]] > stb[stsz-1]) {
          contrib += aval * (long)(lhs[v[i]] - stb[stsz-1]);
          sta[stsz] = aval;
          stb[stsz] = bval;
          stsz++;
        }
      }
      lhs[v[i]] = i;
      ret += contrib;
    }
    System.out.println(ret);
  }
}
