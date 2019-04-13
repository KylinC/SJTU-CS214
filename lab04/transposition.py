from tkinter import *

class MyCanvas(Canvas):
    def __init__(self, master, hLineWidth=1, vLineWidth=1, radius=2, **kwargs):
        Canvas.__init__(self, master, kwargs)
        self.hLineWidth = hLineWidth
        self.vLineWidth = vLineWidth
        self.radius = radius

    def create_segment_h(self, x, y, l):
        self.create_line(x, y, x + l, y, width=self.hLineWidth)
        self.create_oval(x - self.radius, y - self.radius, x + self.radius, y + self.radius, fill='black')
        self.create_oval(x + l - self.radius, y - self.radius, x + l - self.radius, y + self.radius, fill='black')

    def create_segment_v(self, x, y, l):
        self.create_line(x, y, x, y + l, width=self.vLineWidth)
        self.create_oval(x - self.radius, y - self.radius, x + self.radius, y + self.radius, fill='black')
        self.create_oval(x - self.radius, y + l - self.radius, x + self.radius, y + l + self.radius, fill='black')

    def create_line_h(self, x, y, l):
        self.create_line(x, y, x + l, y, width=self.hLineWidth)

    def create_line_v(self, x, y, l):
        self.create_line(x, y, x, y + l, width=self.vLineWidth)


class Transposition:
    def __init__(self, size):
        self.size = size
        if size>1:
            self.subTransposition=Transposition(size-1)

    def getInterval(self, winW, winH):
        return (winH-100)//(self.size-1)

    def drawBase(self, cvs, winW, winH):
        for i in range(self.size):
            cvs.create_line_h(0,winH-50-i*self.getInterval(winW,winH),winW)

    def draw(self, cvs, interval, widval, position_x, position_y):
        tmp_x=position_x
        tmp_y=position_y
        for i in range(self.size-1):
            cvs.create_segment_v(tmp_x,tmp_y,interval)
            tmp_x+=widval
            tmp_y-=interval
        if self.size > 1:
            self.subTransposition.draw(cvs, interval, widval, position_x-widval, position_y-interval)



def main():
    n = int(input('please input the number n: '))

    Tran=Transposition(n)
    winW, winH = 1200, 800
    interval= (winH-100)//(n-1)
    widval=(winW)//(2*n-2)
    root = Tk()
    root.title('Sorting Network with n=%d (Drawn by Python Tkinter)' % n)
    cvs = MyCanvas(root, bg='white', width=winW, height=winH)
    Tran.drawBase(cvs,winW,winH)
    Tran.draw(cvs,interval,widval,winW//2,winH-50-interval)

    cvs.pack()
    root.mainloop()

if __name__ == '__main__':
    main()