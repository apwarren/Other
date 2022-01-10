#Author:    Allyson Warren
#Lable:     Project 1
#Title:     Wikipedia Miner
#Course:    CMPS 4553 Computational Programming Methods
#Semester:  Fall 2021

#   This program finds a particular wikipedia page from the
#   web and then filters out all undesirable information such as 
#   markup syntax. It then removes any stop words that do not
#   contribute to offering useful information before returning
#   the ten most frequent words found on the webpage. Any extra
#   forms of words are included per count as well because it counts
#   stems of words allowing for words of similar root to be grouped
#   together

import nltk
from urllib import request
from bs4 import BeautifulSoup
from collections import Counter
from nltk.corpus import stopwords
nltk.download('punkt')
nltk.download('stopwords')
nltk.download('wordnet')

#Create a new stemmer
ls = nltk.WordNetLemmatizer()

#Create mediawiki page finder for Data science
url = (
        'http://en.wikipedia.org/w/api.php?'
        '&action=query'
        '&titles=Hurricane'
        '&prop=revisions'
        '&rvprop=content'
        '&format=json'
      )

#Retrieve and read information on wikipedia page 
readURL = request.urlopen(url).read()
soup = BeautifulSoup(readURL,'html.parser')

#extract and tokenize the text
words = nltk.word_tokenize(soup.text)

#Convert all text to lower case
words = [getText.lower() for getText in words]

#eliminate stop words and stem the rest of the words
words = [ls.lemmatize(elim) for elim in words if elim not  \
               in stopwords.words("english") and elim.isalnum()]

#tally the words
freqs = Counter(words)

#Print out 10 most common words separating each on a new line to file & console
with open('WikiMinerOutput.txt', 'w') as f:
    print(*freqs.most_common(10), sep = "\n", file=f)   
    
print (*freqs.most_common(10), sep = '\n')

