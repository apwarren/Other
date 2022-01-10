### Author: Allyson Warren
##  Estimating Integration using Simpson's Rule and Monte Carlo Method

This program uses two approximation algorithms used for finding
the area under a curve, the Simpson's Rule and the Monte Carlo Method. The 
Simpson's rule takes interval sections of the desired function and computes
the function's width. It then divides the width by 3 and multiplies it
by the sum of the function's starting postion + 4* the interval's results + the
function of the ending position. This results in an estimated value of the 
length of the desired curve. Next, the Monte Carlo method uses random points
plotted onto the graph to find the area under the curve. The graph ranges from
the staring and ending x-axis which is 0-2 for all functions in the program.
Then as all functions we want to find the average of are increasing functions,
the max height of the graph can be found to be the ending x-value's respective
function result. The y-axis will start at 0 as well. Then after creating this
boundary for the graph, the program generates randome points on the graph within
the boundary. If a point is found to be on or below its respective x-value's y
function, it is added to a counter in order to found how many points are under
the curve. Then this count is divided by the total amount of points plotted onto
the graph in order to obtain a percentage. Finally, this count is multiplied by
the area of the boundary in order to gain an estimated area to be found under
the curve. Fornthis program, x^2 and x^4 are used to determine their area from
0-2. After both methods have been used for both functions, their graphs are
printed to a pdf with proper labels, with each graph showing the interval points
for Simpson's rule, random plots for Monte Carlo method, and the line of the
actual function to be integrated.
