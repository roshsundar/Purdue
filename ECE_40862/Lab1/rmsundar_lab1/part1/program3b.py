import random

num = random.randint(0, 10)

chances = 3

while chances > 0:
    guess = int(input("Enter your guess: "))
        
    if guess == num:
        print("You win!")
        break
    else:
        chances -= 1

if chances == 0:
    print(f"You lose!")
