"""
Nabeel Nayyar | UTA Rover Team 2021
server.py | Target machine > N/Sp
________________________________________________________________________________________________________________________
Main purpose is to accept a stream from the host machine and display it
________________________________________________________________________________________________________________________

This script accepts two live video feeds from the Rover where first stream will be pure footage from system cameras and
the other footage is a 'post process' stream for referencing data processed by the compute algorithms.

Note:


"""

# importing dependencies
from imutils import build_montages
from datetime import datetime
import numpy as np
import imagezmq
import argparse
import imutils
import cv2

# initialize the ImageHub object
imageHub = imagezmq.ImageHub()

# start looping over all the frames
while True:
    # receive RPi name and frame from the RPi and acknowledge
    # the receipt
    (connectedNode, frame) = imageHub.recv_image()
    imageHub.send_reply(b'OK')
    # if a device is not in the last active dictionary then it means
    # that its a newly connected device
    if connectedNode not in lastActive.keys():
        print("[INFO] receiving data from {}...".format(connectedNode))
    # record the last active time for the device from which we just
    # received a frame
    lastActive[connectedNode] = datetime.now()


	# resize the frame to have a maximum width of 400 pixels, then
	# grab the frame dimensions and construct a blob
	frame = imutils.resize(frame, width=400)
	(h, w) = frame.shape[:2]
	blob = cv2.dnn.blobFromImage(cv2.resize(frame, (300, 300)),
		0.007843, (300, 300), 127.5)
	# pass the blob through the network and obtain the detections and
	# predictions
	net.setInput(blob)
	detections = net.forward()
	# reset the object count for each object in the CONSIDER set
	objCount = {obj: 0 for obj in CONSIDER}
