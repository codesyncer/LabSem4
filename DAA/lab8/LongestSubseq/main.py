memo = {}


def solve(arr, i):
    if i in memo:
        return memo[i]
    if i >= len(arr):
        return []
    max_con = []
    for j in range(i + 1, len(arr)):
        if arr[j] <= arr[i]:
            continue
        max_con = max(max_con, solve(arr, j), key=lambda lst: len(lst))
    memo[i] = [arr[i]] + max_con
    return memo[i]


def main():
    lst = [5, 2, 8, 6, 3, 6, 9, 7]
    print(solve([min(lst) - 1] + lst, 0)[1:])


if __name__ == '__main__':
    main()
