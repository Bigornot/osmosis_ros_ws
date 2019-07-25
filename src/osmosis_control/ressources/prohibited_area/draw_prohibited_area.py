import matplotlib.image as mpimg
import numpy as np
import json

graph_path = "../graph/blagnac.graph"
image_path = "blagnac.jpg"
image_prohibited_area = "blagnac_area.jpg"

graph=open(graph_path,"r")
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


"""let's draw the 'abstract' map of the airport (green and red)"""

image=mpimg.imread(image_path)

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

mpimg.imsave(image_prohibited_area,image)
