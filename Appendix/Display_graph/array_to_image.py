import matplotlib.image as mpimg
import numpy as np

file=open("file.txt","r")
ligne=[]
LX=[]
LY=[]
LN1=[]
LN2=[]

for l in file:
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

file.close()

for i in range(len(LX)):
	"""Conversion from coordinate to pixels
	You will have to change those formulas if you change the image,
	as resolution might not be the same. We also used a little arbitrary shift
	to reach a better precision"""
	LX[i]=int((float(LX[i])+80)*(828/160)*1.04)
for i in range(len(LY)):
	LY[i]=int((80-float(LY[i]))*(740/160)*1.15)

"""the nodes start at 1 instead of 0 so we shift it"""
for i in range(len(LN1)):
	LN1[i]=int(LN1[i])-1
for i in range(len(LN2)):
	LN2[i]=int(LN2[i])-1

"""at this point we have 4 lists to work on:
LX : [x(node1),x(node2),...](pixels)
LY : [y(node1),y(node2),...](pixels)
LN1 : [edge1_starting_node, edge2_starting_node, ... ](id of node)
LN2 : [edge1_arrival_node, edge2_arrival_node, ... ](id of node)"""


"""First we draw the graph on the image"""

image=mpimg.imread("blagnac.jpg")

#let's place the nodes on the image
for i in range(len(LX)):
	for taillex in range(10):
		for tailley in range(10):
			image[LY[i]-5+taillex][LX[i]-5+tailley]=(0, 0, 0)

#and let's trace the edges
for i in range(len(LN1)):
	deltax=float(LX[LN2[i]]-LX[LN1[i]])
	deltay=float(LY[LN2[i]]-LY[LN1[i]])

	if deltax==0:#if the slope is infinite
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
			x=int((y+min(LY[LN1[i]],LY[LN2[i]]) - b)/a  )
			image[y+min(LY[LN1[i]],LY[LN2[i]])][x]=(0, 0, 0)

mpimg.imsave("blagnac_graph.jpg",image)




"""same operations to deaw the 'abstract' map of the airport (green and red)"""


image=mpimg.imread("blagnac.jpg")

for i in range(len(image)):
	for j in range(len(image[0])):
		image[i][j]=(255,0,0)

for i in range(len(LX)):
	for taillex in range(20):
		for tailley in range(20):
			image[LY[i]-10+taillex][LX[i]-10+tailley]=(0, 255, 0)

for i in range(len(LN1)):
	LN1[i]=float(LN1[i])


for i in range(len(LN1)):
	LN1[i]=int(LN1[i])
for i in range(len(LN2)):
	LN2[i]=int(LN2[i])


for i in range(len(LN1)):
	deltax=float(LX[LN2[i]]-LX[LN1[i]])
	deltay=float(LY[LN2[i]]-LY[LN1[i]])

	if deltax==0:
		a=9999999999
	else:
		a=deltay/deltax

	b=-a*LX[LN1[i]]+LY[LN1[i]]

	X=range(abs(LX[LN2[i]]-LX[LN1[i]]))
	for x in X:
		for l in range(15):
			y=int(a*(x+min(LX[LN1[i]],LX[LN2[i]]))+b)
			if y<len(image):
				if y+l<len(image):
					if y-l>0:
						image[y-l][x+min(LX[LN1[i]],LX[LN2[i]])]=(0, 255, 0)
						image[y+l][x+min(LX[LN1[i]],LX[LN2[i]])]=(0, 255, 0)

	Y=range(abs(LY[LN2[i]]-LY[LN1[i]]))
	for y in Y:
		for l in range(15):
				x=int((y+min(LY[LN1[i]],LY[LN2[i]])-b)/a)
				if x+l<len(image[0]):
					if x-l>0:
							image[y+min(LY[LN1[i]],LY[LN2[i]])][x-l]=(0, 255, 0)
							image[y+min(LY[LN1[i]],LY[LN2[i]])][x+l]=(0, 255, 0)

mpimg.imsave("blagnac_area.jpg",image)
