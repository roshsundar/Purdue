# Function to generate Fibonacci series up to n digits
def generate_fibonacci(n):
    fib_sequence = []
    a, b = 0, 1
    for _ in range(n + 1):
        if a != 0:
            fib_sequence.append(a)
        a, b = b, a + b
    return fib_sequence

# Get user input for the number of digits
n = int(input("How many Fibonacci numbers would you like to generate? "))

# Generate Fibonacci series
fib_series = generate_fibonacci(n)

# Print the Fibonacci series
print("The Fibonacci Sequence is:", ', '.join(map(str, fib_series)))