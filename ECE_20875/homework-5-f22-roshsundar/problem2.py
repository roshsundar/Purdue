import math as m
import numpy as np
import scipy.stats as stats

# import or paste dataset here
data = [3, -3, 3, 12, 15, -16, 17, 19, 23, -24, 32, 10, -4]

# code for question 1
print('Problem 1 Answers:')
# code below this line
n = len(data)

avg = np.mean(data)
print('mean: ' + str(round(avg, 4)))

sd = np.std(data, ddof=1)
se = sd / (n ** 0.5)
print('standard error: ' + str(round(se, 4)))

t_c = stats.t.ppf(1 - (1 - 0.9)/2, n - 1)
print('t-value: ' + str(round(t_c, 4)))

l_c = avg - (t_c * se)
u_c = avg + (t_c * se)
print('(' + str(round(l_c, 4)) + ', ' + str(round(u_c, 4)) + ')')

print('')

# code for question 2
print('Problem 2 Answers:')
# code below this line
t_c = stats.t.ppf(1 - (1 - 0.95)/2, n - 1)
print('t-value: ' + str(round(t_c, 4)))

l_c = avg - (t_c * se)
u_c = avg + (t_c * se)
print('(' + str(round(l_c, 4)) + ', ' + str(round(u_c, 4)) + ')')

print('')

# code for question 3
print('Problem 3 Answers:')
# code below this line
sd = 15.836
se = sd / (n ** 0.5)
print('standard error: ' + str(round(se, 4)))

z_c = stats.norm.ppf(1 - (1 - 0.95)/2)
print('z-value: ' + str(round(z_c, 4)))

l_c = avg - (z_c * se)
u_c = avg + (z_c * se)
print('(' + str(round(l_c, 4)) + ', ' + str(round(u_c, 4)) + ')')

print('')

# code for question 4
print('Problem 4 Answers:')
# code below this line
sd = np.std(data, ddof=1)
se = sd / (n ** 0.5)

# avg - (t_c * se) = 0 -> t_c = avg / se
t_c = avg / se

p = 2 * stats.t.cdf(-abs(t_c), n - 1)
c = 1 - p
c *= 100
print('Confidence: ' + str(round(c, 4)))