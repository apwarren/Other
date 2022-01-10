#Author:    Allyson Warren
#Lable:     Project 2
#Title:     State to State Similarity Calculator
#Course:    CMPS 4553 Computational Programming Methods
#Semester:  Fall 2021

#   This program takes a given csv file separated by commas that
#   contains the total US population's current and previous
#   year's residencies change within each state. It then 
#   looks at each state's overall residency change and 
#   divides each value by 51 to get the average change
#   between all 50 states and Washington DC. It then 
#   Compares each state's average change in residency 
#   with its residency change by every other state. If 
#   the average change in residency is greater than 
#   the state to state change in residency, then it 
#   is considered that the state's change is not similar.
#   After determining which State to State similarities exist,
#   We then print out the largest State Change populations and
#   what state the change is from to what state people are moving to.

import csv
import numpy as np

with open("StateData.csv", 'r') as infile:
    StatePopulation = list(csv.reader(infile, delimiter = ','))

#----------------State X Data---------------------
#Get average number of people who have moved out of State X per state

#Get row containing how many people of each state had a different state 
# of residence (Value is still a string at the moment)
StateX = StatePopulation[4][5:]
#Remove commas from large values to just get the number
StateX = [row.replace(',','') for row in StateX]

#Convert Total State Residency change to array
StateX = np.array(StateX, dtype = float)

#Get each State's total difference by dividing by all states + DC 
# (This is the X state to compare with)
StateX = np.floor_divide(StateX, 50)


#----------------State Y Data---------------------
#Get Number of People who have moved from State X to State Y

#Get Current Residence State Differences for all Y States
StateY = [row[5:] for row in StatePopulation[5:]]
#Remove commas from large numbers to just get the number
StateY = [[col.replace(',', '') for col in row] for row in StateY]
#Replace Any missing (N/A) values with 0 as State X will always be bigger than 0
StateY = [[col.replace("N/A", "0") for col in row] for row in StateY]

#Store All Y State Values into a 2D array 
StateY = np.array(StateY, dtype = float)


#------------Compare State X to State Y----------

#Determine and only keep values in which State Y's value is greater
#  than its respective State X value
StateDifferences = []
#Perform Comparison between X and Y states. Only keep values in which 
# State Y is bigger than State X
for row in StateY:
        StateDifferences.append(np.where(row > StateX, row, 0))


#Convert the State to State Similarites to array to get its 
# greatest using array methods
StateDifferences = np.array(StateDifferences, dtype = float)


#Print out 10 largest State to State similarities & change current 
# greatest to 0 after its printed
print("\nThe 10 lagrest State to State Similarities are:")
print("---------------------------------------------------\n")

for greatest in range(0, 10):
      #Get largest change in residency population out of all states
    LargestSimilarity = int(np.amax(StateDifferences))
    
      #Get index of largest State to State Residency Change
    index = np.unravel_index(StateDifferences.argmax(), StateDifferences.shape)
    indexStateX = index[1] + 5
    indexStateY = index[0] + 5
    
    #Get which state people are leaving from
    previousState = StatePopulation[indexStateX][0]
    #Get which state people are moving to
    currentState = StatePopulation[indexStateY][0]
    #Print out the residency change going from StateX to StateY
    print(greatest+1)
    print(previousState , " to ", currentState)
    
    #Print out the total state similarity of residency change 
    # from StateX to StateY with formatting
    print("State Similarity is: {:,}".format(LargestSimilarity))
    StateDifferences[index[0]][index[1]] = 0
       
    print()


