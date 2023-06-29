import pandas as pd

data = pd.read_csv("Paths\Path1.csv")
print(data)

while(1):
    print("Start? [j]=Ja ")
    if input() == "j":
        print("yey")
        break

for i in range(len(data)):
    testStr = 'x' + str(data.values[i][0]) + ' c' + str(data.values[i][1]) + ' z' + str(data.values[i][2]) + ' m' + str(data.values[i][3])
    print(testStr)


print(type(testStr))