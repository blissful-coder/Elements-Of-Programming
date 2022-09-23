# Import the required libraries
try:
    from AppKit import NSWorkspace
except ImportError:
    print("Can't import AppKit -- maybe you're running python from brew?")
    print("Try running with Apple's /usr/bin/python instead.")
    exit(1)

from datetime import datetime
from time import sleep
import subprocess
from tkinter import *
import threading

last_active_name = None

def exec_applescript(script):
    p = subprocess.Popen(['osascript', '-e', script], stdout=subprocess.PIPE)
    line = p.stdout.readline()
    if line:
        print(line.rstrip())


def generate_command_for_app(appName):
    command_string = "tell application \"" + appName + "\" to get the {bounds, name}  of front window"
    slack_apps_list = ["Code", "Microsoft Teams", "Slack"]
    if (appName in slack_apps_list):
        command_string = "tell application \"System Events\" to get {position, size, name}  of every window of process \"Electron\""
    return command_string

def bounding_info():
    global last_active_name
    active_app = NSWorkspace.sharedWorkspace().activeApplication()
    if active_app['NSApplicationName'] != last_active_name:
        last_active_name = active_app['NSApplicationName']
        print("-------------------------------")
        print('%s: %s [%s]' % (
            datetime.now().strftime('%Y-%m-%d %H:%M:%S'),
            active_app['NSApplicationName'],
            active_app['NSApplicationPath']
        ))
        command_for_bounds = generate_command_for_app(active_app['NSApplicationName'])
        print(command_for_bounds)
        exec_applescript(command_for_bounds)

def move_ball():
    global xspeed, yspeed
    root.update()
    canvas.move(ball, xspeed, yspeed)
    (leftpos, toppos, rightpos, bottompos) = canvas.coords(ball)
    if leftpos <= 0 or rightpos >= 700:
        xspeed = -xspeed
    if toppos <= 0 or bottompos >= 350:
        yspeed = -yspeed

    canvas.after(30, move_ball)

# Create an instance of tkinter frame or window
root = Tk()
# Set the size of the window
screen_width = root.winfo_screenwidth()
screen_height = root.winfo_screenheight()
# root.attributes('-fullscreen',True)
# root.overrideredirect(True)
# Make the root window always on top
root.wm_attributes("-topmost", True)
# Turn off the window shadow
root.wm_attributes("-transparent", True)
# Set the root window background color to a transparent color
root.config(bg='systemTransparent')
root.attributes('-alpha', 0.4)
# root.wm_attributes("-transparentcolor", "white")
# Create a canvas widget
canvas = Canvas(root,
                width=screen_width,
                height=screen_height,
                highlightthickness=0)
canvas.pack()

# Create an oval or ball in the canvas widget
ball = canvas.create_oval(10, 10, 50, 50, fill="green3")
active_rect = canvas.create_rectangle(100, 100, 200, 200, fill="blue")
print(active_rect)
# Move the balls
xspeed = yspeed = 3
canvas.after(0, move_ball)
root.mainloop()