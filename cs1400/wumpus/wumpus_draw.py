from graphics     import *
from wumpus_data  import *
from wumpus_logic import *

# Implement drawWumpus, drawGold, drawBreeze, drawStench, and updateDisplay here

def initializeGraphics(width, height, cell_size):
    global HIDDEN, VISIBLE
    global WUMPUS_PIXMAP, PIT_PIXMAP, GOLD_PIXMAP, STENCH_PIXMAP, BREEZE_PIXMAP
    global ADVENTURER_GOLD_PIXMAP, ADVENTURER_DEAD_PIXMAP
    global  ADVENTURER_ARROW_PIXMAP, ADVENTURER_NO_ARROW_PIXMAP

    window = GraphWin("Find the Gold", width*cell_size, height*cell_size)
    HIDDEN  = color_rgb(100, 100, 100)
    VISIBLE = color_rgb(200, 200, 200)
    WUMPUS_PIXMAP = "wumpus_img.gif"
    PIT_PIXMAP    = "pit_img.gif"
    GOLD_PIXMAP   = "gold_img.gif"
    STENCH_PIXMAP = "stench_img.gif"
    BREEZE_PIXMAP = "breeze_img.gif"
    ADVENTURER_GOLD_PIXMAP     = "adventurer_gold_img.gif"
    ADVENTURER_DEAD_PIXMAP     = "adventurer_dead_img.gif"
    ADVENTURER_ARROW_PIXMAP    = "adventurer_arrow_img.gif"
    ADVENTURER_NO_ARROW_PIXMAP = "adventurer_no_arrow_img.gif"
    return window

def drawCell(window, data, x, y):
    cell_size = getCellSize(data)
    b_visible = cellIsVisible(data, x, y)
    p1 = Point(x*cell_size, y*cell_size)
    p2 = Point((x+1)*cell_size, (y+1)*cell_size)
    cell = Rectangle(p1, p2)
    if b_visible:
        cell.setFill(VISIBLE)
        cell.draw(window)
        drawPit(window, data, x, y)
        drawWumpus(window, data, x, y)
        drawGold(window, data, x, y)
        drawBreeze(window, data, x, y)
        drawStench(window, data, x, y)
    else:
        cell.setFill(HIDDEN)
        cell.draw(window)

def drawAdventurer(window, data, x, y):
    cell_size  = getCellSize(data)
    have_gold  = getHaveGold(data)
    have_arrow = getHaveArrow(data)
    is_alive   = getIsAlive(data)
    adventurer_point = Point((x+.25)*cell_size, (y+.25)*cell_size)
    if not is_alive:
        ai = Image(adventurer_point, ADVENTURER_DEAD_PIXMAP)
    elif have_gold:
        ai = Image(adventurer_point, ADVENTURER_GOLD_PIXMAP)
    elif have_arrow:
        ai = Image(adventurer_point, ADVENTURER_ARROW_PIXMAP)
    else:
        ai = Image(adventurer_point, ADVENTURER_NO_ARROW_PIXMAP)
    ai.draw(window)

def drawPit(window, data, x, y):
    cell_size = getCellSize(data)
    contains  = cellContainsPit(data, x, y)
    point     = Point((x+.75)*cell_size, (y+.25)*cell_size)
    if contains:
        img = Image(point, PIT_PIXMAP)
        img.draw(window)

def updateDisplay(window, data, ax, ay):
    (width, height) = getDimensions(data)
    for y in range(0, height):
        for x in range(0, width):
            drawCell(window, data, x, y)
    drawAdventurer(window, data, ax, ay) 

def drawWumpus(window, data, x, y):
    cell_size = getCellSize(data)
    contains  = cellContainsWumpus(data, x, y)
    point     = Point((x+.75)*cell_size, (y+.75)*cell_size)
    if contains:
        img = Image(point, WUMPUS_PIXMAP)
        img.draw(window)

def drawGold(window, data, x, y):
    cell_size = getCellSize(data)
    contains  = cellContainsGold(data, x, y)
    point     = Point((x+.25)*cell_size, (y+.75)*cell_size)
    if contains:
        img = Image(point, GOLD_PIXMAP)
        img.draw(window)

def drawBreeze(window, data, x, y):
    cell_size = getCellSize(data)
    pit  = neighborCellContainsPit(data, x, y)
    point = Point((x+.75)*cell_size, (y+.25)*cell_size)
    if pit:
        img = Image(point, BREEZE_PIXMAP)
        img.draw(window)

def drawStench(window, data, x, y):
    cell_size = getCellSize(data)
    wumpus  = neighborCellContainsWumpus(data, x, y)
    point = Point((x+.75)*cell_size, (y+.75)*cell_size)
    if wumpus:
        img = Image(point, STENCH_PIXMAP)
        img.draw(window)

