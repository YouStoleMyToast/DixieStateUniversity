import pygtk
import gtk
import random

GAME_SIZE = 10          # size of game in buttons (i.e. 10x10)
CELL_SIZE = 20          # how big each buttons should be (in pixels)
IMG_FLAG = 'flag.jpg'   # image to display for flags
IMG_BOMB = 'bomb.jpg'   # image to display for bombs
NUM_BOMBS = 10          # how many bombs should be on the screen
BOMB='bomb'

class MinesweeperGUI:
    def __init__(self):
        self.createWindow()
        self.createMenu()
        self.table = myTable(GAME_SIZE, GAME_SIZE)
        self.button=[]
        self.size= GAME_SIZE
        self.logic=MinesweeperLogic(GAME_SIZE)
        self.cell=Cell()
        self.createGame()
        self.window.show_all()

    def createWindow(self):
        self.window=gtk.Window()
        self.window.set_resizable(resizable=True)
        self.main_vbox=gtk.VBox()
        self.window.set_title('Minesweeper')

        self.window.connect('destroy', self.destroy_handler, None)
        self.window.connect('delete_event',self.delete_handler, None)
        self.window.add(self.main_vbox)

    def createMenu(self):
        self.menu=gtk.Menu()
        self.createMenuItem('New Game',self.restart_handler)
        self.createMenuItem('Solve',self.solve_handler)
        self.createMenuItem('Quit',self.destroy_handler)
        root_menu=gtk.MenuItem()
        root_menu.set_label('Game')
        root_menu.set_submenu(self.menu)
        self.menubar=gtk.MenuBar()
        self.menubar.append(root_menu)
        self.main_vbox.pack_start(self.menubar)

    def createMenuItem(self,title,handler):
        self.item=gtk.MenuItem(label=title, use_underline=True)
        self.item.connect('activate',handler)
        self.menu.append(self.item)

    def createGame(self):
        for y in range(GAME_SIZE):
            buttons = []
            for x in range(GAME_SIZE):
                b = gtk.Button()
                b.set_size_request(CELL_SIZE,CELL_SIZE)
                buttons.append(b)
                b.connect('button_press_event',self.clicked_handler)
                self.table.attachButton(b,y,x)
            self.button.append(buttons)
        self.main_vbox.pack_start(self.table)
        self.placeImagesAndLabels()

    def getSmallImage(self, pic):
        self.image=gtk.Image()
        pb=gtk.gdk.pixbuf_new_from_file(pic)
        pb=pb.scale_simple(CELL_SIZE-10, CELL_SIZE, gtk.gdk.INTERP_BILINEAR)
        self.image.set_from_pixbuf(pb)
        return self.image

    def delete_handler(self, widget,event,data=None):
        return False

    def destroy_handler(self,widget,data=None):
        gtk.main_quit()

    def restart_handler(self,widget,data=None):
        self.logic.reset()
        self.table.clearImages()
        self.table.clearLabels()
        self.clearFlagsAndHideButtons()
        self.placeImagesAndLabels()
        self.updateDisplay(widget)
        self.window.show_all()

    def clicked_handler(self, widget,data=None):
        if data.button==1:
            (row,col)=self.table.getRowColOfButton(widget)
            self.processCells(widget)
            self.updateDisplay(widget)
        elif data.button==3:
            self.toggleFlag(widget)

    def solve_handler(self,widget,data=None):
        self.clearFlagsAndHideButtons()
        self.updateDisplay(widget)

    def clearFlagsAndHideButtons(self):
        for row in range(self.size):
            for col in range (self.size):
                self.button[row][col].hide()
                img = self.button[row][col].get_image()
                if img:
                    img.set_visible(visible=False)

    def toggleFlag(self, widget):
        if not widget.get_image():
            widget.set_image(self.getSmallImage(IMG_FLAG))
            widget.get_image().set_visible(True)
        elif widget.get_image().get_visible():
            widget.get_image().set_visible(False)
        else:
            widget.get_image().set_visible(True)

    def placeImagesAndLabels(self):
        place = self.logic.getBombLocations()
        for row in range(self.size):
            for col in range(self.size):
                x=place[row][col].getContents()
                if x==BOMB:
                    smallbomb=self.getSmallImage(IMG_BOMB)
                    self.table.attachImage(smallbomb, row, col)
                elif x>0:
                    label = gtk.Label()
                    label.set_text(str(x))
                    self.table.attachLabel(label,row,col)

    def updateDisplay(self,widget):
        loc = self.logic.getBombLocations()
        for x in range(GAME_SIZE):
            for y in range(GAME_SIZE):
                if loc[x][y].getVisible()==True:
