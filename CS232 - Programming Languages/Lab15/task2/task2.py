import matplotlib
import random
%matplotlib inline
import numpy
import scipy
import matplotlib.pyplot as plt
import math

numdatapoints = 256
xdatapoints=range(numdatapoints)


for x in range(numdatapoints):
    xdatapoints[x]=((-1.5*math.pi)+(x*((3*math.pi)/numdatapoints)))

for x in range(numdatapoints):
    print xdatapoints[x]

sindata=range(numdatapoints)

for x in range(numdatapoints):
    sindata[x]=math.sin(xdatapoints[x])

for x in range(numdatapoints):
    print sindata[x]

plt.plot(xdatapoints,sindata)
plt.show()

noisedata=range(numdatapoints)

noise=0.5

for x in range(numdatapoints):
    noisedata[x]=((sindata[x]-noise)+random.uniform(0,(2*noise)))

for x in range(numdatapoints):
    print noisedata[x]


plt.plot(xdatapoints,noisedata)
plt.show()

smoothercurve=range(numdatapoints)
counter=0
smoothpoints=8

for y in range(numdatapoints):
    if y%smoothpoints==0:
        counter=counter+1
    
    if y!= numdatapoints:
        if y==0:
            smoothercurve[y]=noisedata[y]
        else:
            smoothercurve[y]=((noisedata[y]+noisedata[(smoothpoints*counter)-1])/2)

for z in range(numdatapoints):
    print smoothercurve[z]

plt.plot(xdatapoints,smoothercurve)
plt.show()



plt.gca().set_color_cycle(['blue', 'green', 'red'])

plt.plot(xdatapoints,sindata)
plt.plot(xdatapoints,noisedata)
plt.plot(xdatapoints,smoothercurve)


plt.legend(['Sin(X)', 'Noise', 'Smoother'], loc='upper right')

plt.show()