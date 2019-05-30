import pandas as pd
import io
import string
import csv
from random import *
csv_file1 =  open('file1.csv',mode='w') 
writer=csv.writer(csv_file1)

with open('Datafiniti_Hotel_Reviews.csv') as csv_file:
    csv_reader=csv.reader(csv_file,delimiter=',')
    for row in csv_reader:
        print(row[22])
        writer.writerow([row[22]])
with open('7282_1.csv') as csv_file:
    csv_reader=csv.reader(csv_file,delimiter=',')
    for row in csv_reader:
        print(row[17])
        writer.writerow([row[17]])
