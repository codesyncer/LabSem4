def solve(n, s='S', i='I', t='T'):
    if n >= 1:
        solve(n - 1, s, t, i)
        print("Move disc %d from %c to %c" % (n, s, t))
        solve(n - 1, i, s, t)


if __name__ == '__main__':
    solve(int(input("Enter number of discs: ")))
