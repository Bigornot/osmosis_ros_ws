#!/usr/bin/env python
import rospy
import rospkg
from std_msgs.msg import Bool
from geometry_msgs.msg import Pose2D
import matplotlib.image as mpimg

fault_injection=False

def drive():

    if len(image)>0 and len(image[0])>0 :
        print("Image opened")

    rospy.spin()

def poseCallback(data):
    # Converting pose in pixels
    X=int( (80+float(data.x)) * (828/160) * 1.04)
    Y=int( (80-float(data.y)) * (740/160) * 1.15)


    if int(image[Y][X][0]) > 250 :
	print("Couleur :", int(image[Y][X][0]), image[Y][X][1], image[Y][X][2], "TRUE")
        pub.publish(True)

    else :
        print("Couleur :", int(image[Y][X][0]), image[Y][X][1], image[Y][X][2], "FALSE")
        print(fault_injection)
        if fault_injection==True:
            pub.publish(True)
            print("saltations")
        else:
            pub.publish(False)

def activationCallback(data):
    global fault_injection
    fault_injection=data.data
    print(fault_injection)


rospack = rospkg.RosPack()
path = rospack.get_path('osmosis_control')
path += "/../../ressources/blagnac_area.jpg"
image = mpimg.imread(path)
rospy.init_node('checkProhibitedArea_node')
rospy.Subscriber("/pose", Pose2D, poseCallback)
pub = rospy.Publisher('inProhibitedArea', Bool, queue_size=10)



#fault injection
rospy.Subscriber("/activate_DM1", Bool, activationCallback)


if __name__ == '__main__':
    try:
        drive()
    except rospy.ROSInterruptException:
        pass
