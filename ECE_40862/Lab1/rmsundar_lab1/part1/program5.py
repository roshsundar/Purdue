class SumNums:
    def __init__(self, nums):
        self.nums = nums
        self.map = {}

    def find_indices(self, target):
        for i, num in enumerate(self.nums):
            complement = target - num
            if complement in self.map:
                return [self.map[complement], i]
            self.map[num] = i

nums = [10, 20, 10, 40, 50, 60, 70]
two_sum_finder = SumNums(nums)

target = int(input("What is your target number? "))

result = two_sum_finder.find_indices(target)
if result:
    index1, index2 = result
    print(f"index1={index1}, index2={index2}")