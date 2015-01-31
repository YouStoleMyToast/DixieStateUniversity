# CS 1400
# DSC Fall 2009
# Lab 3 Starter Code

# get the graphics library and create graphics window
from graphics import *

ACTION_PET=1
ACTION_FEED=2
ACTION_PLAY=3
ACTION_IGNORE=4
ACTION_ERROR=5

MOOD_HAPPY=1
MOOD_ANGRY=2
MOOD_SLEEPING=3
MOOD_BORED=4
MOOD_HUNGRY=5
MOOD_DEAD=6


# main program
def main():
    """dog drawing program"""
    
    win = GraphWin("CS1400 - Pet Dog", 610, 500) # create graphics window
    mood=MOOD_HAPPY                       
    rec1, rec2, rec3, rec4= draw_buttons(win) # create user buttons

    # loop forever until dog is dead
    while True:
        DrawDogMood(win, mood)
        mouseClick = win.getMouse()                 # get mouse click
        action=getAction(rec1, rec2, rec3, rec4, mouseClick)
        mood = setMood(mood, action)
        if mood == MOOD_DEAD:
            drawDead(win)
            break
        

    # wait for user to click one more time before ending the program
    msg_location = Point(305, 430)
    msg = Text(msg_location, "Click anywhere to quit.")
    msg.setTextColor("red")
    msg.draw(win)                         # draw message
    mouseClick = win.getMouse()
    win.close()
    return

def setMood(mood, action):
    new_mood=mood
    if new_mood==MOOD_HAPPY:
        return happyAction(action)
    elif new_mood==MOOD_ANGRY:
        return angryAction(action)
    elif new_mood==MOOD_SLEEPING:
        return sleepingAction(action)
    elif new_mood==MOOD_BORED:
        return boredAction(action)
    elif new_mood==MOOD_HUNGRY:
        return hungryAction(action)
    
def getAction(rec1, rec2, rec3, rec4, mouseClick):
    if inBox(rec1, mouseClick):
        return ACTION_PET                 
    elif inBox(rec2, mouseClick):
        return ACTION_FEED                            
    elif inBox(rec3, mouseClick):
        return ACTION_PLAY                         
    elif inBox(rec4, mouseClick):
        return ACTION_IGNORE
    else:
        return ACTION_ERROR

def DrawDogMood(win, mood):
    if mood == MOOD_HAPPY:
        drawHappy(win)
    elif mood == MOOD_ANGRY:
        drawAngry(win)
    elif mood == MOOD_SLEEPING:
        drawSleeping(win)
    elif mood == MOOD_BORED:
        drawBored(win)
    elif mood == MOOD_HUNGRY:
        drawHungry(win)
    elif mood == MOOD_DEAD:
        drawDead(win)

def happyAction(action):
   if action==ACTION_PET:
       return MOOD_SLEEPING
   elif action==ACTION_FEED:
       return MOOD_SLEEPING
   elif action==ACTION_PLAY:
       return MOOD_HUNGRY
   elif action==ACTION_IGNORE:
       return MOOD_BORED

def angryAction(action):
   if action==ACTION_PET:
       return MOOD_SLEEPING
   elif action==ACTION_FEED:
       return MOOD_BORED
   elif action==ACTION_PLAY:
       return MOOD_HUNGRY
   elif action==ACTION_IGNORE:
       return MOOD_ANGRY

def sleepingAction(action):
   if action==ACTION_PET:
       return MOOD_ANGRY
   elif action==ACTION_FEED:
       return MOOD_SLEEPING
   elif action==ACTION_PLAY:
       return MOOD_ANGRY
   elif action==ACTION_IGNORE:
       return MOOD_BORED

def boredAction(action):
   if action==ACTION_PET:
       return MOOD_HAPPY
   elif action==ACTION_FEED:
       return MOOD_BORED
   elif action==ACTION_PLAY:
       return MOOD_HUNGRY
   elif action==ACTION_IGNORE:
       return MOOD_SLEEPING

