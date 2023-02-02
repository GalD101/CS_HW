def sub_groups(arr, to_return=[]):
    if (arr == []):
        return [[]]
    x = sub_groups(arr[1:]);
    return x + [[arr[0]] + y for y in x];

print(sub_groups([1, 2]))
