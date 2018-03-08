def max_array(A, x, y):
    if x == y:
        return A[x], x, y
    s = [0, 0, 0]
    i = [0, 0, 0]
    j = [0, 0, 0]
    s[1], i[1], j[1] = max_array(A, x, (x + y) // 2)
    s[2], i[2], j[2] = max_array(A, 1 + (x + y) // 2, y)
    i[0], sum, max_sum = (x + y) // 2, 0, 0
    for k in range(i[0], 0, -1):
        sum += A[k]
        if max_sum < sum:
            i[0] = k
            max_sum = sum
    s[0] = max_sum
    j[0], sum, max_sum = 1 + (x + y) // 2, 0, 0
    for k in range(j[0], y, +1):
        sum += A[k]
        if max_sum < sum:
            j[0] = k
            max_sum = sum
    s[0] += max_sum
    res = s.index(max(s))
    return s[res], i[res], j[res]


if __name__ == '__main__':
    A = [-2, -3, 4, -1, -2, 1, 5, 3]
    print(max_array(A, 0, len(A) - 1))