def hungryAction(action):
   if action==ACTION_PET:
       return MOOD_HUNGRY
   elif action==ACTION_FEED:
       return MOOD_SLEEPING
   elif action==ACTION_PLAY:
       return MOOD_ANGRY
   elif action==ACTION_IGNORE:
       return MOOD_DEAD


# Visually erase the contents of the window, by hiding them
def clear_screen(win):
    # overwrite the screen with a blank rectangle (clears the screen)
    rec=Rectangle(Point(10,10),Point(600,440))
    rec.setFill("white")
    rec.draw(win)

# create the buttons at the bottom of the screen
def draw_buttons(win):
    # draw line at bottom of screen
    line1 = Line(Point(10,440),Point(600,440))# create line
    line1.draw(win)                           # draw it

    # draw the 6 buttons at the bottom of the screen
    rec1 = drawRec(win, Point(10,450), Point(150,490), 'green', 'Pet')
    rec2 = drawRec(win, Point(160,450), Point(300,490), 'green', 'Feed')
    rec3 = drawRec(win, Point(310,450), Point(450,490), 'green', 'Play')
    rec4 = drawRec(win, Point(460,450), Point(600,490), 'green', 'Ignore')    
    return rec1, rec2, rec3, rec4

# function to draw a button
#  parameters: win    - Window to draw in        (GraphWin object)
#              recTop - Top corner of button     (Point object)
#              recBot - Bottom corner of button  (Point object)
#              color  - Color of button          (string or Color object)
#              mood   - Text of button           (string)
#
#  return:     a list of these paramters so we can save them of later use
def drawRec(win, recTop, recBot, color, mood):
    """(top corner, bottom corner, color, mood)"""
    rec = Rectangle(recTop,recBot)# create rectangle
    rec.setFill(color)                       # set fill color
    rec.draw(win)                           # draw it
    label = Text(Point((recTop.getX()+recBot.getX())/2,(recBot.getY()+recTop.getY())/2),mood)
    label.draw(win)                         # draw label
    return [recTop,recBot,color]

# function to determine of mouse click is in button box
#  parameters: rec    -  The rectangle of the button box
#              click  -  The Point coordinates of the mouse click
#
#  return:     True  - If click is in the rectangle
#              False - If click is NOT in the rectangle
def inBox(rec, click):
    """(rec, click) checks if click in rec"""
    recTop = rec[0]
    recBot = rec[1]
    if (click.getX() > recTop.getX()) and (click.getX()< recBot.getX()):
        if (click.getY() > recTop.getY()) and (click.getY() < recBot.getY()):
            return True
    return False

#
# Place your shared functions here so they can be used by the
# draw mood functions.
#    

def background(win):
    rect=Rectangle(Point(10,400), Point(600,440))
    rect.setFill('dark green')
    rect.draw(win)
    rect=Rectangle(Point(10,10), Point(600,400))
    rect.setFill('dodger blue')
    rect.draw(win)
    doghouse(win)
    
def dogbody(win):
    center=Point(220,300)
    circ=Circle(center,50)
    circ.setFill('darkslategray')
    circ.draw(win)
    center=Point(380,300)
    circ=Circle(center,50)
    circ.setFill('darkslategray')
    circ.draw(win)
    rect=Rectangle(Point(220,350), Point(380,250))
    rect.setFill('darkslategray')
    rect.draw(win)
    
def dogleftlegs(win):
    poly=Polygon(Point (420, 300), Point (400, 360), Point (410, 410), Point(390, 410), Point (385, 360), Point (390, 300))
    poly.setFill('darkslategray')
    poly.draw(win)
    poly=Polygon(Point (235, 300), Point (215, 360), Point (225, 410), Point(205, 410), Point (200, 360), Point (195, 300))
    poly.setFill('darkslategray')
    poly.draw(win)
    oval=Oval(Point (380,415), Point(410,400))
    oval.setFill('darkslategray')
    oval.draw(win)
    oval=Oval(Point (195,420), Point(225,405))
    oval.setFill('darkslategray')
    oval.draw(win)

