from wumpus_data import *

def cellContainsWumpus(data, x, y):
    (wumpus_x,wumpus_y) = getWumpusPosition(data)
    if wumpus_x==x and wumpus_y==y:
        return True
    else:
        return False

def cellContainsGold(data, x, y):
    (gold_x,gold_y)=getGoldPosition(data)
    if gold_x==x and gold_y==y:
        return True
    else:
        return False

def cellContainsPit(data, x, y):
    (width, height) = getDimensions(data)
    pit = getPits(data)
    i = y * width + x
    if i>15:
        return False
    else:
        return pit[i]

def cellIsVisible(data, x, y):
    (width, height) = getDimensions(data)
    visible = getVisible(data)
    i = y * width + x
    if i>15:
        return False
    else:
        return visible[i]

def cellIsInCavern(data, x, y):
    (width,height)=getDimensions(data)
    return x>=0 and x<width and y>=0 and y<height

def neighborCellIsVisible(data, x, y):
    if cellIsInCavern(data, x + 1, y) and cellIsVisible(data, x + 1, y):
        return True 
    elif cellIsInCavern(data, x - 1, y) and cellIsVisible(data, x - 1, y):
        return True
    elif cellIsInCavern(data, x, y + 1) and cellIsVisible(data, x, y + 1):
        return True
    elif cellIsInCavern(data, x, y - 1) and cellIsVisible(data, x, y - 1):
        return True

    return False

def neighborCellContainsPit(data, x, y):
    if cellIsInCavern(data, x + 1, y) and cellContainsPit(data, x + 1, y):
        return True
    elif cellIsInCavern(data, x - 1, y) and cellContainsPit(data, x - 1, y):
        return True
    elif cellIsInCavern(data, x, y + 1) and cellContainsPit(data, x, y + 1):
        return True
    elif cellIsInCavern(data, x, y - 1) and cellContainsPit(data, x, y - 1):
        return True

    return False

def neighborCellContainsWumpus(data, x, y):
    if cellIsInCavern(data, x + 1, y) and cellContainsWumpus(data, x + 1, y):
        return True
    elif cellIsInCavern(data, x - 1, y) and cellContainsWumpus(data, x - 1, y):
        return True
    elif cellIsInCavern(data, x, y + 1) and cellContainsWumpus(data, x, y + 1):
        return True
    elif cellIsInCavern(data, x, y - 1) and cellContainsWumpus(data, x, y - 1):
        return True

    return False
