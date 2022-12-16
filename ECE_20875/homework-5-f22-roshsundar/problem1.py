import numpy as np
import math as m
import scipy.stats as stats
from scipy.stats import norm
from scipy.stats import t

# import or paste dataset here
myFile = open('engagement_0.txt')
data0 = myFile.readlines()
myFile.close()
data0 = [float(x) for x in data0]

myFile = open('engagement_1.txt')
data1 = myFile.readlines()
myFile.close()
data1 = [float(x) for x in data1]

# code for question 2
print('Problem 2 Answers:')
# code below this line
mu = 0.75

n = len(data0) # sample size
print('sample size: ' + str(n))

avg = np.mean(data0) # mean
print('sample mean: ' + str(round(avg, 4)))

se = np.std(data0, ddof=1) / (n ** 0.5) # standard error
print('standard error: ' + str(round(se, 4)))

z = abs((avg - mu) / se) # standard score
print('standard score: ' + str(round(z, 4)))

p = 2 * stats.norm.cdf(-abs(z))
print('p-value: ' + str(round(p, 4)))

print('')

# code for question 3
print('Problem 3 Answers:')
# code below this line

z = stats.norm.ppf(0.05/2)
z = abs(z)

# z = (avg - mu) / se -> se = (avg - mu) / z, p = z = alpha = 0.05
se_large =  (avg - mu) / z
se_large = abs(se_large)
print('largest standard error: ' + str(round(se_large, 4)))

# se = s / sqrt(n) -> s = se * sqrt(n)
s =  se * (n ** 0.5)

# se_large = s / sqrt(n) -> n = (s / se_large) ** 2
n_min = (s / se_large) ** 2
n_min = m.ceil(n_min)
print('minimum sample size: ' + str(round(n_min, 4)))

print('')

# code for question 5
print('Problem 5 Answers:')
# code below this line

n0 = len(data0) # sample size for engagement_0
n1 = len(data1) # sample size for engagement_1
print('n0: ' + str(round(n0, 4)) + ', n1: ' + str(round(n1, 4)))

x0 = np.mean(data0) # sample mean for engagement_0
x1 = np.mean(data1) # sample mean for engagement_1
print('x0: ' + str(round(x0, 4)) + ', x1: ' + str(round(x1, 4)))

sd0 = np.std(data0, ddof=1)
sd1 = np.std(data1, ddof=1)
se = (((sd0 ** 2) / n0) + ((sd1 ** 2) / n1)) ** 0.5
print('se: ' + str(round(se, 4)))

z = (x1 - x0) / se
print('z: ' + str(round(z, 4)))

p = 2 * stats.norm.cdf(-abs(z))
print('p: ' + str(round(p, 4)))