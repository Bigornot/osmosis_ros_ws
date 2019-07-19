import matplotlib.image as mpimg
import numpy as np
import json

graph=open("../../ressources/blagnac.graph","r")
data=""
for l in graph:
	data=data+l

obj=json.loads(data)
graph.close()

LX=[]
LY=[]
LN1=[]
LN2=[]

for node in obj["nodes"]:
	LX.append(node["x"])
	LY.append(node["y"])
for edge in obj["edges"]:
	LN1.append(int(edge[0][1:]))
	LN2.append(int(edge[1][1:]))

for i in range(len(LX)):
	"""Conversion from coordinate to pixels
	You will have to change those formulas if you change the image,
	as resolution might not be the same. We also used a little arbitrary shift
	to reach a better precision on the blagnac image"""
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


#Then we draw the graph on the image
image=mpimg.imread("../../ressources/blagnac.jpg")

#let's place the nodes on the image
for i in range(len(LX)):
	for sizex in range(10):
		for sizey in range(10):
			image[LY[i]-5+sizex][LX[i]-5+sizey]=(0, 0, 0)

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

mpimg.imsave("../osmosis_simulation/models/blagnac.jpg",image)
