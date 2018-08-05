import matplotlib
%matplotlib inline
import numpy
import scipy
import matplotlib.pyplot as plt

mydata = numpy.genfromtxt('data.txt',delimiter =',')
date=mydata[(mydata[:,4]==0),2]
temp=mydata[(mydata[:,4]==0),3]
strDate=range(len(date))
for x in range(len(date)):
    strDate[x]=str(date[x])
year=range(len(strDate))
#deciDate=range(len(strDate))
for x in range(len(strDate)):
    year[x]=int(strDate[x][0:4])
#deciDate[x]=int(strDate[x][4:8])
Dyear=year[0]
Nyear=365.0
Lyear=366.0
count=0
for x in range(len(year)):
    if Dyear==year[x]:
        if Dyear%4==0:
            count+=1
            year[x]=year[x]+count/Lyear
        else:
            count+=1
            year[x]=year[x]+count/Nyear
    else:
        Dyear=year[x]
        count=0
        if Dyear%4==0:
            count+=1
            year[x]=year[x]+count/Lyear
        else:
            count+=1
            year[x]=year[x]+count/Nyear

plt.plot(year,temp)
plt.show()