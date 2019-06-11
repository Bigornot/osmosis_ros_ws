import matplotlib.image as mpimg
import numpy as np

tableau=open("tableau.txt","r")
ligne=[]
LX=[]
LY=[]
LN1=[]
LN2=[]


for l in tableau:
	ligne.append(l)

l1=ligne[0]
l2=ligne[1]
l3=ligne[2]
l4=ligne[3]

for el in l1.split(' '):
	LX.append(el)

for el in l2.split(' '):
	LY.append(el)

for el in l3.split(' '):
	LN1.append(el)

for el in l4.split(' '):
	LN2.append(el)


del LX[-1]
del LY[-1]
del LN1[-1]
del LN2[-1]

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

for i in range(len(LN1)):
	LN1[i]=float(LN1[i])


for i in range(len(LN1)):
	LN1[i]=int(LN1[i])-1
for i in range(len(LN2)):
	LN2[i]=int(LN2[i])-1


for i in range(len(LN1)):
	deltax=float(LX[LN2[i]]-LX[LN1[i]])
	deltay=float(LY[LN2[i]]-LY[LN1[i]])

	if deltax=0:
		a=9999999999
	else:
		a=deltay/deltax

	b=-a*LX[LN1[i]]+LY[LN1[i]]

	X=range(abs(LX[LN2[i]]-LX[LN1[i]]))
	for x in X:
		y=int(a*(x+min(LX[LN1[i]],LX[LN2[i]]))+b)
		image[y][x+min(LX[LN1[i]],LX[LN2[i]])]=(0, 0, 0)

	Y=range(abs(LY[LN2[i]]-LY[LN1[i]]))
	for y in Y:
		x=int( ( y+min(LY[LN1[i]],LY[LN2[i]]) - b)/a  )
		image[y+min(LY[LN1[i]],LY[LN2[i]])][x]=(0, 0, 0)

















mpimg.imsave("blagnac_graphe.jpg",image)
