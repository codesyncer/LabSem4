def swap(A, i, j):
    tmp = A[i]
    A[i] = A[j]
    A[j] = tmp


def median5(A, i):
    x = sorted(A[i:i + 5])
    return x[len(x) // 2]


def approx_median(A, i, j):
    lst = []
    for k in range(i, j + 1, 5):
        lst.append(median5(A, k))
    return select(lst, 0, len(lst) - 1, len(lst) // 2)


def partition(A, i, j, x):
    l = []
    ge = []
    for k in range(i, j + 1):
        if A[k] < x:
            l.append(A[k])
        else:
            ge.append(A[k])
    res = l + ge
    A[i:j + 1] = res
    return len(l)


def select(A, i, j, k):
    if j - i + 1 <= 5:
        return median5(A, i)
    x = approx_median(A, i, j)
    p = partition(A, i, j, x)
    if k == p - i + 1 + 1:
        return x
    if p - i + 1 >= k:
        return select(A, i, p, k)
    return select(A, p + 1, j, k - (p - i + 1 + 1))


if __name__ == '__main__':
    A = [1, 5, 2, 5, 3, 6, 3, 7, 3, 8, 2, 9, 4, 2]
    print(select(A, 0, len(A) - 1, len(A) // 2))
