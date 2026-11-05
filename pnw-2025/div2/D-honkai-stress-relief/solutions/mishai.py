n, a, b = list(map(int, input().split()))

p = 1.0

for _ in range(n):
    s, e = list(map(int, input().split()))
    p *= (max(0, min(b, e) - max(a, s))) / (b - a)

print(1.0 - p)