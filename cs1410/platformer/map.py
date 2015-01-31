import pygame
import tileset

class Map():
    def __init__(self, filename, tiles, screen, view_x, view_y):
        self.filename=filename
        self.tiles=tiles
        self.screen=screen
        self.view_x=view_x
        self.view_y=view_y
        
        filename=open(self.filename)
        filecontents=filename.read()
        self.map = eval(filecontents)
        filename.close()

    def getSize(self):
        self.cols=len(self.map)
        self.rows=len(self.map[0])
        return(self.rows,self.cols)

    def getViewSize(self):
        viewsize=(self.view_x,self.view_y)
        return viewsize

    def getTileNumber(self,x,y):
        if x<0 or y<0 or y>=self.cols or x>=self.rows:
            return None
        else:
            return self.map[y][x]

    def getTileNumberAt(self,x,y):
        (x,y)=self.tiles.getTileCoordsAt(x,y)
        num=self.getTileNumber(x,y)
        return num

    def getTile(self,x,y):
        num=self.getTileNumber(x,y)
        if num==None:
            return self.tiles.getBackgroundTile()
        else:
            return self.tiles.getTile(num)

    def isSolidAt(self,x,y):
        tnum=self.getTileNumberAt(x,y)
        return self.tiles.isSolid(tnum) or tnum==None

    def iscube(self,x,y):
        cnum=self.getTileNumberAt(x,y)
        return self.tiles.cube(cnum)

    def willkill(self,x,y):
        knum=self.getTileNumberAt(x,y)
        return self.tiles.isdeadly(knum)

    def lasser(self,x,y):
        lnum=self.getTileNumberAt(x,y)
        return self.tiles.lassertile(lnum)

    def cake(self,x,y):
        cnum=self.getTileNumberAt(x,y)
        return self.tiles.caketile(cnum)

    def isswitch(self,x,y):
        snum=self.getTileNumberAt(x,y)
        return self.tiles.switch(snum)

    def isbutton(self,x,y):
        bnum=self.getTileNumberAt(x,y)
        return self.tiles.button(bnum)

    def opendoor(self,x,y):
        onum=self.getTileNumberAt(x,y)
        return self.tiles.opendoor4(onum)
    
    def drawMap(self,left,top):
        (x,y)=self.tiles.getTileSize()
        (corner_x, corner_y) = (left / x, top / y)
        (offset_x, offset_y) = (left % x, top % y)
        for i in range(self.view_y+1):
            map_y = i + corner_y
            for j in range(self.view_x+1):
                map_x = j + corner_x
                tile=self.getTile(map_x, map_y)
                pos=(j * x - offset_x, i * y - offset_y)
                self.screen.blit(tile, pos)

