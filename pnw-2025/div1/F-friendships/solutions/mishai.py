import sys
input = sys.stdin.readline

n, q = list(map(int, input().split()))

anss = []
glb = [0 for _ in range(51)]
glb[0] = n
own = [0 for _ in range(n+1)]
toys = [[0 for _ in range(51)] for _ in range(n+1)]
friends = [[] for _ in range(n+1)]

for _ in range(q):
    s = str(input())
    if s[0] == 'F':
        i, j = list(map(int, s[2:].split()))
        i-=1
        j-=1
        toys[i][own[j]]+=1
        toys[j][own[i]]+=1
        friends[i].append(j)
        friends[j].append(i)
    elif s[0] == 'A':
        i = int(s[2:])
        i-=1
        for friend in friends[i]:
            toys[friend][own[i]]-=1
            toys[friend][own[i]+1]+=1
        glb[own[i]]-=1
        glb[own[i]+1]+=1
        own[i]+=1
    else:
        j = int(s[2:])
        j-=1
        for i in range(50, -1, -1):
            val = glb[i] - toys[j][i] - (own[j] == i)
            if val > 0:
                anss.append(str(i))
                break
        else:
            anss.append("-1")

print("\n".join(anss))
