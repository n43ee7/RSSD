import time
import threading
from tkinter import *
from tkinter import ttk
from tkinter.ttk import *
import serial

serial_data = ''
filter_data = ''
update_period = 1
serial_object = None
gui = Tk()
gui.title("UTA RoverTeam | Serial Profiler")


def connect():
    version_ = button_var.get()
    print("Connection Sucess: " + str(version_))
    global serial_object
    port = port_entry.get()
    baud = baud_entry.get()

    try:
        if version_ == 2:
            try:
                serial_object = serial.Serial('/dev/tty' + str(port), baud)

            except:
                print("Cant Open Specified Port")

        elif version_ == 1:
            serial_object = serial.Serial('COM' + str(port), baud)

    except ValueError:
        print("Enter Baud and Port")
        return

    t1 = threading.Thread(target=get_data)
    t1.daemon = True
    t1.start()


def get_data():  # Serial Read failed
    global serial_object
    global serial_data

    while (1):
        try:
            serial_data = str(serial_object.readline()).strip('\r').strip('\n')
            print("RX: " + serial_data)

        except TypeError:
            print("RX ERR")
            pass


def update_gui():
    global serial_data
    global update_period

    new = time.time()

    while 1:
        if serial_data:

            node1.insert(END, serial_data)
            node1.insert(END, "\n")
            node1.pack()
            try:
                print("RX NULL")


            except:
                pass

            if time.time() - new >= update_period:
                node1.delete("1.0", END)
                new = time.time()


def send():
    send_data = data_entry.get()

    if not send_data:
        print("NULL Value not cast")

    serial_object.write(str.encode(send_data))
    print("TX: " + send_data)


def disconnect():  # Successful release of port and exit
    try:
        serial_object.close()

    except AttributeError:
        print("Disconnected")

    gui.quit()


if __name__ == "__main__":
    l0 = Label(text="Node 1 Serial monitor: ").place(x=15, y=5)
    node1 = Text(gui, width=59, height=13).place(x=15, y=25)

    l01 = Label(text="Node 2 Serial monitor: ").place(x=600, y=5)
    node2 = Text(width=59, height=13).place(x=600, y=25)

    # threads
    t2 = threading.Thread(target=update_gui)
    t2.daemon = True
    t2.start()

    # Labels



    l10 = Label(text="Cast a Serial Message:").place(x=15, y=225)  # N1
    baud = Label(text="Baud").place(x=100, y=348)
    port = Label(text="Port").place(x=200, y=348)
    data5 = Label(text="Connection Configuration").place(x=15, y=290)

    l11 = Label(text="Cast a Serial Message:").place(x=600, y=225)  # N2
    baud1 = Label(text="Baud").place(x=700, y=348)
    port1 = Label(text="Port").place(x=800, y=348)
    data51 = Label(text="Connection Configuration").place(x=600, y=290)

    # Entry
    data_entry = Entry(width=65)  # N1
    data_entry.place(x=80, y=253)
    baud_entry = Entry(width=7)
    baud_entry.place(x=100, y=365)
    port_entry = Entry(width=7)
    port_entry.place(x=200, y=365)

    data_entry1 = Entry(width=65)  # N2
    data_entry1.place(x=680, y=253)
    baud_entry1 = Entry(width=7)
    baud_entry1.place(x=700, y=365)
    port_entry1 = Entry(width=7)
    port_entry1.place(x=800, y=365)

    # radio button
    button_var = IntVar()  # N1
    radio_1 = Radiobutton(text="Windows", variable=button_var, value=1).place(x=10, y=325)
    radio_2 = Radiobutton(text="Linux", variable=button_var, value=2).place(x=110, y=325)

    # button
    button1 = Button(text="Send", command=send, width=6).place(x=15, y=250)
    connect = Button(text="Connect", command=connect).place(x=15, y=360)
    disconnect = Button(text="Disconnect", command=disconnect).place(x=15, y=390)

    # mainloop
    gui.geometry('1100x450')
    gui.mainloop()