#                    (row,col)=self.table.getRowColOfButton(widget)
                    self.button[x][y].hide()

    def processCells(self,widget):
        (row,col)=self.table.getRowColOfButton(widget)
        place=self.logic.bomb_locations[row][col].getContents()
        if place==BOMB:
            self.clearFlagsAndHideButtons()
            print 'You landed on a bomb, Game over!'
        else:
            pass
            self.logic.checkCell(row,col)
            
    def run(self):
        gtk.main()

class myTable(gtk.Table):
    def __init__(self, xsize, ysize):
         gtk.Table.__init__(self, xsize, ysize, True)
         numcells = xsize * ysize
         self.xsize = xsize
         self.ysize = ysize
         self.cells = []
         self.images = []
         self.labels = []

    def attachButton(self,button,row,col):
        index=row*GAME_SIZE + col
        self.attach(button, col, col+1, row, row+1)
        self.cells.append((button, index))

    def getRowColOfButton(self, button):
        for (b,index) in self.cells:
            if b==button:
                row=index/self.xsize
                col=index%self.xsize
                return (row, col)

    def attachImage(self,image,row,col):
        self.attach(image, col, col+1, row, row+1)
        index = row * GAME_SIZE + col
        self.images.append(image)

    def attachLabel(self,label,row,col):
        self.attach(label, col, col+1, row, row+1)
        index = row * GAME_SIZE + col
        self.labels.append(label)

    def clearImages(self):
        for i in self.images:
            self.remove(i)

    def clearLabels(self):
        for i in self.labels:
            self.remove(i)
            
class Cell:
    def __init__(self):
        self.content = ''
        self.visibility=False

    def setVisible(self):
        self.visibility=True

    def getVisible(self):
        return self.visibility

    def getContents(self):
        return self.content

    def setContents(self, content):
        self.content = content

class MinesweeperLogic:
    def __init__(self, s):
        self.size=s
        self.reset()

    def reset(self):
        self.bomb_locations=[]
        for row in range(self.size):
            r = []
            for col in range(self.size):
                c = Cell()
                r.append(c)
            self.bomb_locations.append(r)
        self.setBombLocations()
        self.setBombCounters()

    def getBombLocations(self):
        return self.bomb_locations

    def setBombLocations(self):
        for i in range(NUM_BOMBS):
            randrow = random.randint(0,self.size-1)
            randcol = random.randint(0,self.size-1)
            self.bomb_locations[randrow][randcol].setContents(BOMB)

    def setBombCounters(self):
        for row in range(self.size):
            for col in range(self.size):
                if self.bomb_locations[row][col].getContents() != BOMB:
                    self.bomb_locations[row][col].setContents(self.setBombCountNumbers(row,col))

    def setBombCountNumbers(self, row, col):
        count=0
        count += self.isBomb(row-1, col-1)
        count += self.isBomb(row-1, col)
        count += self.isBomb(row-1, col+1)
        count += self.isBomb(row, col-1)
        count += self.isBomb(row, col+1)
        count += self.isBomb(row+1, col-1)
        count += self.isBomb(row+1, col)
        count += self.isBomb(row+1, col+1)
        return count

    def isBomb(self, row, col):
        if row<0:
            return 0
        if row>=GAME_SIZE:
            return 0
        if col<0:
            return 0
        if col>=GAME_SIZE:
            return 0
        if self.bomb_locations[row][col].getContents()==BOMB:
            return 1
        else:
            return 0

    def checkCell(self, row, col):
        if row < 0 or row >= self.size or col < 0 or col >= self.size:
#            print "OUT OF RANGE"
            return
        if self.bomb_locations[row][col].getVisible():
#            print "DONE BEEN HERE (%d, %d)" % (row, col)
            return
        
        cell_contents = self.bomb_locations[row][col].getContents()       
        self.bomb_locations[row][col].setVisible()
        if cell_contents == 0:
            self.checkCell(row+1,col)
            self.checkCell(row-1,col)
            self.checkCell(row,col+1)
            self.checkCell(row,col-1)

        
        
x=MinesweeperGUI()
x.run()

