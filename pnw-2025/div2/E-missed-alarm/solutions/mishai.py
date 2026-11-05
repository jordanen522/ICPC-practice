def c(s):
    a, b = s.split(":")
    return int(a) * 60 + int(b)

print("NO" if c(input()) > c(input()) else "YES")