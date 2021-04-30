#!/usr/bin/python

import cv2

vid = cv2.VideoCapture(1) # number picks which webcam to read from
while(True):

	ret, frame = vid.read()
	if (ret):
		cv2.imshow('Video Test', frame)
	
    key = cv2.waitKey(1) & 0xFF
	if(key == ord('q')):
		vid.release()
		exit()
	
	

