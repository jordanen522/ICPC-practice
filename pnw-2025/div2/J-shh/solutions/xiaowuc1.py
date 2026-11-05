WANT = "shh"
MOD = 67

def get_next(s):
  for length in range(min(len(s), len(WANT)), 0, -1):
    if s[-length:] == WANT[:length]:
      return length
  return 0

def main():
  n, k = map(int, input().split())
  s = input().strip()

  INF = 1 << 25
  dp = [[[INF, 0] for _ in range(3)] for _ in range(k + 1)]
  dp[0][0][0] = 0
  dp[0][0][1] = 1

  for i in range(n):
    ndp = [[[INF, 0] for _ in range(3)] for _ in range(k + 1)]
    for a in range(k + 1):
      for b in range(3):
        if dp[a][b][0] == INF:
          continue
        have = WANT[:b]
        for c in map(chr, range(ord('a'), ord('z') + 1)):
          nhave = have + c
          na = a
          nb = get_next(nhave)
          nchange = dp[a][b][0]
          if c != s[i]:
            nchange += 1
          nways = dp[a][b][1]
          if nb == 3:
            na += 1
            nb = 0
          if na <= k:
            if nchange < ndp[na][nb][0]:
              ndp[na][nb][0] = nchange
              ndp[na][nb][1] = 0
            if nchange == ndp[na][nb][0]:
              ndp[na][nb][1] += nways
    dp = ndp

  minchange = INF
  minways = 0
  for i in range(3):
    if dp[k][i][0] < minchange:
      minchange = dp[k][i][0]
      minways = 0
    if dp[k][i][0] == minchange:
      minways += dp[k][i][1]
  print(minchange, minways % MOD)

if __name__ == "__main__":
  main()
