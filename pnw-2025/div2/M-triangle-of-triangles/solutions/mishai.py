t = int(input())

for _ in range(t):
    a1, b1, c1 = list(map(int, input().split()))
    a2, b2, c2 = list(map(int, input().split()))
    a3, b3, c3 = list(map(int, input().split()))

    ok = False

    for a, b, c in [(a1, b1, c1), (b1, c1, a1), (c1, a1, b1)]:
        for ap, bp, cp in [(a2, b2, c2), (b2, c2, a2), (c2, a2, b2), (a2, c2, b2), (b2, a2, c2), (c2, b2, a2),
                           (a3, b3, c3), (b3, c3, a3), (c3, a3, b3), (a3, c3, b3), (b3, a3, c3), (c3, b3, a3)]:
            for app, bpp, cpp in [(a2, b2, c2), (b2, c2, a2), (c2, a2, b2), (a2, c2, b2), (b2, a2, c2), (c2, b2, a2),
                               (a3, b3, c3), (b3, c3, a3), (c3, a3, b3), (a3, c3, b3), (b3, a3, c3), (c3, b3, a3)]:
                if ap + app == a and bp + bpp == 180 and cp == b and cpp == c:
                    ok = True
    if ok:
        print("YES")
    else:
        print("NO")