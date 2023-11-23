from PIL import Image, ImageTk
import pytesseract
import tkinter as tk
from tkinter import filedialog
from tkinter.filedialog import askopenfile


textdata='''
1 LAL MIRCH PAN 1 325.00 325.00
2 GUNTOOR CHICK 1 385.00 385.00
MEXICAN FRIES 1 250.00 250.00
RANCH BBQ CHI 4 385.00 1540.00
MUTTON CHETTI 2 450.00 900.00
ROSEMARRY MAR 1 375500 375.00
CAJUN CHATPAT 1 245,00 245.00
CHEESY VEG NA 1 260.00 260.00
MURGH KEEMAN 1 310.00 310.00
1OBBQ CHICKEN P 1 450.00 450.00
11PERI PERI ONT 1 215.00 215.00
12KAFIR GINGER 2 225.00 450.00
13SPRITE 2 65.00 130.00
14GINGER ALE 1110.00 110.00
15B0TTLED WATER 5 60.00 300.00
16LONG ISLAND I 3 515.00 1545.00
170LD FASHIONED 5 415.00 2075.00
18WHISKY SOUR 3 415.00 1245.00
19BACARDI ORANG 4 220.00 880.00
20KF ULTRA TOWR 21850.00 3700.00

Total Amount 15690.00
SERC@10 1569.00
State GST@2.59% 181 95
Central GsT@2.5¢ 181.95
Round Off i

Gross Amount
17623

'''


class FoodItem:
    def __init__(self, name, price):
        self.name = name
        self.price = price
    def __repr__(self):
        return f"<name:{self.name} price:{self.price}>"
    def __str__(self):
        return f"<name:{self.name} price:{self.price}>"

class BillItem:
    def __init__(self, foodItem, quantity):
        self.foodItem = foodItem
        self.quantity = quantity
        self.itemTotal = foodItem.price * quantity
    def __repr__(self):
        return f"<foodItem:{self.foodItem} quantity:{self.quantity} itemTotal:{self.itemTotal}>"
    def __str__(self):
        return f"<foodItem:{self.foodItem} quantity:{self.quantity} itemTotal:{self.itemTotal}>"

class Tax:
    def __init__(self, sgst, cgst, st):
        self.sgst = sgst
        self.cgst = cgst
        self.st = st

    def __repr__(self):
        return f"<sgst:{self.sgst} cgst:{self.cgst} st:{self.st}>"
    def __str__(self):
        return f"<sgst:{self.sgst} cgst:{self.cgst} st:{self.st}>"

class Bill:
    def __init__(self, billItem, tax, discount):
        self.itemList = billItem
        self.tax = tax
        self.totalTaxAmount = 0.0
        self.itemTotal = 0.0
        self.grossTotal = 0.0
        self.roundOff = 0.0
        self.calculateFromBillItem()
        self.calculateTaxAmount() 
        self.calculateGrossTotal()


    def calculateFromBillItem(self):
        for i in self.itemList:
            self.itemTotal += i.itemTotal

    def calculateTaxAmount(self):
        self.totalTaxAmount = (self.itemTotal)*(self.tax.cgst + self.tax.sgst + self.tax.st)/100

    def calculateGrossTotal(self):
        self.grossTotal = self.itemTotal + self.totalTaxAmount
        roundOff = round(self.grossTotal)
        if(roundOff > self.grossTotal):
            self.roundOff = roundOff - self.grossTotal
        else:
            self.roundOff = self.grossTotal - roundOff

        self.grossTotal = roundOff

    def __repr__(self):
        return f"ItemTotal:{self.itemTotal}Tax:{self.tax}\nTotal Tax Amount:{self.totalTaxAmount}\nGross Total:{self.grossTotal}"

    def __str__(self):
        return f"\n---\nItemTotal: {self.itemTotal}\nTax: {self.tax}\nTotal Tax Amount: {self.totalTaxAmount}\nGross Total: {self.grossTotal}\n---\n"
       


# my_w = tk.Tk()
# my_w.geometry("1400x900")  # Size of the window 
# my_w.title('Bill Waits')
# my_font1=('times', 18, 'bold')
# l1 = tk.Label(my_w,text='Add Bill Image',width=30,font=my_font1)  
# l1.grid(row=1,column=1)
# b1 = tk.Button(my_w, text='Upload File', 
#    width=20,command = lambda:upload_file())
# b1.grid(row=2,column=1) 
# text_read = pytesseract.image_to_string('test.jpeg')


# def upload_file():
#     global img
#     f_types = [('Jpg Files', '*.jpg')]
#     filename = filedialog.askopenfilename(filetypes=f_types)
#     img=Image.open(filename)
#     img_resized=img.resize((600,800)) # new width & height
#     img=ImageTk.PhotoImage(img_resized)
#     b2 =tk.Button(my_w,image=img,command = lambda:run_ocr()) # using Button 
#     b2.grid(row=3,column=1)

# def run_ocr():
#     text_box = tk.Text(my_w,height=60,width=50)
#     text_box.grid(row=3,column=2)
#     text_box.insert('end',text_read)
#     text_prev = tk.Text(my_w,height=60,width=50,bg='white',fg='black')
#     text_prev.grid(row=3,column=3)
#     text_prev.insert('end',text_read)

def sanitise_data():
    print(textdata)
    p1 = FoodItem("Paneer", 30)
    p2 = FoodItem("Aam", 10)
    p3 = FoodItem("Seb", 20)
    demoList = [p1,p2,p3]
    billItem1 = BillItem(p1,2)
    billItem2 = BillItem(p2,4)
    billItem3 = BillItem(p3,1)
    billItemlist = [billItem1,billItem2,billItem3]
    for item in billItemlist:
        print(item)
    tax = Tax(2.5,2.5,5.0)
    bill = Bill(billItemlist,tax,10)
    print(bill)


# my_w.mainloop()  # Keep the window open

sanitise_data()