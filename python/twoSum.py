def twoSum(nums, target):
    # print(nums)
    # print(target)
    numMap = {}
    for i, num in enumerate(nums):
        numMap[num] = i
    
    # print(numMap)
    for i, num in enumerate(nums):
        complement = target - num
        if complement in numMap and numMap[complement] != i:
            # print(i)
            # print(numMap[complement])
            return [i, numMap[complement]]
    return []

a = [2,7,4,3]
t = 9

ans = twoSum(a,t)
print(ans)