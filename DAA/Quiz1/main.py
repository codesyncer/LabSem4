def find(lst, low, high):
    if low > high:
        return -1
    mid = (low + high) // 2
    if lst[mid] < mid:
        return find(lst, mid + 1, high)
    if lst[mid] > mid:
        return find(lst, low, mid - 1)
    return mid


if __name__ == '__main__':
    arr = [int(inp) for inp in input("Enter A: ").split()]
    ans = find(arr, 0, len(arr) - 1)
    print("Not found!" if ans == -1 else "A[%d]= %d" % (ans, ans))
