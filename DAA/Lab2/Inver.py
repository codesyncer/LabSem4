def naive(arr):
    n = len(arr)
    count = 0
    for i in range(n - 1):
        for j in range(i + 1, n):
            if arr[i] > arr[j]:
                count += 1
    return count


def count_split_inversions(arr, i, j, tmp_arr):
    li = i
    ln = (j + i) // 2
    ri = ln + 1
    rn = j
    cnt = 0
    while li <= ln and ri <= rn:
        if arr[li] < arr[ri]:
            tmp_arr[li] = arr[li]
            li += 1
        else:
            tmp_arr[ri] = arr[ri]
            ri += 1
            cnt += ln - li + 1
    while li <= ln:
        tmp_arr[li] = arr[li]
        li += 1
    while ri <= rn:
        tmp_arr[ri] = arr[ri]
        ri += 1
    for k in range(i, j + 1):
        arr[i] = tmp_arr[i]
    return cnt


def count_inversions(arr, i=0, j=None, tmp_arr=None):
    if j is None:
        j = len(arr) - 1
        tmp_arr = [None] * len(arr)
    return 0 if i >= j else count_inversions(arr, i, (j + i) // 2, tmp_arr) + \
                            count_inversions(arr, (j + i) // 2 + 1, j, tmp_arr) + \
                            count_split_inversions(arr, i, j, tmp_arr)


if __name__ == '__main__':
    seq = [int(num) for num in input("Sequence: ").split()]
    # print(naive(seq))
    print(count_inversions(seq))
