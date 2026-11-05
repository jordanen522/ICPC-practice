import java.io.*;
import java.util.*;
public class friendships_AN2 {
  public static final int TOY_MAX = 50;
  public static void main(String[] args) throws Exception {
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    PrintWriter pw = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));
    StringTokenizer st = new StringTokenizer(br.readLine());
    int n = Integer.parseInt(st.nextToken()), q = Integer.parseInt(st.nextToken());
    int[] toys = new int[n];
    int[] totals = new int[TOY_MAX + 1];
    int[][] adjust = new int[n][TOY_MAX + 1];
    Set<Integer>[] friends = new Set[n];
    for (int i = 0; i < n; i++) {
      friends[i] = new HashSet<>();
      friends[i].add(i);
      adjust[i][0] = 1;
    }
    totals[0] = n;
    for (int i = 0; i < q; i++) {
      st = new StringTokenizer(br.readLine());
      String command = st.nextToken();
      if ("F".equals(command)) {
        int a = Integer.parseInt(st.nextToken()), b = Integer.parseInt(st.nextToken());
        a--;b--;
        friends[a].add(b);
        friends[b].add(a);
        adjust[a][toys[b]]++;
        adjust[b][toys[a]]++;
      } else if ("A".equals(command)) {
        int x = Integer.parseInt(st.nextToken());
        x--;
        for (int f : friends[x]) {
          adjust[f][toys[x]]--;
          adjust[f][toys[x] + 1]++;
        }
        totals[toys[x]]--;
        toys[x]++;
        totals[toys[x]]++;
      } else {
        int y = Integer.parseInt(st.nextToken());
        y--;
        int ans = TOY_MAX;
        while (ans >= 0 && totals[ans] - adjust[y][ans] == 0) ans--;
        pw.println(ans);
      }
    }
    pw.close();
  }
}
