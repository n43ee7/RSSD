import socket, cv2, pickle, struct
import numpy as np


# Sockets create
video_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
#host_ip = '192.168.1.254' # Jetson wlan IP address
host_ip = 'localhost'
print('HOST IP: ', host_ip)
video_port = 9999 # Assign Video stream port
video_address = (host_ip,video_port)

# Socket Bind
video_socket.bind(video_address)

# Socket listen
video_socket.listen(5)
print("LISTENING AT: ", video_address)

# socket accept
while True:
  client_socket, addr = video_socket.accept()
  print("GOT CONNECTION FROM: ", addr)
  if client_socket:
    vid = cv2.VideoCapture(1)
    while(vid.isOpened()):
      ret, frame = vid.read()
      if(ret):
        a = pickle.dumps(frame)
        message = struct.pack("Q", len(a)) + a
        client_socket.sendall(message)

      ## vvv Play video, enable only for debugging
      ## vvv (will use processing power, disable when implimenting on rover)
      #cv2.imshow('TRANSMITTING VIDEO', frame) 
      
      key = cv2.waitKey(1) & 0xFF
      if key == ord('q'):
        vid.release()
        client_socket.close()
        exit()


