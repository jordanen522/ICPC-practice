import sys

input = sys.stdin.readline


def main():
    t = int(input().strip())
    for _ in range(t):
        x0, y0, x1, y1, x2, y2 = map(int, input().strip().split())

        a_lensq = x0 ** 2 + y0 ** 2
        b_lensq = (x1 - x0) ** 2 + (y1 - y0) ** 2
        c_lensq = (x2 - x0) ** 2 + (y2 - y0) ** 2

        if b_lensq > a_lensq or c_lensq > a_lensq:
            print("NO")
        elif b_lensq == a_lensq and c_lensq == a_lensq:
            print("NO")
        elif b_lensq == a_lensq and x1 - x0 == x0 and y1 - y0 == y0:
            print("NO")
        elif c_lensq == a_lensq and x2 - x0 == x0 and y2 - y0 == y0:
            print("NO")
        else:
            print("YES")


if __name__ == "__main__":
    main()