def dogrightlegs(win):
    poly=Polygon(Point (410, 295), Point (390, 355), Point (400, 405), Point(380, 405), Point (375, 355), Point (380, 295))
    poly.setFill('darkslategray')
    poly.draw(win)
    poly=Polygon(Point (220, 305), Point (200, 365), Point (210, 405), Point(190, 405), Point (185, 365), Point (190, 305))
    poly.setFill('darkslategray')
    poly.draw(win)
    oval=Oval(Point (370,405), Point(400,390))
    oval.setFill('darkslategray')
    oval.draw(win)
    oval=Oval(Point (180,410), Point(210,395))
    oval.setFill('darkslategray')
    oval.draw(win)


def dogtail(win):
    poly=Polygon(Point (420, 245), Point(425, 247),Point (410, 260), Point(400, 260))
    poly.setFill('darkslategray')
    poly.draw(win)

def dogneck(win):
    poly=Polygon(Point (140,203), Point (210, 250), Point (190, 330), Point (125, 250))
    poly.setFill('darkslategray')
    poly.draw(win)

def dogear(win):
    poly1=Polygon(Point(130,180), Point (130, 220), Point (150, 220))
    poly1.setFill('darkslategray')
    poly1.draw(win)
    center=Point(140,225)
    circ=Circle(center,15)
    circ.setFill('darkslategray')
    circ.draw(win)
    circ.setOutline('darkslategray')

def doghead(win):
    poly=Polygon(Point(50,245), Point (90, 220), Point(140,205), Point (150,235), Point (50,260))
    poly.setFill('darkslategray')
    poly.draw(win)
    poly=Polygon(Point(50,270), Point (150,230), Point (150,255), Point (60,270))
    poly.setFill('darkslategray')
    poly.draw(win)
    center=Point(90,225)
    circ=Circle(center,10)
    circ.setFill('white')
    circ.draw(win)
    center=Point(90,225)
    circ=Circle(center,3)
    circ.setFill('black')
    circ.draw(win)


def cleanup(win):
    center=Point(219,298)
    circ=Circle(center,47)
    circ.setFill('darkslategray')
    circ.setOutline('darkslategray')
    circ.draw(win)
    center=Point(380,298)
    circ=Circle(center,47)
    circ.setFill('darkslategray')
    circ.setOutline('darkslategray')
    circ.draw(win)
    center=Point(140,235)
    circ=Circle(center,25)
    circ.setFill('darkslategray')
    circ.setOutline('darkslategray')
    circ.draw(win)

def doghouse(win):
    poly=Polygon(Point(450,200), Point (600,200), Point (600,420), Point (450,420))
    poly.setFill('red')   
    poly.draw(win)
    poly=Polygon(Point(440,110), Point (600,110), Point (600,200), Point (400,200))
    poly.setFill('brown')   
    poly.draw(win)
    poly=Polygon(Point(455,250), Point (600,250), Point (600,420), Point (455,420))
    poly.setFill('black')   
    poly.draw(win)
    poly=Polygon(Point(465,200), Point (600,200), Point (600,420), Point (465,420))
    poly.setFill('red')   
    poly.draw(win)
    poly=Polygon(Point(475,200), Point (600,200), Point (600,420), Point (475,420))
    poly.setFill('red')   
    poly.draw(win)
    poly=Polygon(Point(465,250), Point (471,250), Point (471,420), Point (465,420))
    poly.setFill('black')   
    poly.draw(win)
 
def basicbody(win):
    dogrightlegs(win)
    dogbody(win)
    dogtail(win)
    dogleftlegs(win)
    dogneck(win)
    doghead(win)
    poly=Polygon(Point(50,245), Point (52,242), Point (58,242),Point (51,248))
    poly.setFill('black')
    poly.draw(win) 
    cleanup(win)

# draw happy dog (Place your code here)
def drawHappy(win):
    """draws happy dog"""
    clear_screen(win)
    background(win)
    poly=Polygon(Point(50,265), Point (120,243), Point (120,260), Point (55,270))
    poly.setFill('deeppink')
    poly.draw(win)
    basicbody(win)
    dogear(win)

