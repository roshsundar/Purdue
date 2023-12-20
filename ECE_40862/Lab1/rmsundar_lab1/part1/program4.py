birthday_dict = {
    "Albert Einstein": "03/14/1879",
    "Benjamin Franklin": "01/17/1706",
    "Ada Lovelace": "12/10/1815",
    "Isaac Newton": "01/04/1643",
    "Marie Curie": "11/07/1867"
}

print("Welcome to the birthday dictionary. We know the birthdays of:")
for name in birthday_dict:
    print(name)

name = input("Whose birthday do you want to look up?\n")

if name in birthday_dict:
    birthday = birthday_dict[name]
    print(f"{name}'s birthday is {birthday}.")