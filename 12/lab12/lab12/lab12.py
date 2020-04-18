
from tkinter import *
import threading
import time

def start_threads():
    thread_1 = threading.Thread(target=change_color, args=(1,)).start()
    thread_2 = threading.Thread(target=change_color, args=(2,)).start()
    thread_3 = threading.Thread(target=change_color, args=(3,)).start()

def change_color(index):
    colors = ["blue", "yellow", "black"]
    lock = threading.Lock()

    while True:
        lock.acquire()
        canvas.itemconfig(square_1, fill=colors[index - 1])
        time.sleep(1)
        lock.release()


root = Tk()
root.title("lab12")
root.geometry("1000x500")
root.resizable(0, 0)

canvas = Canvas(root, width=1000, height=500)
canvas.pack()
square_1 = canvas.create_polygon((0, 0), (1000, 0), (1000, 500), (0, 500), fill="white")

start_threads()

# start window;
root.mainloop()
