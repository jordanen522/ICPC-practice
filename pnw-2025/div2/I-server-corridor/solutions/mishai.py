n = int(input())

s = str(input())
s = '0' + s + '0'

ans = 0
prevtaken = False

for i in range(1, n + 1):
    if s[i] == '1' and s[i - 1] in '01' and s[i + 1] in '01' and not prevtaken:
        ans += 1
        prevtaken = True
    elif s[i] == '2':
        prevtaken = True
    else:
        prevtaken = False
print(ans)