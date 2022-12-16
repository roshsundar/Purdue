# Homework 6: Regular Expressions
## Due: October-18.2022 at 11:59 pm ET

The length of this homework is inversely proportional to your knowledge in writing regular expressions, both for finding matches and for doing substitutions.

A good resource to use is https://regex101.com/ for checking your expressions

## Background

Please refresh your memory of regular expressions using the class notes. You may also find the Python [documentation on regular expressions](https://docs.python.org/3.6/library/re.html) useful.

A few helpful reminders: 

### Testing for Patterns

When you use `re.search` to find a regular expression match, it returns a `Match` object if the pattern exists in the string (we will see more about objects later in the semester). If *there is no match*, then `re.search` (and `re.match` and `re.findall`) will return `None`,  which you can test for:

```
p = re.compile('pattern')
if (p.search(s)) :
   # This branch will execute if the pattern is found
else :
   # this branch will execute if the pattern is *not* found
```

### Substituting with functions

A common use of `re.sub` is to substitute one string for another (remember that you can use the *groups* that you match in a pattern as part of your string substitution):

```
s = "loooool"
p = re.compile('(l)o+(l)')
p.sub(r'\1o\2', s) #replace "loooool" with "lol"
```

You can also call a method instead of providing a replacement string. This method will be called with the `Match` object corresponding to the matched string, and should return a string:

```
def replFun(m) :
   return m.group(2).upper()
s = "loooool"   
p = re.compile('(l)(o+)(l)')
m = p.search(s)
p.sub(r'\1'+replFun(m) +r'\3', s) #replace "loooool" with "lOOOOOl"
```
Remember that `(`, `)`, `-` and `.` are special characters for regular expressions. To search for those characters, you need to precede them with a backslash: `\(` `\)`, `\-`, `\.`. 

# Instructions

## 0) Set up your repository

Click the link on Piazza to set up your repository for HW 6, then clone it.

The repository should contain two files:

1. `problems.py`, the file in which you will fill in the functions for the problems. This also contains test code you can use to test your solutions.
2. This README.

## Problem 1: Regular expression matches

Congratulations! You have been hired as part of the staff to onboard new students to the new Jedi Academy on your planet. However, you have noticed that there has been a disturbance in the email list of the students. Dark forces must have added invalid emails to the list. You must create a function that can correctly identify which emails are valid. A valid email at the jedi academy has the following structure:

Fill in the function `problem1`. This function should return `True` if the input string *is a valid email address* and `False` if not. We define a valid email as follows:

1. The email **must** begin with upper or lower case letters, containing at least 1, but no more than 7 letters.
2. The email **may** have numbers from 0 up to 9999 following the letters (but **not required**).
3. The email **must** have the “@” symbol followed by jediacademy.edu
4. There **must** be nothing following the .edu

Correct Examples:
```
lskywal05@jediacademy.edu
byoda@jediacademy.edu
mwindu@jediacademy.edu
```

Incorrect Examples:
```
maul@jediacademy.eduasdf (broke rule 4)
vader99999@jediacademy.edu (breaks rule 2, too many numbers)
darthsidious@jediacademy.edu (breaks rule 1, too many letters)
r2d2@jediacademy.edu (breaks format established in 1 and 2 (has letters following numbers)
vader@sithschool.edu (breaks rule 3)
```

*ANY other format should not count as a valid email. Spaces before or after an otherwise valid email is considered invalid.*



Because we are looking for the entire string to be an email, you can either use `^` and `$` to force a match to be at the beginning and end of a string, or you can use `fullmatch` instead of `match` or `search`.

## Problem 2: Groups

Wow, there are a lot of problems on your first day, the list of students and their ships have been lost. Luckily you have some transcripts that have the students and their ships. Fill in function problem 2 to return a tuple of the student's name and the spaceship that the student drives. 

A transcript would have the format *STUDENT flies the SHIP* and will have the following conditions:

1. A ship name **must** have a hyphen in it. The characters preceding the hyphen **must** contain 1 or more capital letters
2. The students name **must** precede the word *flies* and **must** be one or two words with the first letter capitalized in each word. 
3. If the above two conditions are both not met, there is no match. You will then return a tuple of strings (“noname”, “noship”)

Example: 

`Chewbacca flies the most in his family, but Han Solo flies the YT-1300 even more.`

Although there is the phrase “Chewbacca flies the” it does not have a ship name. Therefore, your program needs to keep looking for the correct pattern. 

This pattern is found in “Han Solo flies the YT-1300”. The correct output of the problem2 would be ("Han Solo", YT-1300)




Fill in the function `problem2`. This function should search an input string for the student and ship then return a tuple of them.

`Luke Skywalker flies the X-wing`

you should return:

`(Luke Skywalker,X-wing)`

If you pass in:

`No one flies the YT-1300 like Han Solo, though Rey flies the YT-1300 very very well`

you should return:

`(Rey, YT-1300)`

*This is because No one did not have a capitalized first letter in the word preceding "flies"*

**Be careful not to return extra spaces in the return value. You may need to do a little bit of extra processing of the string captured by your group to ensure this. You will receive partial credit for having spaces. Please remove extra spaces for full credit.**

## Problem 3: Substitution
Oh no! Someone has changed these audio transcripts. Someone had replaced the title “Master” or “Darth” with "apprentice/Apprentice". Fill in the function `problem3` to returns a string with the correct title restored. 

Here are the rules for replacement
1. Apprentice should be replaced with Master if the word "Jedi" or "jedi" precedes it
2. Apprentice should be replaced with Darth if the word "Sith" or "sith" precedes it. 
3. If no match is found, return "nomatch"

Here are some examples: 

` Hello Jedi apprentice Luke! Baby Yoda is your apprentice now, teach him to be a Jedi `

*Should return*

` Hello Jedi Master Luke! Baby Yoda is your apprentice now, teach him to be a Jedi `

Your script should be able to handle the transcript with jedi and apprentice having a leading uppercase or lower case letter. However the name following "apprentice/Apprentice" will allways have a leading capital letter. 


**Be careful not to return extra spaces in the final output. You may need to do a little bit of extra processing of the string captured by your group to ensure this. You will receive partial credit for having unwanted spaces. Please remove extra spaces for full credit.**

# Testing Your Code

To test your code, run the `test_problems.py` file. These tests are not exhaustive, passing them does not guarentee full credit on the homework.

# What to Submit

Please submit `problems.py` with all the functions filled in. 

# Submitting your code

Please add, commit and push the latest version of your code, as you did in the previous HW.
Do not make any modifications to this post submission and prevent the late penalty.
