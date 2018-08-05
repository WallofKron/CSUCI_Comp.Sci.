#!/usr/bin/python

import Tkinter as tk

class Model:
    def __init__(self):
        self.Money = 0

    def addMoney(self, value):
        self.Money.set(self.Money.get() + value)




class View(tk.Toplevel):
    def __init__(self, master):
        tk.Toplevel.__init__(self, master)
        self.protocol('WM_DELETE_WINDOW', self.master.destroy)
        tk.Label(self, text='My Money').pack(side='left')
        self.moneyCtrl = tk.Entry(self, width=8)
        self.moneyCtrl.pack(side='left')
        
    def SetMoney(self, money):
        self.moneyCtrl.delete(0,'end')
        self.moneyCtrl.insert('end', str(money)) 


class Controller:
    def __init__(self, root):
        self.model = Model()
        self.view = View(root)
 
    def AddMoney(self):
        self.model.addMoney(10)

   
def main():
    root = tk.Tk()
    root.withdraw()
    app = Controller(root)
    root.mainloop()



if __name__ == '__main__':
    main()
