mkdir $1
xterm -e "rostopic echo /mission > $1/mission.txt" &
xterm -e "rostopic echo /hmi_done > $1/hmi_done.txt" &
xterm -e "rostopic echo /summit_xl_a/robotnik_base_control/cmd_vel > $1/cmd_vel.txt" &
xterm -e "rostopic echo /pose > $1/pose.txt" &
xterm -e "rostopic echo /clock > $1/clock.txt" &
