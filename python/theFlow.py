# Assuming Python 2.x
# For Python 3.x support change print -> print(..) and Tkinter to tkinter
from tkinter import *
import screeninfo


class theFlow(object):

    def __init__(self):
        self.root = Tk()
        self.monitor_info = screeninfo.get_monitors()
        for item in self.monitor_info:
            print(item)
        self.screen_width = self.root.winfo_screenwidth()
        self.screen_height = self.root.winfo_screenheight()
        self.canvas = Canvas(self.root,
                             width=self.screen_width,
                             height=self.screen_height,highlightthickness=0)

        self.root.wm_attributes("-topmost", True)
        self.root.wm_attributes("-transparent", True)
        self.root.config(bg='systemTransparent')
        self.root.attributes('-alpha', 0.1)
        self.canvas.pack()
        self.zone = self.canvas.create_oval(20,
                                            260,
                                            35,
                                            275,
                                            outline='black',
                                            fill='white')
        self.zonebox = []
        self.zonex = 0
        self.zoney = 0
        self.root.bind("<Button-1>", self.drawOnClick)
        self.root.mainloop()

    def prepare_canvas():
        

    def drawOnClick(self, event):
        self.zonex, self.zoney = event.x, event.y
        print('{}, {}'.format(self.zonex, self.zoney))
        current = self.canvas.coords(self.zone)
        self.canvas.move(self.zone, self.zonex - current[0] - 10,
                         self.zoney - current[1] - 10)
        self.canvas.update()

theFlow()