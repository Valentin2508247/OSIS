
from tkinter import *
import random
import time
import threading

class Config:
    def __init__(self, stopped=False):
        self.stopped = stopped

config = Config()

def start_threads():
    config.stopped = False
    thread_1 = threading.Thread(target=change_color, args=(1,)).start()
    thread_2 = threading.Thread(target=change_color, args=(2,)).start()
    thread_3 = threading.Thread(target=change_color, args=(3,)).start()
    thread_4 = threading.Thread(target=change_color, args=(4,)).start()

def stop_threads():
    config.stopped = True

def change_color(index):
    if index == 1:
        square = square_1
    if index == 2:
        square = square_2
    if index == 3:
        square = square_3
    if index == 4:
        square = square_4

    colors = ["red", "green", "blue", "yellow", "orange", "lime", "brown", "black", "white", "pink", "cyan", "magenta", "silver", "maroon", "olive", "aqua", "teal", "navy", "fuchsia", "purple"]

    while True:
        if config.stopped:
            break
        color = colors[round(random.uniform(0, len(colors) - 1))]
        canvas.itemconfig(square, fill=color)
        time.sleep(1)




# main window properties;
root = Tk()
root.title("lab11")
root.geometry("1000x500")

root.resizable(0, 0)

# canvas properties;
canvas = Canvas(root, width=1000, height=450)
canvas.pack()
square_1 = canvas.create_polygon((0, 0), (250, 0), (250, 450), (0, 450), fill="red")
square_2 = canvas.create_polygon((250, 0), (500, 0), (500, 450), (250, 450), fill="green")
square_3 = canvas.create_polygon((500, 0), (750, 0), (750, 450), (500, 450), fill="blue")
square_4 = canvas.create_polygon((750, 0), (1000, 0), (1000, 450), (750, 450), fill="yellow")



# buttons properties;
button_add = Button(text="ADD", command=start_threads, width=500)
button_add.pack(side=LEFT)
button_clear = Button(text="CLEAR", command=stop_threads, width=500)
button_clear.pack(side=LEFT)

# start window;
root.mainloop()
