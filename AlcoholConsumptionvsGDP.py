#Author:    Allyson Warren
#Lable:     Project 3
#Title:     GDP vs Alcohol Consumption
#Course:    CMPS 4553 Computational Programming Methods
#Semester:  Fall 2021

#   This program takes two given csv files. The first
#   contains the annual GDP of all countries from 2000-2020
#   and the second contains the alcohol consumption of all
#   countries during 2018. We want to strip and only keep
#   the GDP data from 2018 in the first file and remove
#   all other years from the dataframe and then store 
#   the GDP in 2018 into a new dataframe that also 
#   contains the alcohol consumption in total liters of
#   pure alcohol. After both values have been stored, we
#   want to calculate the mean average for both columns
#   and then reassign each value to be binned as either
#   above or below average. For any missing values in the 
#   files, they are replaced with the discovered average to 
#   not throw it off when sorting the values into above/below
#   categories. After this has been done for both columns,
#   We then want to compare and see how many countries have
#   matching GDP vs Alcohol Consumption high or low averages. 
#   We then take this amount and divide it by all countries in the 
#   data to get the percentage of countries with similar data between
#   the two. Lastly, we want to print out the head and tail of the data
#   and show the first 10 of each to the user.


import pandas as pd
import numpy as np

#read csv file and set up both Alcohol Consumption and GDP Growth
GDP = pd.read_csv("GDPGrowth2000-2020.csv")
Alco2018 = pd.read_csv("Alco2018byCountry.csv")

#Set Country to be the row index
GDP = GDP.reset_index().set_index('Country')
#Remove all columns starting from Country Code to the Year 2017
GDP.drop(GDP.loc[:, 'Country Code': "2017 [YR2017]"], inplace = True, axis = 1)
#Remove columns for 2019 and 2020
GDP.drop(GDP.columns[2:], inplace = True, axis = 1)

#Remove index column from data
GDP = GDP.drop(columns=['index'], axis=1)

#Rename 2018 column for better understanding as its the only one now
GDP.rename(columns ={'2018 [YR2018]':'GDP in 2018'}, inplace=True )
GDP['GDP in 2018'] = GDP['GDP in 2018'].replace("..", 'NaN')

#Manipulate Alcohol Consumption File

#Set index of alcohol consumption to be based on country
Alco2018 = Alco2018.reset_index().set_index('Country')

#Remove all columns except country and total liters of per alcohol
Alco2018.drop(Alco2018.loc[:, 'index': "Wine"], inplace = True, axis = 1)

#Rename litres of pure alchol for clarity in merged dataframe
Alco2018.rename(columns={'total_litres_of_pure_alcohol':\
                    'Alcohol Consumption'}, inplace=True )

#make countries be completely in lower case spelling
GDP.index = GDP.index.str.lower()


#Merge GDP and Alco2018 together based on Country index
mf = pd.merge(GDP, Alco2018, on = 'Country')

#Covert All columns to numerical values
mf['GDP in 2018'] = mf['GDP in 2018'].astype(np.float64)
mf['Alcohol Consumption'] = mf['Alcohol Consumption'].astype(np.float64)

#Replace NaN values with average of column for both columns
mf.fillna((mf.mean()), inplace=True)

#Sort data by GDP column in descending order
mf.sort_values('GDP in 2018', ascending = False, inplace = True)

#Organize into two bins above average and below average for both columns
mf['GDP in 2018'] = pd.cut(mf['GDP in 2018'], 2, \
                labels = ("Below Average", "Above Average"))

mf['Alcohol Consumption'] = pd.cut(mf['Alcohol Consumption'], 2,\
                labels = ("Below Average", "Above Average"))

#Count how many times GDP and Alcohol consumption are equal in terms of average
matching_Average = (mf['GDP in 2018'] == mf['Alcohol Consumption']).sum()

#Get percentage of matching averages between GDP and Alcohol Consumption
percentage_Matched = (matching_Average / len(mf) * 100 )

#Print out percentage of countries with same above/below 
#for GDP vs Alcohol Consumption
print("The percentage of all countries GDP in 2018 being",\
      "above average at the same time its alcohol consumption",\
      "was above average is",\
      "{:.2f}%".format(percentage_Matched))
    
#Print out Top 10 countries with above average GDP
print("Top 10 countries with the highest GDP are: ")
print(mf.head(10))
print()
#Print out Top 10 countries below average GDP
print("Top 10 countries with the lowest GDP are: ")
print(mf.tail(10))
