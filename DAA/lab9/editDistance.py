memo = {}


def key(n1, n2):
    return '%d,%d' % (n1, n2)


def solve(str1, str2, n1, n2):
    k = key(n1, n2)
    if k in memo:
        return memo[k]
    if n1 < 0:
        memo[k] = n2 + 1
    elif n2 < 0:
        memo[k] = n1 + 1
    elif str1[n1] == str2[n2]:
        memo[k] = solve(str1, str2, n1 - 1, n2 - 1)
    else:
        memo[k] = 1 + min(solve(str1, str2, n1, n2 - 1), solve(str1, str2, n1 - 1, n2),
                          solve(str1, str2, n1 - 1, n2 - 1))
    return memo[k]


def solve_bup(str1, str2, n1, n2):
    mem = {}
    for i in range(-1, n1 + 1):
        mem[key(-1, i)] = i + 1
    for i in range(-1, n2 + 1):
        mem[key(i, -1)] = i + 1
    for i in range(n2 + 1):
        for j in range(n1 + 1):
            if str2[i] == str1[j]:
                mem[key(i, j)] = mem[key(i - 1, j - 1)]
            else:
                mem[key(i, j)] = 1 + min(mem[key(i - 1, j)], mem[key(i, j - 1)], mem[key(i - 1, j - 1)])
    return mem[key(n2, n1)]


def main():
    str1 = 'saturday'
    str2 = 'sunday'
    print(solve(str1, str2, len(str1) - 1, len(str2) - 1))
    print(solve_bup(str1, str2, len(str1) - 1, len(str2) - 1))


if __name__ == '__main__':
    main()
