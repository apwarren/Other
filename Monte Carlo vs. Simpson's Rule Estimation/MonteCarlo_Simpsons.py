#Author:    Allyson Warren
#Lable:     Project 5
#Title:     Estimating Integration using Simpson's Rule and Monte Carlo Method
#Course:    CMPS 4553 Computational Programming Methods
#Semester:  Fall 2021

#   This program uses two approximation algorithms used for finding
#   the area under a curve, the Simpson's Rule and the Monte Carlo Method. The 
#   Simpson's rule takes interval sections of the desired function and computes
#   the function's width. It then divides the width by 3 and multiplies it
#   by the sum of the function's starting postion + 4* the interval's results + the
#   function of the ending position. This results in an estimated value of the 
#   length of the desired curve. Next, the Monte Carlo method uses random points
#   plotted onto the graph to find the area under the curve. The graph ranges from
#   the staring and ending x-axis which is 0-2 for all functions in the program.
#   Then as all functions we want to find the average of are increasing functions,
#   the max height of the graph can be found to be the ending x-value's respective
#   function result. The y-axis will start at 0 as well. Then after creating this
#   boundary for the graph, the program generates randome points on the graph within
#   the boundary. If a point is found to be on or below its respective x-value's y
#   function, it is added to a counter in order to found how many points are under
#   the curve. Then this count is divided by the total amount of points plotted onto
#   the graph in order to obtain a percentage. Finally, this count is multiplied by
#   the area of the boundary in order to gain an estimated area to be found under
#   the curve. Fornthis program, x^2 and x^4 are used to determine their area from
#   0-2. After both methods have been used for both functions, their graphs are
#   printed to a pdf with proper labels, with each graph showing the interval points
#   for Simpson's rule, random plots for Monte Carlo method, and the line of the
#   actual function to be integrated.
#---------------------------------------------------------------------------------

import numpy as np
import matplotlib, matplotlib.pyplot as plt
import random as rand

# Select a good-looking style
matplotlib.style.use("ggplot")

plt.axis([0, 5, 0, 30])
#Create four different graphs on one file
figure, axis = plt.subplots(1,2)
figure.tight_layout()

#Simpson's Composite Rule:
#interval values (Range goes from 0 to 2 for both functions)
a = 0
b = 2
#number of intervals
n = 11
#Compute width
h = (b - a) / (n - 1)
#Return evenly spaced numbers over a specified interval.
x = np.linspace(a, b, n)
#Get function for first function x squared
firstFunction = x ** 2
#Get function for second function x ^ 4
secondFunction = x ** 4

#Compute Composite Simpson for x squared
C_simp_x2 = (h/3) * (firstFunction[0] + 2*sum(firstFunction[:n-2:2])\
     + 4*sum(firstFunction[1:n-1:2]) + firstFunction[n-1])

#Compute Composite Simpton for x ^ 4
C_simp_x4 = (h/3) * (secondFunction[0] + 2*sum(secondFunction[:n-2:2])\
     + 4*sum(secondFunction[1:n-1:2]) + secondFunction[n-1])

#Add x^2 and x^4 to the graphs and state which graph is which
axis[0].set_title('Graph for x^2', fontsize = 8)
axis[0].scatter(x, firstFunction, color = 'b')
axis[1].set_title('Graph for x^4', fontsize = 8)
axis[1].scatter(x, secondFunction, color = 'b')

#--------------------------------------------------------
#Compute using Monte Carlo Method for both x^2 and x^4

#number of random points to Generate
N = 5000
#initialize count of points inside
countx2 = 0
countx4 = 0
#No points have been placed yet
xlist = np.empty((0, 0))
ylist = np.empty((0, 0))

#generate points and count inside
for i in range (N):
  x = rand.uniform(0, 2)    #X values should range from 0 to 2
  y = rand.uniform(0, 4)    #Y values should range from 0 to 2^2
  val = x**2        #Put the x value into the function to get its actual y value

  if y < val:               #Point is under the curve
    countx2 += 1            #Add to counter as point is under curve

  #Add to list of x and y values to plot onto graph
  xlist = np.append(xlist, x)
  ylist = np.append(ylist, y)

#Plot all random points onto graph
axis[0].scatter(xlist, ylist, s=2)

#Create and plot actual line of the function x^2 onto the graph
f2 = np.empty((0,0))         
x2 = np.linspace(0, 2, 100)
for x in x2:
  f2 = np.append (f2, x**2)

#Actual line curve is shown as a green color
axis[0].plot(x2, f2,  color='g')

#-------
#Reset points for next function x^4
xlist = np.empty((0, 0))
ylist = np.empty((0, 0))

#generate points and count inside
for i in range (N):
  x= rand.uniform(0, 2)     #X values should range from 0 to 2
  y= rand.uniform(0, 16)    #Y values should range from 0 to 2^4
  val = x**4       #Put the x value into the function to get its actual y value

  if y < val:               #Point is under the curve
    countx4 += 1            #Add to counter as point is under curve

  #Add to list of x and y values to plot onto graph
  xlist = np.append(xlist, x)
  ylist = np.append(ylist, y)

#Plot all random points used to determine x^4 area under curve
axis[1].scatter(xlist, ylist, s=2)
f2 = np.empty((0,0))
x2 = np.linspace(0, 2, 100)
for x in x2:
  f2 = np.append (f2, x**4)

#Actual line curve is shown in green
axis[1].plot(x2, f2,  color='g')

#Print estimated results for both functions to the user to view
print ("Estimate of x^2 on interval [", a, ",", b, "]")
print("Computed using Simpson's Composite Rule:")
print("Estimate of x^2 is ~ " , C_simp_x2)
print('------------')
print('Computed using Monte Carlo Method:')
print ("Esimate of x^2 is", 8*countx2/N)    #Area of 2x(2^2) = 8
print('------------')
print ("Actual Result of x^2 is ", 2.66666666666667, "...")
print('-------------------------------------------------------')
print ("Integral of f(x) = x ^ 4 on interval [", a, ",", b, "]")
print("Computed using Simpson's Composite Rule:")
print("Result ~ " , C_simp_x4)
print('------------')
print('Computed using Monte Carlo Method:')
print ("Esimate of x^4 is", 32*countx4/N)   #Area of 2*(2^4) = 32
print('------------')
print ("Actual Result of x^4 is ", 6.4)

#Add and show both graph in a pdf
plt.savefig("Simpsons_&_MonteCarlo_Functions.pdf")