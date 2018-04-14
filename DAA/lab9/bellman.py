def solve(s, n, edges):
    inf = 100000
    memo = [inf] * n
    memo[s] = 0
    for _ in range(n):
        for u, v, w in edges:
            if memo[u] == inf:
                continue
            if memo[v] == inf or memo[v] > memo[u] + w:
                memo[v] = memo[u] + w
    for u, v, w in edges:
        if memo[u] == inf:
            continue
        if memo[v] == inf or memo[v] > memo[u] + w:
            return memo, True
    return memo, False


def main():
    edges = [(0, 1, -1), (0, 2, 4), (1, 2, 3), (3, 2, 5), (3, 1, -1), (1, 3, 2), (1, 4, -2), (4, 3, -3)]
    print(solve(0, 5, edges))


if __name__ == '__main__':
    main()
