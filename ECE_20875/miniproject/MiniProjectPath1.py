import pandas

'''
The following is the starting code for path1 for data reading to make your first step easier.
'dataset_1' is the clean data for path1.
'''
dataset_1 = pandas.read_csv('NYC_Bicycle_Counts_2016_Corrected.csv')
dataset_1['Brooklyn Bridge']      = pandas.to_numeric(dataset_1['Brooklyn Bridge'].replace(',','', regex=True))
dataset_1['Manhattan Bridge']     = pandas.to_numeric(dataset_1['Manhattan Bridge'].replace(',','', regex=True))
dataset_1['Queensboro Bridge']    = pandas.to_numeric(dataset_1['Queensboro Bridge'].replace(',','', regex=True))
dataset_1['Williamsburg Bridge']  = pandas.to_numeric(dataset_1['Williamsburg Bridge'].replace(',','', regex=True))
dataset_1['High Temp']            = pandas.to_numeric(dataset_1['High Temp'].replace(',','', regex=True))
dataset_1['Low Temp']             = pandas.to_numeric(dataset_1['Low Temp'].replace(',','', regex=True))
dataset_1['Precipitation']        = pandas.to_numeric(dataset_1['Precipitation'].replace(',','', regex=True))
dataset_1['Total']                = pandas.to_numeric(dataset_1['Total'].replace(',','', regex=True))
# print(dataset_1.to_string()) #This line will print out your data