# draw angry dog (Place your code here)
def drawAngry(win):
    """draws angry dog"""
    clear_screen(win)
    background(win)
    poly=Polygon(Point(51,258), Point (120,240), Point (120,260), Point (53,270))
    poly.setFill('white')
    poly.draw(win)
    basicbody(win)
    poly=Polygon(Point(200,215), Point (140, 205), Point (150, 218))
    poly.setFill('darkslategray')
    poly.draw(win)
    center=Point(140,220)
    circ=Circle(center,14)
    circ.setFill('darkslategray')
    circ.draw(win)
    circ.setOutline('darkslategray')
    poly=Polygon(Point(80,228), Point (81, 222),Point (84, 218), Point (88, 216), Point (90, 216), Point (94,216), Point (99,220))
    poly.setFill('darkslategray')
    poly.draw(win)

# draw sleeping dog (Place your code here)
def drawSleeping(win):
    """draws sleeping dog"""
    clear_screen(win)
    background(win)
# dogbody
    center=Point(360,360)
    circ=Circle(center,50)
    circ.setFill('darkslategray')
    circ.draw(win)
    center=Point(500,360)
    circ=Circle(center,50)
    circ.setFill('darkslategray')
    circ.draw(win)
    rect=Rectangle(Point(360,410), Point(500,310))
    rect.setFill('darkslategray')
    rect.draw(win)      
# dogneck
    poly=Polygon(Point (240,350), Point (330, 325), Point (335, 402), Point (235, 402))
    poly.setFill('darkslategray')
    poly.draw(win) 
# doghead
    poly=Polygon(Point(150,385), Point (190, 360), Point(240,345), Point (250,398), Point (150,394))
    poly.setFill('darkslategray')
    poly.draw(win)
    poly=Polygon(Point(150,397), Point (250,393), Point (250,401), Point (160,402))
    poly.setFill('darkslategray')
    poly.draw(win)
    center=Point(185,370)
    circ=Circle(center,10)
    circ.setFill('darkslategray')
    circ.draw(win)
    poly=Polygon(Point(149,385), Point (156, 382), Point(155,386), Point (149,388))
    poly.setFill('black')
    poly.draw(win)
# dogear
    poly1=Polygon(Point(230,310), Point (230, 350), Point (250, 350))
    poly1.setFill('darkslategray')
    poly1.draw(win)
# dogleg
    poly=Polygon (Point (275, 400), Point(375, 400), Point (375, 415), Point(275, 415))
    poly.setFill('darkslategray')
    poly.draw(win)
    oval=Oval(Point(255,400),Point(280,415))
    oval.setFill('darkslategray')
    oval.draw(win)
# doghouse add on
    poly=Polygon(Point(465,200), Point (600,200), Point (600,420), Point (465,420))
    poly.setFill('red')   
    poly.draw(win)
    poly=Polygon(Point(475,200), Point (600,200), Point (600,420), Point (475,420))
    poly.setFill('red')   
    poly.draw(win)
    poly=Polygon(Point(465,250), Point (471,250), Point (471,420), Point (465,420))
    poly.setFill('black')   
    poly.draw(win)
#cleanup
    center=Point(360,360)
    circ=Circle(center,48)
    circ.setFill('darkslategray')
    circ.draw(win)
    circ.setOutline('darkslategray')
    center=Point(240,375)
    circ=Circle(center,26)
    circ.setFill('darkslategray')
    circ.draw(win)
    circ.setOutline('darkslategray')
   
# draw bored dog (Place your code here)
def drawBored(win):
    """draws bored dog"""
    clear_screen(win)
    background(win)
# dogbody
    center=Point(360,360)
    circ=Circle(center,50)
    circ.setFill('darkslategray')
    circ.draw(win)
    center=Point(500,360)
    circ=Circle(center,50)
    circ.setFill('darkslategray')
    circ.draw(win)
    rect=Rectangle(Point(360,410), Point(500,310))
    rect.setFill('darkslategray')
    rect.draw(win)      
# dogneck
    poly=Polygon(Point (240,350), Point (330, 325), Point (335, 402), Point (235, 402))
    poly.setFill('darkslategray')
    poly.draw(win) 
