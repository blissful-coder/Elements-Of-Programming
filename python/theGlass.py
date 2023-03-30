from tkinter import *

window = Tk()
window.title("Welcome to LikeGeeks app")
# window.attributes('-fullscreen', True)
window.wm_attributes("-transparent", True)
# Make the window window always on top
window.wm_attributes("-topmost", True)
# window.config(bg='systemTransparent')
window.attributes("-alpha", 0.5)
window.mainloop()