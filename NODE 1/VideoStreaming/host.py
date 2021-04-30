"""
Nabeel Nayyar | UTA Rover Team 2021
host.py | Target machine > Jetson TX2
____________________________________________________
Main purpose is to localise identified parameters
and set up socket stream for the Base Station
____________________________________________________

This script arranges two live video feeds from the Rover where first stream will be pure footage from system cameras and
the other footage is a 'post process' stream for referencing data processed by the compute algorithms/
"""

# Importing dependencies
import pyzed.sl as sl
from imutils.video import VideoStream
import imagezmq
import argparse
import socket
import time

# collect an argument and parse it
ap = argparse.ArgumentParser()
ap.add_argument("-i", "--ip", required=True, help="The IP address of the server to start the stream")
ap.add_argument("-n", "--no-ml", required=False, help="Starts a debugger session with no image computation alg")
ap.add_argument("-b", "--BLUFF", required=False, help="Creates a bluff stream instance to check IP")

args = vars(ap.parse_args())

# initialize the object with the socket address of the server to start the stream
senderObject = imagezmq.ImageSender(connect_to="tcp://{}:5555".format(args["server_ip"]))

# Create a ZED camera object
zedCamObj = sl.Camera()

# Set configuration parameters
init_params = sl.InitParameters()
init_params.camera_resolution = sl.RESOLUTION.RESOLUTION_HD1080
init_params.camera_fps = 30

# get the host name, initialize the video stream, and allow the
# camera sensor to warmup
nodeName = socket.gethostname()

# Open the camera
vs = zedCamObj.open(init_params)
# vs = VideoStream(src=0).start()    # If error remains when reaching zed cam
if vs != sl.ERROR_CODE.SUCCESS:
    print("[!] ZED Cam error upon attempt to open the camera.")
    exit(-1)

time.sleep(2.0)

while True:
    # read the frame from the camera and send it to the server
    frame = vs.read()
    senderObject.send_image(nodeName, frame)
