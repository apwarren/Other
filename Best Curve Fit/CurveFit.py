#Author:    Allyson Warren
#Lable:     Project 6
#Title:     Finding the Curve Fit of a scatter plot
#Course:    CMPS 4553 Computational Programming Methods
#Semester:  Fall 2021

#   This program tries to find the best fit of a curve using two/three
#   different models that plot the best curve fit and then are compared to 
#   determine which had the closest value to the true value of defects. The
#   first and third file of data are compared using the Go S_Shaped Model and
#   the Goel-Okumoto Model and both model fits are plotted onto a graph to show
#   what their fits visually. The second file also both of these models, but it
#   is also fitted with another model called the Yamada model to see which of these
#   is closest to the true value of the graph. The models are then used to each 
#   predict the outcome of a given x variable. Each model's prediction is also 
#   graphed. After finding the best fit curve for each model, the program then
#   determines which one had the better fit and then states who it was and was 
#   their fit was determined to be. After this, the program will lastly print 
#   out what the true value was in the end.
#---------------------------------------------------------------------------------

import numpy as np
import matplotlib, matplotlib.pyplot as plt
from scipy.optimize import curve_fit

matplotlib.style.use("ggplot")

#Define GO S-Shaped Model (GO-S)
def GO_S(t, a, b):
    return a*(1-((1+(b*t))*np.exp(-b*t)))

#Define Goel Okumoto Model (GO)
def GO(t, a, b):
    return a * (1-np.exp(-b*t))
    
#Define Yamada Model
def Yamada(t, a, bc, d):
  return a * (1- np.exp(-bc * (1-np.exp(-d*t))))

#------------
#Code for srgm1.txt

#get the data and do an indirect sort on the indices of the data along the x axis
my_data = np.genfromtxt('srgm1.txt', delimiter=' ')
my_data = my_data[my_data[:,0].argsort()]

#make it 1xN data instead of Nx1
xdata = my_data[:,0].transpose()
ydata = my_data[:,1].transpose()

a_guess = ydata[-1]
b_guess = .01

#make an initial guess for a, b
init_vals = [a_guess, b_guess]

# fit your data and getting fit parameters
popt, pcov = curve_fit(GO_S, xdata, ydata, p0=init_vals, \
                bounds=([a_guess, b_guess], [1000, 1]))

#Print out a_guess value and the score of the curve
GO_S_score = popt
print('The score of the GO-S Model is:', popt)

# predict new data for an x-value based on the fit
x_guess = 30
y_pred = GO_S(x_guess, *popt)
print("Prediction of GO-S: (", x_guess, ',', y_pred, ")")

#plot the data
plt.title("SRGM1")
plt.plot(xdata, ydata, 'bo', label='data')
plt.plot(xdata, GO_S(xdata, *popt), '-', label='GO-S Data')
plt.scatter ([x_guess], [y_pred], color = 'red')

#Get data for the GO Model curve fit and then state its score
popt, pcov = curve_fit(GO, xdata, ydata, p0=init_vals, \
                        bounds=([a_guess, b_guess], [1000, 1]))
print('The score of the GO Model is:', popt)
GO_score = popt

#Predict the value of the new x-value based on the fit for GO
y_pred = GO(x_guess, *popt)
print("Prediction of GO: (", x_guess, ',', y_pred, ")")
plt.plot(xdata, GO(xdata, *popt), '-', label='GO Data')
plt.scatter ([x_guess], [y_pred], color = 'teal')

#Print which of the two models had the best fit score
if(GO_S_score[-1] >= GO_score[-1]):
    print("The SRGM Model with the best score was the Go S-Shaped Model.\
             Its score was:", GO_S_score[-1])
    print('It predicted that the true value for srgm1 is\
             {:0.2f}'.format(GO_S_score[0]))

else:
    print("The SRGM Model with the best score was the Goel-Okumoto Model.\
             Its score was:", GO_score[-1])
    print('It predicted that the true value for srgm1 is\
             {:0.2f}'.format(GO_score[0]))

#Print out the actual true value for the srgm
print("The actual true value of srgm1 is", 231)

#label plot
plt.xlabel('x = Time (t)')
plt.ylabel('y = Cumulative Defects')
plt.legend()
#save the plot
plt.savefig("Curve1.pdf")
#------------
print()
print('--------------------------------------------------------------')
print()
plt.clf()
plt.cla()
plt.close()


#------------
#Code for srgm2.txt

#get the data and do an indirect sort on the indices of the data along the x axis
my_data = np.genfromtxt('srgm2.txt', delimiter=' ')
my_data = my_data[my_data[:,0].argsort()]

#make it 1xN data instead of Nx1
xdata = my_data[:,0].transpose()
ydata = my_data[:,1].transpose()

a_guess = ydata[-1]
b_guess = .01

#make an initial guess for a, b
init_vals = [a_guess, b_guess]

# fit your data and getting fit parameters
popt, pcov = curve_fit(GO_S, xdata, ydata, p0=init_vals, \ 
                        bounds=([a_guess, b_guess], [1000, 1]))
#Print out a_guess value and the score of the curve
GO_S_score = popt
print('The score of the GO-S Model is:', popt)

# predict new data for an x-value based on the fit for Go S-Shaped
x_guess = 30
y_pred = GO_S(x_guess, *popt)
print("Prediction of GO-S: (", x_guess, ',', y_pred, ")")