# doghead
    poly=Polygon(Point(235,300), Point (240, 310), Point(240,403), Point (225,403))
    poly.setFill('darkslategray')
    poly.draw(win)
    poly=Polygon(Point(225,302), Point (233, 300), Point(230,403), Point (185,403), Point (195,350))
    poly.setFill('darkslategray')
    poly.draw(win)
    center=Point(200,350)
    circ=Circle(center,10)
    circ.setFill('white')
    circ.draw(win)
    center=Point(200,350)
    circ=Circle(center,3)
    circ.setFill('black')
    circ.draw(win) 
# dogear
    poly1=Polygon(Point(155,404), Point (190, 390), Point (190, 404))
    poly1.setFill('darkslategray')
    poly1.draw(win)
# dogleg
    poly=Polygon (Point (290, 300), Point(380, 300), Point (380, 315), Point(290, 315))
    poly.setFill('darkslategray')
    poly.draw(win)
    oval=Oval(Point (280,296),Point(295,318))
    oval.setFill('darkslategray')
    oval.draw(win)
    
# doghouse add on
    poly=Polygon(Point(465,200), Point (600,200), Point (600,420), Point (465,420))
    poly.setFill('red')   
    poly.draw(win)
    poly=Polygon(Point(475,200), Point (600,200), Point (600,420), Point (475,420))
    poly.setFill('red')   
    poly.draw(win)
    poly=Polygon(Point(465,250), Point (471,250), Point (471,420), Point (465,420))
    poly.setFill('black')   
    poly.draw(win)
# squirl
    oval=Oval(Point (170,35),Point(195,50))
    oval.setFill('white')
    oval.setOutline('white')
    oval.draw(win)
    center=Point(165,60)
    circ=Circle(center,20)
    circ.setFill('white')
    circ.setOutline('white')
    circ.draw(win)
    oval=Oval(Point (130,35),Point(170,60))
    oval.setFill('white')
    oval.setOutline('white')
    oval.draw(win)
    center=Point(165,60)
    circ=Circle(center,20)
    circ.setFill('white')
    circ.setOutline('white')
    circ.draw(win)
    center=Point(190,90)
    circ=Circle(center,30)
    circ.setFill('white')
    circ.setOutline('white')
    circ.draw(win)
    center=Point(210,80)
    circ=Circle(center,10)
    circ.setFill('white')
    circ.setOutline('white')
    center=Point(215,70)
    circ=Circle(center,10)
    circ.setFill('white')
    circ.setOutline('white')
    circ.draw(win)
    center=Point(227,60)
    circ=Circle(center,10)
    circ.setFill('white')
    circ.setOutline('white')
    circ.draw(win)
    center=Point(238,50)
    circ=Circle(center,15)
    circ.setFill('white')
    circ.setOutline('white')
    circ.draw(win)   

#cleanup
    center=Point(198,393)
    circ=Circle(center,10)
    circ.setFill('darkslategray')
    circ.setOutline('darkslategray')
    circ.draw(win)
    center=Point(230,385)
    circ=Circle(center,17)
    circ.setFill('darkslategray')
    circ.setOutline('darkslategray')
    circ.draw(win)
    center=Point(235,385)
    circ=Circle(center,16)
    circ.setFill('darkslategray')
    circ.setOutline('darkslategray')
    circ.draw(win)
    center=Point(360,360)
    circ=Circle(center,48)
    circ.setFill('darkslategray')
    circ.setOutline('darkslategray')
    circ.draw(win)  

    
# draw hungry dog (Place your code here)
def drawHungry(win):
    """draws hungry dog"""
    clear_screen(win)
    background(win)
    basicbody(win)
    dogear(win)
    poly=Polygon(Point(34,270), Point (70, 255),Point (74, 265), Point (34, 280))
    poly.setFill('red')
    poly.draw(win)
    
    
# draw dead dog (Place your code here)
def drawDead(win):
    """draws dead dog"""
    clear_screen(win)
#sky
    rec=Rectangle(Point(10,10),Point(600,440))
    rec.setFill("dodgerblue")
    rec.draw(win)
