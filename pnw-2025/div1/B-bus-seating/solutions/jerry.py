n, k, m, c = map(int, input().split())
fav = list(map(int, input().split()))

bits = [[0]*n for i in range(30)]
rbits = [[0]*n for i in range(30)]
tot = [0]*30
tot[0] = n

def add(layer, ind, val):
    global bits, n, rbits
    tind = ind
    ind += 1
    while ind <= n:
        bits[layer][ind-1] += val
        ind += ind&-ind

    ind = n-1-tind
    ind += 1
    while ind <= n:
        rbits[layer][ind-1] += val
        ind += ind&-ind

def query(layer, ind):
    ind += 1
    out = 0
    while ind:
        out += bits[layer][ind-1]
        ind ^= ind&-ind
    return out

for i in range(n):
    add(0, i, 1)

def get(layer, ind):
    global tot, n, c, bits, rbits
    before = 0 if ind == 0 else query(layer, ind-1)
    mult = 1<<(30-layer)

    ret = (-1, -1)
    if tot[layer] == before and before == 0:
        return ret

    above = tot[layer] - before
    if above != 0:
        cur = -1
        ctot = 0
        for i in range(20, -1, -1):
            if cur + (1<<i) >= n:
                continue
            if ctot + rbits[layer][cur+(1<<i)] < above:
                cur += (1<<i)
                ctot += rbits[layer][cur]
        ans = n-1-cur
        ans -= 1

        cost = c - abs(ans - ind)
        cost *= mult
        if ret[1] < cost:
            ret = (ans, cost)
        elif ret[1] == cost and ret[0] > ans:
            ret = (ans, cost)

    if before != 0:
        cur = -1
        ctot = 0
        for i in range(20, -1, -1):
            if cur + (1<<i) >= n:
                continue
            if ctot + bits[layer][cur+(1<<i)] < before:
                cur += (1<<i)
                ctot += bits[layer][cur]
        ans = cur+1
        cost = c - abs(ans - ind)
        cost *= mult
        if ret[1] < cost:
            ret = (ans, cost)
        elif ret[1] == cost and ret[0] > ans:
            ret = (ans, cost)
    return ret

out = []
for p in fav:
    p -= 1
    place = (-1, -1)
    lay = -1

    while tot[0] == 0:
        t = bits[0]
        t2 = rbits[0]
        for j in range(29):
            bits[j] = bits[j+1]
            rbits[j] = rbits[j+1]
            tot[j] = tot[j+1]
        bits[29] = t
        rbits[29] = t2
        tot[29] = 0
        k -= 1

    for layer in range(min(30, k)):
        if tot[layer] == 0:
            continue
        pl, amt = get(layer, p)
        if pl == -1:
            continue
        if place[1] < amt:
            place = (pl, amt)
            lay = layer
        elif place[1] == amt and place[0] > pl:
            place = (pl, amt)
            lay = layer
        
    out.append(place[0]+1)
    tot[lay] -= 1
    add(lay, place[0], -1)
    if lay+1 < min(30, k):
        tot[lay+1] += 1
        add(lay+1, place[0], 1)

print(*out)

