n = int(input())

a, b = [], []

for _ in range(n):
    x, y = list(map(int, input().split()))
    a.append(x)
    b.append(y)

ubx, uby = max(a), max(b)
lbx, lby = max(ubx - n, 1), max(uby - n, 1)

ans = 10**10

for x in range(lbx, ubx + 1):
    for y in range(lby, uby + 1):
        extra = 0
        ok = True
        currx, curry = x, y
        for i in range(n):
            if currx + extra < a[i]:
                ok = False
                break
            else:
                extra -= max(0, a[i] - currx)
                currx = max(currx, a[i])

            if curry + extra < b[i]:
                ok = False
                break
            else:
                extra -= max(0, b[i] - curry)
                curry = max(curry, b[i])

            extra += 1
        if ok:
            ans = min(ans, x + y)

print(ans)