#clouds
    oval=Oval(Point (20,325),Point(150,425))
    oval.setFill('white')
    oval.setOutline('white')
    oval.draw(win)
    oval=Oval(Point (100,325),Point(250,425))
    oval.setFill('white')
    oval.setOutline('white')
    oval.draw(win)
    oval=Oval(Point (200,325),Point(355,425))
    oval.setFill('white')
    oval.setOutline('white')
    oval.draw(win)
    oval=Oval(Point (300,325),Point(455,425))
    oval.setFill('white')
    oval.setOutline('white')
    oval.draw(win)
    oval=Oval(Point (400,325),Point(555,425))
    oval.setFill('white')
    oval.setOutline('white')
    oval.draw(win)
# deaddog
# dogleg right
    poly=Polygon (Point (270, 400), Point(295, 320), Point(370, 330), Point (370, 380), Point(300, 350), Point(285, 400))
    poly.setFill('darkslategray')
    poly.draw(win)
    oval=Oval(Point(260,400),Point(280,410))
    oval.setFill('darkslategray')
    oval.draw(win)
    poly=Polygon (Point (180, 245), Point(280, 245), Point (290, 255), Point(180, 255))
    poly.setFill('darkslategray')
    poly.draw(win)
    oval=Oval(Point(170,245),Point(190,255))
    oval.setFill('darkslategray')
    oval.draw(win)

#harp
    poly=Polygon (Point (110, 225), Point(190, 230), Point (230, 237), Point(160, 233))
    poly.setFill('yellow')
    poly.setOutline('yellow')
    poly.draw(win)
    poly=Polygon (Point (110, 225), Point(111, 350), Point (110, 400), Point(108,360))
    poly.setFill('yellow')
    poly.setOutline('yellow')
    poly.draw(win)
    poly=Polygon (Point (230, 237), Point(231, 250), Point (230, 260), Point(229, 245))
    poly.setFill('yellow')
    poly.setOutline('yellow')
    poly.draw(win)
    poly=Polygon (Point (230, 260), Point(225, 305), Point (112, 400), Point(220, 310))
    poly.setFill('yellow')
    poly.setOutline('yellow')
    poly.draw(win)
    line=Line (Point (115,225), Point (115, 398))
    line.setOutline ('yellow')
    line.draw(win)
    line=Line (Point (120,226), Point (120, 392))
    line.setOutline ('yellow')
    line.draw(win)
    line=Line (Point (125,226), Point (125, 390))
    line.setOutline ('yellow')
    line.draw(win)
    line=Line (Point (130,226), Point (130, 388))
    line.setOutline ('yellow')
    line.draw(win)
    line=Line (Point (135,226), Point (135, 388))
    line.setOutline ('yellow')
    line.draw(win)
    line=Line (Point (140,227), Point (140, 385))
    line.setOutline ('yellow')
    line.draw(win)
    line=Line (Point (145,227), Point (145, 385))
    line.setOutline ('yellow')
    line.draw(win)
    line=Line (Point (150,227), Point (150, 370))
    line.setOutline ('yellow')
    line.draw(win)
    line=Line (Point (155,227), Point (155, 370))
    line.setOutline ('yellow')
    line.draw(win)
    line=Line (Point (160,228), Point (160, 350))
    line.setOutline ('yellow')
    line.draw(win)
    line=Line (Point (165,228), Point (165, 350))
    line.setOutline ('yellow')
    line.draw(win)
    line=Line (Point (170,228), Point (170, 350))
    line.setOutline ('yellow')
    line.draw(win)
    line=Line (Point (175,235), Point (175, 330))
    line.setOutline ('yellow')
    line.draw(win)
    line=Line (Point (180,235), Point (180, 330))
    line.setOutline ('yellow')
    line.draw(win)
    line=Line (Point (185,235), Point (185, 330))
    line.setOutline ('yellow')
    line.draw(win)
    line=Line (Point (190,235), Point (190, 325))
    line.setOutline ('yellow')
    line.draw(win)
    line=Line (Point (195,235), Point (195, 325))
    line.setOutline ('yellow')
    line.draw(win)
    line=Line (Point (200,235), Point (200, 325))
    line.setOutline ('yellow')
    line.draw(win)
    line=Line (Point (205,235), Point (205, 320))
    line.setOutline ('yellow')
    line.draw(win)
    line=Line (Point (210,237), Point (210, 320))
    line.setOutline ('yellow')
    line.draw(win)
    line=Line (Point (215,237), Point (215, 315))
    line.setOutline ('yellow')
    line.draw(win)
    line=Line (Point (220,237), Point (220, 315))
    line.setOutline ('yellow')
    line.draw(win)
    line=Line (Point (235,238), Point (245, 260))
    line.setOutline ('yellow')
    line.draw(win)
