#Author:    Allyson Warren
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

#Open file and read data
with open("CovidDeathCounts.csv") as infile:
    data = list(csv.reader(infile))

#Examine header row to find columns of interest(Ages & Deaths caused by Covid-19)
ageIndex = data[0].index("Age")
covidDeathsIndex = data[0].index("COVID-19 Deaths")


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
    print("-----------------------------------------------", file = f)
    #Print results of the average age and standard deviation
    print("The average age people die from Covid-19 is:", file = f)
    print("avg = {:0.2f}".format(averageAge), file = f)
    print("The standard deviation for this average is:", file = f)
    print("stdev = {:0.2f}\n".format(standardDeviation), file = f)
