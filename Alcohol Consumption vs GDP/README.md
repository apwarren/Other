### Author:    Allyson Warren
## GDP vs Alcohol Consumption in 2018
  
  This program takes two given csv files. The first
  contains the annual GDP of all countries from 2000-2020
  and the second contains the alcohol consumption of all
  countries during 2018. We want to strip and only keep
  the GDP data from 2018 in the first file and remove
  all other years from the dataframe and then store 
  the GDP in 2018 into a new dataframe that also 
  contains the alcohol consumption in total liters of
  pure alcohol. After both values have been stored, we
  want to calculate the mean average for both columns
  and then reassign each value to be binned as either
  above or below average. For any missing values in the 
  files, they are replaced with the discovered average to 
  not throw it off when sorting the values into above/below
  categories. After this has been done for both columns,
  We then want to compare and see how many countries have
  matching GDP vs Alcohol Consumption high or low averages. 
  We then take this amount and divide it by all countries in the 
  data to get the percentage of countries with similar data between
  the two. Lastly, we want to print out the head and tail of the data
  and show the first 10 of each to the user.