# dogbody
    center=Point(300,260)
    circ=Circle(center,50)
    circ.setFill('darkslategray')
    circ.draw(win)
    center=Point(400,360)
    circ=Circle(center,50)
    circ.setFill('darkslategray')
    circ.draw(win)
    poly=Polygon(Point (325,216), Point (420, 314),Point (374, 400), Point (280, 305))
    poly.setFill('darkslategray')
    poly.draw(win) 
    poly=Polygon(Point (450,350), Point (462,345),Point (466,355), Point (450,360))
    poly.setFill('darkslategray')
    poly.draw(win) 
# dogneck
    poly=Polygon(Point (250,170), Point (310,210),Point (270,300), Point (220, 210))
    poly.setFill('darkslategray')
    poly.draw(win) 
# doghead
    poly=Polygon(Point(160,205), Point (200, 180), Point(250,165), Point (260,218), Point (160,214))
    poly.setFill('darkslategray')
    poly.draw(win)
    poly=Polygon(Point(160,217), Point (260,213), Point (260,221), Point (160,222))
    poly.setFill('darkslategray')
    poly.draw(win)
    center=Point(210,180)
    circ=Circle(center,10)
    circ.setFill('white')
    circ.draw(win)
    center=Point(209,180)
    circ=Circle(center,3)
    circ.setFill('black')
    circ.draw(win)
    poly=Polygon(Point(160,205), Point (165, 202), Point(164,205), Point (160,208))
    poly.setFill('black')
    poly.draw(win)
# dogear
    poly1=Polygon(Point(250,135), Point (240, 173), Point (260, 180))
    poly1.setFill('darkslategray')
    poly1.draw(win)
# dogleg left
    poly=Polygon (Point (280, 400), Point(305, 320), Point(380, 330), Point (380, 380), Point(310, 350), Point(295, 400))
    poly.setFill('darkslategray')
    poly.draw(win)
    oval=Oval(Point(165,260),Point(185,270))
    oval.setFill('darkslategray')
    oval.draw(win)
    poly=Polygon (Point (180, 260), Point (230, 260), Point(280, 230), Point (280, 265), Point(180, 270))
    poly.setFill('darkslategray')
    poly.draw(win)
    oval=Oval(Point(272,399),Point(295,409))
    oval.setFill('darkslategray')
    oval.draw(win)


#halo
    oval=Oval(Point(238,127),Point(285,142))
    oval.setFill('yellow')
    oval.setOutline('yellow')
    oval.draw(win)
    oval=Oval(Point(242,130),Point(277,140))
    oval.setFill('dodgerblue')
    oval.setOutline('dodgerblue')
    oval.draw(win)

#cleanup
    center=Point(301,260)
    circ=Circle(center,49)
    circ.setFill('darkslategray')
    circ.setOutline('darkslategray')
    circ.draw(win)
    center=Point(245,200)
    circ=Circle(center,27)
    circ.setFill('darkslategray')
    circ.setOutline('darkslategray')
    circ.draw(win)
    center=Point(400,360)
    circ=Circle(center,49)
    circ.setFill('darkslategray')
    circ.setOutline('darkslategray')
    circ.draw(win)
    center=Point(380,320)
    circ=Circle(center,20)
    circ.setFill('darkslategray')
    circ.setOutline('darkslategray')
    circ.draw(win)


# run main loop
main()
