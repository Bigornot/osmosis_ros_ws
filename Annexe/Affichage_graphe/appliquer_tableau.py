import matplotlib.image as mpimg
import numpy as np

tableau=open("tableau.txt","r")
ligne=[]
LX=[]
LY=[]

for l in tableau:
	ligne.append(l)

l1=ligne[0]
l2=ligne[1]

for el in l1.split(' '):
	LX.append(el)

for el in l2.split(' '):
	LY.append(el)

del LX[-1]
del LY[-1]


tableau.close()


for i in range(len(LX)):
	"""Calcul des coordonnees des noeuds vers pixels"""
	LX[i]=int((float(LX[i])+80)*(828/160)*1.04)
for i in range(len(LY)):
	LY[i]=int((80-float(LY[i]))*(740/160)*1.15)


image=mpimg.imread("blagnac.jpg")

for i in range(len(LX)):
	for taillex in range(10):
		for tailley in range(10):
			image[LY[i]-5+taillex][LX[i]-5+tailley]=(0, 0, 0)




mpimg.imsave("blagnac_graphe.jpg",image)

