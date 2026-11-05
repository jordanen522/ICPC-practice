n, m, MOD = map(int, input().split())

if n > m:
    n, m = m, n

n -= 1
m -= 1

dp = [[0, 0] for _ in range(n+1)]
dp[0][0] = 1

for ln in range(1, n + m + 1):
    ndp = [[0, 0] for _ in range(n+1)]
    for b in range(0, n + 1):
        if b > 0:
            ndp[b][1] = (ln + 1) * (dp[b-1][0] + dp[b-1][1]) % MOD
        ndp[b][0] = ((ln + 1) * dp[b][0] + dp[b][1]) % MOD

    dp, ndp = ndp, dp

print((dp[n][0] + dp[n][1]) % MOD)