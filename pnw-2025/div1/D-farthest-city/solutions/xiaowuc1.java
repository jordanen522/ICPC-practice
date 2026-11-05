import java.io.*;
import java.util.*;
public class xiaowuc1 {
  public static void main(String[] args) throws Exception {
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    PrintWriter pw = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));
    int n = Integer.parseInt(br.readLine());
    to = new int[2*n];
    weight = new int[2*n];
    nextID = new int[2*n];
    start = new int[n];
    Arrays.fill(nextID, -1);
    Arrays.fill(start, -1);
    for(int i = 0; i < n; i++) {
      StringTokenizer st = new StringTokenizer(br.readLine());
      int a = Integer.parseInt(st.nextToken())-1;
      int b = Integer.parseInt(st.nextToken())-1;
      int w = Integer.parseInt(st.nextToken());
      nextID[2*i] = start[a];
      start[a] = 2*i;
      to[2*i] = b;
      weight[2*i] = w;
      nextID[2*i+1] = start[b];
      start[b] = 2*i+1;
      to[2*i+1] = a;
      weight[2*i+1] = w;
    }
    onCycle = new boolean[n];
    Arrays.fill(onCycle, true);
    {
      int[] degree = new int[n];
      q = new int[n];
      int ql = 0, qr = 0;
      for(int i = 0; i < n; i++) {
        int curr = start[i];
        for(int id = start[i]; id != -1; id = nextID[id]) degree[i]++;
        if(degree[i] == 1) q[qr++] = i;
      }
      while(ql < qr) {
        int curr = q[ql++];
        onCycle[curr] = false;
        for(int id = start[curr]; id != -1; id = nextID[id]) {
          if(--degree[to[id]] == 1) q[qr++] = to[id];
        }
      }
    }
    long[] retq = new long[n];
    long[] disttoleaf = new long[n];
    {
      DPState lhs = new DPState(n);
      DPState rhs = new DPState(n);
      int tcn = 0;
      for(int i = 0; i < n; i++) {
        if(!onCycle[i]) continue;
        ArrayList<Integer> inComp = new ArrayList<>();
        int lleaf = bfs(++tcn, i, lhs, true, inComp);
        disttoleaf[i] = lhs.dist[lleaf];
        int rleaf = bfs(++tcn, lleaf, rhs, false, null);
        bfs(++tcn, rleaf, lhs, false, null);
        for(int out: inComp) {
          retq[out] = Math.max(retq[out], lhs.dist[out]);
          retq[out] = Math.max(retq[out], rhs.dist[out]);
        }
      }
    }
    long cycleLen = 0;
    for(int i = 0; i < n; i++) {
      if(!onCycle[i]) continue;
      for(int id = start[i]; id != -1; id = nextID[id]) {
        if(to[id] > i && onCycle[to[id]]) {
          cycleLen += weight[id];
        }
      }
    }
    long[] updist = new long[n];
    Arrays.fill(updist, -1);
    int cycleroot = 0;
    while(!onCycle[cycleroot]) cycleroot++;
    for(int uid = start[cycleroot]; uid != -1; uid = nextID[uid]) {
      int orientv = to[uid];
      if(!onCycle[orientv]) continue;
      ArrayList<Integer> cycleOrd = new ArrayList<>();
      ArrayList<Long> distOnCycle = new ArrayList<>();
      cycleOrd.add(cycleroot);
      distOnCycle.add(0L);
      int curr = orientv;
      long currd = weight[uid];
      int par = cycleroot;
      int seen = 0;
      while(true) {
        distOnCycle.add(currd);
        cycleOrd.add(curr);
        if(curr == cycleroot) {
          if(++seen == 2) break;
        }
        int nv = -1, nw = -1;
        for(int id = start[curr]; id != -1; id = nextID[id]) {
          int candv = to[id];
          if(!onCycle[candv] || candv == par) continue;
          nv = candv;
          nw = weight[id];
          break;
        }
        par = curr;
        curr = nv;
        currd += nw;
      }
      int lhs = 0;
      MaxQueue maxq = new MaxQueue(4*n);
      maxq.push(disttoleaf[cycleroot]);
      for(int i = 1; i < cycleOrd.size(); i++) {
        while(2 * (distOnCycle.get(i) - distOnCycle.get(lhs)) > cycleLen) {
          maxq.pop();
          lhs++;
        }
        if(maxq.size() > 0) {
          updist[cycleOrd.get(i)] = Math.max(updist[cycleOrd.get(i)], distOnCycle.get(i) + maxq.maxpeek());
        }
        maxq.push(disttoleaf[cycleOrd.get(i)] - distOnCycle.get(i));
      }
    }
    {
      DPState downdp = new DPState(n);
      for(int i = 0; i < n; i++) {
        if(!onCycle[i]) continue;
        downdp.dist[i] = updist[i];
        downdp.cn[i] = i;
        int ql = 0, qr = 0;
        q[qr++] = i;
        while(ql < qr) {
          int curr = q[ql++];
          retq[curr] = Math.max(retq[curr], downdp.dist[curr]);
          for(int id = start[curr]; id != -1; id = nextID[id]) {
            int nv = to[id];
            if(onCycle[nv]) continue;
            if(downdp.cn[nv] != i) {
              downdp.cn[nv] = i;
              downdp.dist[nv] = downdp.dist[curr] + weight[id];
              q[qr++] = nv;
            }
          }
        }
      }
    }
    for(int i = 0; i < n; i++) {
      if(i > 0) pw.print(' ');
      pw.print(retq[i]);
    }
    pw.println();
    pw.close();
  }

  static int[] to, weight, nextID, start;
  static int[] q;
  static boolean[] onCycle;

  private static int bfs(int tcn, int src, DPState dp, boolean fill, ArrayList<Integer> inComp) {
    dp.dist[src] = 0;
    dp.cn[src] = tcn;
    int ql = 0, qr = 0;
    q[qr++] = src;
    int ret = -1;
    long bestdist = -1;
    while(ql < qr) {
      int curr = q[ql++];
      if(fill) inComp.add(curr);
      if(dp.dist[curr] > bestdist) {
        bestdist = dp.dist[curr];
        ret = curr;
      }
      for(int id = start[curr]; id != -1; id = nextID[id]) {
        int nv = to[id];
        if(onCycle[nv] && onCycle[curr]) continue;
        if(dp.cn[nv] != tcn) {
          dp.cn[nv] = tcn;
          dp.dist[nv] = dp.dist[curr] + weight[id];
          q[qr++] = nv;
        }
      }
    }
    return ret;
  }

  static class DPState {
    long[] dist;
    int[] cn;
    DPState(int n) {
      dist = new long[n];
      cn = new int[n];
      Arrays.fill(cn, -1);
    }
  }

  static class MaxQueue {
    long[] q, maxq;
    int ql, qr, maxql, maxqr;
    MaxQueue(int n) {
      q = new long[4*n];
      maxq = new long[4*n];
      ql = 0;
      qr = 0;
      maxql = 0;
      maxqr = 0;
    }
    void push(long x) {
      q[qr++] = x;
      while(maxqr > maxql && maxq[maxqr-1] < x) maxqr--;
      maxq[maxqr++] = x;
    }
    long pop() {
      long curr = q[ql++];
      if(maxq[maxql] == curr) maxql++;
      return curr;
    }
    long maxpeek() {
      return maxq[maxql];
    }
    int size() {
      return qr - ql;
    }
  }
}
