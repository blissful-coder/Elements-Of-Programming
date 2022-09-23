try:
    from AppKit import NSWorkspace
except ImportError:
    print("Can't import AppKit -- maybe you're running python from brew?")
    print("Try running with Apple's /usr/bin/python instead.")
    exit(1)

from datetime import datetime
from time import sleep
import subprocess

def exec_applescript(script):
    p = subprocess.Popen(['osascript', '-e', script],stdout=subprocess.PIPE)
    line = p.stdout.readline()
    if line:
        print(line.rstrip())

def generate_command_for_app(appName):
    command_string =  "tell application \"" + appName + "\" to get the {bounds, name}  of front window"
    slack_apps_list = ["Code", "Microsoft Teams", "Slack"]
    if(appName in slack_apps_list):
        command_string = "tell application \"System Events\" to get {position, size, name}  of every window of process \"Electron\""
    return command_string

last_active_name = None
while True:
    # active_app = NSWorkspace.sharedWorkspace().frontmostApplication().localizedName()
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

# tell application "System Events" to ¬
# 	get {position, size, name} of every window of process "Electron"

# tell application "Finder" to get the bounds of every window