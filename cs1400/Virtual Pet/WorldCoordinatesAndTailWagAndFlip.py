from graphics import *
import math

def BriefPause():
    for i in range(3000000):
        x = math.sqrt(2)
        
def main():
    screen_x = 600
    screen_y = 600
    win = GraphWin("My Cool Window", screen_x, screen_y)
    win.setCoords(0,600, 600,0)

    snakeStart = Point(305,230)
    snakeEnd = Point(305,250)
    snakeStart2 = Point(305, 220)
    snakeEnd2 = Point(305,240)
    snake1 = Line( snakeStart, snakeEnd )
    snake1.setWidth(10)

    snake2 = Line(snakeStart2, snakeEnd2)
    snake2.setWidth(10)
    snake2.draw(win)

    while win.checkMouse() == None:
        snake1.draw(win)
        snake2.undraw()
        BriefPause()
        snake2.draw(win)
        snake1.undraw()
        BriefPause()
        #snake = Line( snakeStart, snakeEnd )
   
    #win.getMouse() # pause for click in window
    win.close()

main()
