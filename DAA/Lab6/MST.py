from DisjointSets import DisjointSets as DS


def mst(n, edges):
    weight_sum, m, tree = 0, n - 1, []
    edges.sort(key=lambda x: -x[2])
    sets = DS()
    vertices = [sets.make_set(i) for i in range(n)]
    while m > 0:
        edge = edges.pop()
        if not sets.union(vertices[edge[0]], vertices[edge[1]]):
            continue
        tree.append(edge)
        weight_sum += edge[2]
        m -= 1
    return tree, weight_sum


def main():
    sets = DS()
    edges = [
        (0, 1, 1),
        (0, 5, 2),
        (0, 6, 5),
        (1, 2, 3),
        (1, 5, 2),
        (1, 6, 3),
        (2, 6, 2),
        (2, 3, 1),
        (3, 6, 2),
        (3, 4, 1),
        (4, 5, 2),
        (4, 5, 2),
        (5, 6, 6)
    ]
    n = 7
    print(mst(n, edges))


if __name__ == '__main__':
    main()
