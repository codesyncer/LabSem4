    from copy import deepcopy

inf = 'inf'


def solve(weight_mat):
    def decide(x, y, z):
        if x == inf or y == inf:
            return z, 1
        if z == inf:
            return x + y, 0
        if x + y < z:
            return x + y, 0
        return z, 1

    np1 = len(weight_mat)
    pre = [[[prev for _ in range(np1)] for prev in range(np1)] for _ in range(2)]
    dist = [deepcopy(weight_mat), [[inf] * np1 for _ in range(np1)]]
    for k in range(1, np1):
        kay, kay_1 = k % 2, int(not k % 2)
        for i in range(1, np1):
            for j in range(1, np1):
                dist[kay][i][j], res = decide(dist[kay_1][i][k], dist[kay_1][k][j], dist[kay_1][i][j])
                pre[kay][i][j] = pre[kay_1][i if res == 1 else k][j]
    return dist[(np1 - 1) % 2], pre[(np1 - 1) % 2]


if __name__ == '__main__':
    def main():
        dist, pre = solve([[],
                           [0, 0, inf, inf, inf, -1, inf],
                           [0, 1, 0, inf, 2, inf, inf],
                           [0, inf, 2, 0, inf, inf, -8],
                           [0, -4, inf, inf, 0, 3, inf],
                           [0, inf, 7, inf, inf, 0, inf],
                           [0, inf, 5, 10, inf, inf, 0]])
        for i in range(1, len(dist)):
            for j in range(1, len(dist)):
                print('Dist(%d,%d) = %s' % (i, j, str(dist[i][j])))
                if dist[i][j] != inf:
                    k = j
                    path = str(j)
                    while k != i:
                        path += ' >- ' + str(pre[i][k])
                        k = pre[i][k]
                    print('Path(%d,%d) = %s' % (i, j, path[::-1]))


    main()
