import sys
input = sys.stdin.readline

n = int(input())

c = [int(input()) for _ in range(n)]
c.sort()

lsum, rsum = 0, 0
anss = [0]

for i in range(1, n):
    if i % 2 == 1:
        lsum += c[i // 2]
        rsum += c[i]
    else:
        rsum += c[i] - c[i // 2]
    anss.append(rsum - lsum)

anss = list(map(str, anss[::-1]))
print("\n".join(anss))
