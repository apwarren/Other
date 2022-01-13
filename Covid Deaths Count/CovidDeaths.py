#Author:    Allyson Warren
#Lable:     Homework 3
#Title:     Covid Deaths Avg Age & StdDev
#Course:    CMPS 4553 Computational Programming Methods
#Semester:  Fall 2021

#   This program takes a given csv file separated by commas and then
#   traverses through and finds the ages and Covid-19 deaths to be used
#   to calculate the average age that people die from covid and what
#   this average's standard deviation would be. Both results are printed
#   to an output file. 


import csv
import math
import numpy as np
import matplotlib, matplotlib.pyplot as plt

#Select a good-looking style for plotting
matplotlib.style.use("ggplot")

#Open file and read data
with open("CovidDeathCounts.csv") as infile:
    data = list(csv.reader(infile))

#Examine header row to find columns of interest(Ages & Deaths caused by Covid-19)
ageIndex = data[0].index("Age")
covidDeathsIndex = data[0].index("COVID-19 Deaths")

#Get all ages being considered for covid deaths
ages = [row[ageIndex] for row in data[1:(len(data) // 2) + 1] if float(row[ageIndex]) % 5 == 0 ]

#Get all covid deaths for females separated by age
femaleCovidDeaths = [row[covidDeathsIndex] for row in data[1:(len(data) // 2) + 1]]
        
#Get all covid deaths for males separated by age
maleCovidDeaths = [row[covidDeathsIndex] for row in data[(len(data) // 2) + 1 : ]]

#Sum up and group age deaths by 5
groupedFemCovidDeaths = [0] * len(ages)
groupedMaleCovidDeaths = [0] * len(ages)

for val in range(len(femaleCovidDeaths)):
    groupedFemCovidDeaths[val // 5] += float(femaleCovidDeaths[val])
    groupedMaleCovidDeaths[val // 5] += float(maleCovidDeaths[val])

#Determine Average Age for Deaths Caused by Covid
#--------------------------------------------------------------------
#   To get this average, we first multiply each age by how many people of that
#   age died from Covid-19 in order to get each age's frequency and then
#   divide the sum of all of these frequencies by how many people total
#   have died from Covid-19
#--------------------------------------------------------------------

#Get how many people of a particular age died
covidDeathPerAge = [(float(row[ageIndex]) * float(row[covidDeathsIndex])) 
                                                        for row in data[1:]]
#Get how many people total died
totalCovidDeaths = [float(row[covidDeathsIndex]) for row in data[1:]]

#Get the average age for people who have died from Covid
averageAge = sum(covidDeathPerAge) / sum(totalCovidDeaths)

#Determine Standard Deviation
#--------------------------------------------------------------------
#   To determine the standard deviation for the average, we take each
#   age and subtract it from the average found. The difference is then
#   squared and multiplied by the current age's amount of Covid-19 deaths.
#   Once each age has been calculated like this, we take the sum of all 
#   of them and divide it by one less than the total Covid-19 deaths. 
#   The standard deviation can now be calculated by taking the square root
#   of this result.
#--------------------------------------------------------------------

#Find the difference in each age compared to the average and then 
# use the difference to get the death frequency for each one
standardNumerator = [((float(row[ageIndex])  - averageAge) ** 2) *
                        float(row[covidDeathsIndex]) for row in data[1:]]
#The denominator is the total deaths caused by Covid - 1
standardDenominator = sum(totalCovidDeaths) - 1

#The standard deviation takes the square root of the freqency of deaths 
# per age difference sums / total death- 1
standardDeviation = math.sqrt(sum(standardNumerator) / standardDenominator)
#--------------------------------------------------------------------

#Print output Header and results found to two decimal places
with open('CovidDeathOutput.txt', 'w') as f:
    #Header
    print("Allyson Warren", file=f)
    print("9/14/2021" , file = f)
    print("Homework 3: Covid Deaths Avg Age & StdDev", file = f)
    print("CMPS 4553 Computational Programming Methods", file = f)
    print("-----------------------------------------------", file = f)
    #Print results of the average age and standard deviation
    print("The average age people die from Covid-19 is:", file = f)
    print("avg = {:0.2f}".format(averageAge), file = f)
    print("The standard deviation for this average is:", file = f)
    print("stdev = {:0.2f}\n".format(standardDeviation), file = f)

  
X_axis = np.array(ages, dtype = int)

f, (ax, ax2) = plt.subplots(2, 1, sharex=True)

#Cut out middle of bar graphs to make for better readability
ax.set_ylim(12000, groupedFemCovidDeaths[-1]) #Top of data  
ax2.set_ylim(0, 8000) #Lower part of data

ax.bar(X_axis - 1, groupedFemCovidDeaths, 2, label = 'Females')
ax.bar(X_axis + 1, groupedMaleCovidDeaths, 2, label = 'Males')
  
ax2.bar(X_axis - 1, groupedFemCovidDeaths, 2, label = 'Females')
ax2.bar(X_axis + 1, groupedMaleCovidDeaths, 2, label = 'Males')
 
# hide the spines between ax and ax2
ax.spines['bottom'].set_visible(False)
ax2.spines['top'].set_visible(False)
ax.xaxis.tick_top()
ax.tick_params(labeltop=False)  
# don't put tick labels at the top
ax2.xaxis.tick_bottom()

#Make tick marks where ages are on graph for x-axis
plt.xticks(np.arange(0, int(ages[-1]) + 1, step = 5))

plt.xlabel("Ages")
plt.ylabel("Total Covid Deaths", loc = 'center')
ax.set_title("Number of Covid Deaths per Age")
ax.legend()
#Save graph as a pdf file
plt.savefig("CovidDeathsGraph.pdf")