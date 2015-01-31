import random

#
# The wumpus world data is contained in an array with the following elements:
#
# [0],[1] width, height are the dimensions of the world, in cells.
#
# [2] cell_size is the number of pixels on the side of each cell in the display.
#
# [3] pits is an array with one element per cell.  The value of each element,
#   pits[i] is True if there is a pit in the cell, and False if there is 
#   not a pit in the cell.
#   indexed by i = y * width + x
#
# [4] visible is an array with one element per cell.  The value of each element,
#   visible[i] is True if the adventurer has visited the cell, and False if 
#   the adventurer has not visited the cell.
#   indexed by i = y * width + x
#
# [5],[6] wumpus_x, wumpus_y are the coordinates of the cell that contains 
#   the wumpus.
#
# [7],[8] gold_x, gold_y are the coordinates of the cell that contains the gold.
#
# [9] have_gold is True if the adventurer is holding the gold, otherwise 
#   it is False.
#
# [10] have_arrow is True if the adventurer is still holding the arrow, 
#   otherwise it is False.
#
# [11] is_alive is True if the adventurer has not fallen in a pit and has not
#   been eaten by the wumpus.  Otherwise, it is False.
# 

#
# Functions to set and get data from the wumpus world data array.
# These functions do not understand the data.  They just save it to and
# retrieve it from the correct location in the array.
# 
def setDimensions(data, width, height):
    data[0] = width
    data[1] = height
    
def getDimensions(data):
    return (data[0], data[1])

def setCellSize(data, cell_size):
    data[2] = cell_size
    
def getCellSize(data):
    return data[2]

def setPits(data, pits):
    data[3] = pits
    
def getPits(data):
    return data[3]

def setVisible(data, visible):
    data[4] = visible
    
def getVisible(data):
    return data[4]

def setWumpusPosition(data, x, y):
    data[5] = x
    data[6] = y
    
def getWumpusPosition(data):
    return (data[5], data[6])
    
def setGoldPosition(data, x, y):
    data[7] = x
    data[8] = y
    
def getGoldPosition(data):
    return (data[7], data[8])
    
def setHaveGold(data, have_gold):
    data[9] = have_gold
    
def getHaveGold(data):
    return data[9]
    
def setHaveArrow(data, have_arrow):
    data[10] = have_arrow
    
def getHaveArrow(data):
    return data[10]
    
def setIsAlive(data, is_alive):
    data[11] = is_alive
    
def getIsAlive(data):
    return data[11]

#
# This function intializes a single wumpus world data set.  The cell at 0,0
# has no pits, wumpus or gold.  All other cells in the cavern have a 20% 
# chance of containing a pit.  The wumpus is randomly put in one of the
# cells.  The gold is randomly put in one of the cells.  The adventurer does not
# start with the gold, but does start with the arrow, and is alive.
#
def initializeData(width, height, cell_size, debug=0):
    pits = []
    visible = []
    if debug == 0:
        for y in range(0,height):
            for x in range(0,width):
                r = random.randint(1,10)
                if r < 3: # 20% chance of pit
                    pits.append(True)
                else:
                    pits.append(False)
                visible.append(False)
        pits[0]    = False
        visible[0] = True

        (wumpus_x, wumpus_y) = (0, 0)
        while wumpus_x == 0 and wumpus_y == 0:
            wumpus_x = random.randint(0,width-1)
            wumpus_y = random.randint(0,height-1)
        
        (gold_x, gold_y) = (0, 0)
        while gold_x == 0 and gold_y == 0:
            gold_x = random.randint(0,width-1)
            gold_y = random.randint(0,height-1)
            
    elif debug == 1:
        width  = 4
        height = 4
        pits = [ False, False, False, False,
                 False, False, True, False,
                 False, False, False, False,
                 False, False, False, True ]
        visible = [ True, False, False, False,
                    False, False, False, False,
                    False, False, False, False,
                    False, False, False, False ]
        (wumpus_x, wumpus_y) = (3, 0)
        (gold_x, gold_y) = (0, 3)
        
    elif debug == 2:
        width  = 4
        height = 4
        pits = [ False, False, False, False,
                 False, False, True, False,
                 False, False, False, False,
                 False, False, False, True ]
        visible = [ True, True, True, True,
                    True, True, True, True,
                    True, True, True, True,
                    True, True, True, True ]
        (wumpus_x, wumpus_y) = (3, 0)
        (gold_x, gold_y) = (0, 3)
    
    have_gold  = False
    have_arrow = True
    is_alive   = True

    data = []
    data.append(width)
    data.append(height)
    data.append(cell_size)
    data.append(pits)
    data.append(visible)
    data.append(wumpus_x)
    data.append(wumpus_y)
    data.append(gold_x)
    data.append(gold_y)
    data.append(have_gold)
    data.append(have_arrow)
    data.append(is_alive)
    
    return data


