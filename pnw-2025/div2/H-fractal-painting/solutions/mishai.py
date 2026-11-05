t = int(input())

for _ in range(t):
    x0, y0, x1, y1, x2, y2 = list(map(int, input().split()))
    d0 = x0**2 + y0**2
    d1 = (x1 - x0)**2 + (y1 - y0)**2
    d2 = (x2 - x0)**2 + (y2 - y0)**2
    ok = True
    if d1 == d0 and d2 == d0:
        ok = False
    if d1 > d0 or (d1 == d0 and x1 == 2 * x0 and y1 == 2 * y0):
        ok = False
    if d2 > d0 or (d2 == d0 and x2 == 2 * x0 and y2 == 2 * y0):
        ok = False
    print("YES" if ok else "NO")