#plot the data
plt.title("SRGM2")
plt.plot(xdata, ydata, 'bo', label='data')
plt.plot(xdata, GO_S(xdata, *popt), '-', label='GO-S Data')
plt.scatter ([x_guess], [y_pred], color = 'red')

#Get data for the GO Model curve fit
popt, pcov = curve_fit(GO, xdata, ydata, p0=init_vals, \
                    bounds=([a_guess, b_guess], [1000, 1]))
print('The score of the GO Model is:', popt)
GO_score = popt

# predict new data for an x-value based on the fit for Goel-Okumoto model
y_pred = GO(x_guess, *popt)
print("Prediction of GO: (", x_guess, ',', y_pred, ")")
plt.plot(xdata, GO(xdata, *popt), '-', label='GO Data')
plt.scatter ([x_guess], [y_pred], color = 'teal')


#make an initial guess for a, bc, and d for the Yamada model
init_vals = [a_guess, 0, b_guess]

#Get data for the Yamada Model curve fit
popt, pcov = curve_fit(Yamada, xdata, ydata, p0=init_vals, \
                bounds=([a_guess, 0, b_guess], [1000, 1000, 1]))
print('The score of the Yamada Model is:', popt)
Yam_score = popt

# predict new data for an x-value based on the fit for Yamada
y_pred = Yamada(x_guess, *popt)
print("Prediction of Yamada: (", x_guess, ',', y_pred, ")")
plt.plot(xdata, Yamada(xdata, *popt), '-', label='Yamada Data')
plt.scatter ([x_guess], [y_pred], color = 'purple')

#Print which of the two models had the best fit score
if(GO_S_score[-1] >= GO_score[-1] and [-1] >= Yam_score[-1]):
    print("The SRGM Model with the best score was the Go S-Shaped Model.\
             Its score was:", GO_S_score[-1])
    print('It predicted that the true value for srgm2 is \
        {:0.2f}'.format(GO_S_score[0]))

elif(GO_score[-1] >= Yam_score[-1]):
    print("The SRGM Model with the best score was the Goel-Okumoto Model.\
         Its score was:", GO_score[-1])
    print('It predicted that the true value for srgm2 is\
             {:0.2f}'.format(GO_score[0]))

else:
    print("The SRGM Model with the best score was the Yamada Model.\
             Its score was:", Yam_score[-1])
    print('It predicted that the true value for srgm2 is \
            {:0.2f}'.format(Yam_score[0]))

#Print out the actual true value for the srgm
print("The actual true value of srgm2 is", 245)

#label plot
plt.xlabel('x = Time (t)')
plt.ylabel('y = Cumulative Defects')
plt.legend()
#save the plot
plt.savefig("Curve2.pdf")
#------------

print()
print('--------------------------------------------------------------')
print()
plt.clf()
plt.cla()
plt.close()
#------------
#Code for srgm2.txt

#get the data and do an indirect sort on the indices of the data along the x axis
my_data = np.genfromtxt('srgm3.txt', delimiter=' ')
my_data = my_data[my_data[:,0].argsort()]

#make it 1xN data instead of Nx1
xdata = my_data[:,0].transpose()
ydata = my_data[:,1].transpose()

a_guess = ydata[-1]
b_guess = .01

#make an initial guess for a, b, c, d
init_vals = [a_guess, b_guess]

# fit your data and getting fit parameters
popt, pcov = curve_fit(GO_S, xdata, ydata, p0=init_vals, \
            bounds=([a_guess, b_guess], [1000, 1]))
#Print out a_guess value and the score of the curve
GO_S_score = popt
print('The score of the GO-S Model is:', popt)

# predict new data for an x-value based on the fit for GO-S
x_guess = 30
y_pred = GO_S(x_guess, *popt)
print("Prediction of GO-S: (", x_guess, ',', y_pred, ")")

#plot the data
plt.title("SRGM3")
plt.plot(xdata, ydata, 'bo', label='data')
plt.plot(xdata, GO_S(xdata, *popt), '-', label='GO-S Data')
plt.scatter ([x_guess], [y_pred], color = 'red')

#Get data for the GO Model curve fit
popt, pcov = curve_fit(GO, xdata, ydata, p0=init_vals, \
        bounds=([a_guess, b_guess], [1000, 1]))
print('The score of the GO Model is:', popt)
GO_score = popt

# predict new data for an x-value based on the fit for the GO model
y_pred = GO(x_guess, *popt)
print("Prediction of GO: (", x_guess, ',', y_pred, ")")
plt.plot(xdata, GO(xdata, *popt), '-', label='GO Data')
plt.scatter ([x_guess], [y_pred], color = 'teal')

#Print which of the two models had the best fit score
if(GO_S_score[-1] >= GO_score[-1]):
    print("The SRGM Model with the best score was the Go S-Shaped Model.\
             Its score was:", GO_S_score[-1])
    print('It predicted that the true value for srgm3 is\
             {:0.2f}'.format(GO_S_score[0]))
else:
    print("The SRGM Model with the best score was the Goel-Okumoto Model. \
            Its score was:", GO_score[-1])
    print('It predicted that the true value for srgm3 is \
            {:0.2f}'.format(GO_score[0]))

#Print out the actual true value for the srgm
print("The actual true value of srgm3 is", 83)

#label plot
plt.xlabel('x = Time (t)')
plt.ylabel('y = Cumulative Defects')
plt.legend()
#save the plot
plt.savefig("Curve3.pdf")
#------------
