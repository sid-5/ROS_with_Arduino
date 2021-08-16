# ROS with Arduino


# Step 1: Creating URDF files

* Start by installing the fusion2urdf plugin for Fusion 360 for converting your fusion design to URDF
*link to plugin: https://github.com/syuntoku14/fusion2urdf*
tutorial to install plugin: https://www.youtube.com/watch?v=TitHYg-5_j8
Next start desiging your bot in Fusion 360
Tutorial for simple differential bot design and URDF conversion: https://youtu.be/cQh0gNfb6ro
There are some steps missed in this tutorial due to which we require corrections in URDF file(watch this https://youtu.be/FYF1L440tdY else follow the following steps):
following are the corrections required:
Open myrobot.xacro file and navigate to REV1 joint, there replace  <axis xyz="0.0 -1.0 0.0"/>  with  <axis xyz="0.0 1.0 0.0"/>
Now open gazebo.lauch file and under "right_wheel" and "left_wheel" referenve change friction values to 150, set updateRate to 100, leftJoint to Rev2, rightJoint to Rev1, wheel seperation to 0.2, wheelDiameter to 0.1 and robotBaseFrame to base_link

# you can instead download the URDF files directly from the repo

# Step 2: Running the URDF files in Gazebo:

Copy the myrobot_description folder containing the URDF files to your (catkin workspace)/src folder
Run catkin build once to build your package
Now to run the simulation in gazebo you will find a gazebo.launch file in the myrobot_description/launch folder...(myrobot_description is the package name containing your URDF files)
To launch file use   roslauch myrobot_description gazebo.launch 
When gazebo launches remember to push the play button to run the simulation as it is paused initially(you can change the arg name="paused" value to "true" in the gazebo.launch file so that it starts automatically when you launch the simulator)
Run   rostopic list    command in terminal to check if /cmd_vel topic is present
Run teleop   rosrun teleop_twist_keyboard teleop_twist_keyboard.py    in a new terminal window(if not installed use   sudo apt-get install ros-melodic-teleop_twist_keyboard    )
Then check if the bot is moving after using the keyboard keys

# Step 3: Arduino Integration

Install rosserial_python libary
Upload code to arduino
Connect the HC-05 accordingly:
![image](https://user-images.githubusercontent.com/70048742/129587227-9842d356-7151-44ff-be08-7ff30fffed3f.png)
Now connect the app to HC-05
Run command   roslauch myrobot_description gazebo.launch   to run the robot model
Run command   rosrun rosserial_python serial_node.py _port:=/dev/ttyACM0 _baud:=57600   to start communication between ROS and Arduino(change the port number according your port)
Use to mobile app to control the bot in gazebo
