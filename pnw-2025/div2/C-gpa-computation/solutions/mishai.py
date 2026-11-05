n = int(input())

uw = 0
w = 0
for _ in range(n):
    s = str(input())
    c = s[0]
    t = int(s[1])
    if c in "ABC":
        w += (3 - t) * 0.025
    uw += 4 - "ABCDE".find(c)
print(uw / n + w)