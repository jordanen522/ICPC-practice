n, t = list(map(int, input().split()))

a = list(map(int, input().split()))
a.sort()
dp = [1 for _ in range(n)]
for i in range(1, n):
    for j in range(i - 1, -1, -1):
        if a[i] - a[j] >= t:
            dp[i] = dp[j] + 1
            break

print(max(dp))
