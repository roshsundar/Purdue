from homework2 import happybirthday
name_to_day={'Stive':24,'Bill':28,'Elon':28,'Jeff':12,'Mark':14}
name_to_month={'Stive':2,'Bill':10,'Elon':6,'Jeff':1,'Mark':5}
name_to_year={'Stive':1955,'Bill':1950,'Elon':1971,'Jeff':1964,'Mark':1984}
date_to_all = happybirthday(name_to_day, name_to_month, name_to_year)
print(date_to_all)

# answer: {24: ('Stive', (2, 1955, 67)), 28: ('Bill', (10, 1950, 72)), 12: ('Jeff', (1, 1964, 58)), 14: ('Mark', (5, 1984, 38))}