def peak(arr, low=0, high=None):
    if high is None:
        high = len(arr) - 1
    mid = (low + high) // 2
    if arr[mid - 1] < arr[mid] > arr[mid + 1]:
        return mid
    if arr[mid - 1] < arr[mid]:
        return peak(arr, mid + 1, high)
    return peak(arr, low, mid - 1)


if __name__ == '__main__':
    seq = [int(num) for num in input("Sequence: ").split()]
    print(seq[peak(seq)])
