#Author:    Allyson Warren
#Lable:     Project 4
#Title:     Texas Population over the Years
#Course:    CMPS 4553 Computational Programming Methods
#Semester:  Fall 2021

#   This program takes a given csv file containing all
#   US states population and Total population for the
#   years 2010 to 2019. We want to view and graph the 
#   yearly populations for Texas in regards to the total
#   US population over the years. For this program, we take
#   and focus on this Texas data and get the relative population
#   for each year by dividing the Texas population by the total
#   US population for each respective year. Once we have the 
#   relative population for each year, we plot these points
#   onto a line graph in which the year is the x-axis and the
#   population is the y-axis. The graph also places a dot
#   on the given coordinates that are found within the dataframe.
#   Lastly, the program seeks out the year with the highest population
#   and then annotates this point on the graph to indicate the max of the graph.
#   All axes are labled for the graph properly and the graph is also given a title.
#   Finally the image of the graph will be saved to a pdf file to be seen clearly.
#   The data for the years and populations of Texas will also be shown in table
#   format to the console to see the specific data as well.
#---------------------------------------------------------------------------------

import matplotlib, matplotlib.pyplot as plt
import pandas as pd

# Put csv file into data frame to extract wanted information
allStates = pd.read_csv("USPopDatav3.csv",  header = 0, index_col=[0])

#Place Texas populations into own dataframe
Texas = pd.DataFrame()
#Create Column containing all years to look over
Texas['Year'] = allStates.loc['States']

#Create Column containing population of texas in relation to 
#overall US population (Texas / US pop)
Texas['Population'] = (allStates.loc['Texas'] / allStates.loc['United States'])

#Make the years into the Index for the dataframe
Texas.set_index('Year', inplace = True)

#Print out table to view dataframe
print('Texas Populations Throughout the Years Over')
print('Each Year\'s Total US Population')
#Print out new Texas Populations to the screen
print(Texas)


#Select a good-looking style
matplotlib.style.use("ggplot")
#Set the x-axis to be the Years
xdata = Texas.index
#Set the y-axis to be the relative population
ydata = Texas.loc[:, 'Population']

#Plot data as a line graph with point for given coordinates
plt.plot(xdata, ydata, '-o')

#Add annotations with arrows for highest found population
plt.annotate(text="Highest Overall Population", \
              xy=(ydata.argmax() + 2010, ydata.max()),\
              xytext=(ydata.argmax() + 2005, ydata.max()),\
              arrowprops= dict(facecolor='black', shrink=0.2))

# Add labels for both axes
plt.ylabel("Texas Population in Relation to Total US Population")
plt.xlabel("Year")
#Add Title to the graph
plt.title("Texas Population From 2010 to 2019")
#Save graph as a pdf file
plt.savefig("TexasPopGraph.pdf")