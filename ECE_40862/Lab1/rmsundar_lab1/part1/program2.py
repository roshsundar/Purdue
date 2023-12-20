a = [1, 1, 2, 3, 5, 8, 13, 21, 34, 55]

print("a =", a)

inp_number = int(input("Enter number: "))

a = [num for num in a if num < inp_number]

print("The new list is", a)
