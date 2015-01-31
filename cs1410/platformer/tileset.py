import pygame

class Tileset():
    def __init__(self, filename, tile_size_x, tile_size_y):
        self.tile_size_x=32
        self.tile_size_y=32
        image=pygame.image.load('portal tileset.png')
        (self.x, self.y)=image.get_size()
        self.x_size = self.x / self.tile_size_x
        self.y_size = self.y / self.tile_size_y
        self.tiles=[]
        for i in range(self.y_size):
            for j in range(self.x_size):
                r=pygame.rect.Rect(j*self.tile_size_x, i*self.tile_size_y, self.tile_size_x, self.tile_size_y)
                self.tiles.append(image.subsurface(r))

    def getTileSize(self):
        i=self.tile_size_x
        j=self.tile_size_y
        return (i,j)

    def getTileCoordsAt(self,x,y):
        k=x/self.tile_size_x
        l=y/self.tile_size_y
        return (k, l)

    def getTile(self,tilenumber):
        return self.tiles[tilenumber]

    def getBackgroundTile(self):
        return self.tiles[11]

    def getFirstCharacterTileNumber(self):
        return self.x_size *3

    def isSolid(self,tilenumber):
        return self.x_size*2 <= tilenumber and self.x_size*3 > tilenumber

    def isdeadly(self,tilenumber):
        return tilenumber==20

    def lassertile(self,tilenumber):
        return tilenumber==21 or tilenumber==22 or tilenumber==23

    def caketile(self,tilenumber):
        return tilenumber==27

    def ball(self, tilenumber):
        return tilenumber==19

    def red(self, tilenumber):
        return tilenumber==24

    def blue(self, tilenumber):
        return tilenumber==29

    def cube(self, tilenumber):
        return 25

    def switch(self, tilenumber):
        return tilenumber==28

    def button(self, tilenumber):
        return tilenumber==26

    def opendoor1(self, tilenumber):
        return tilenumber==3

    def opendoor2(self, tilenumber):
        return tilenumber==4

    def opendoor3(self, tilenumber):
        return tilenumber==8
    
    def opendoor4(self, tilenumber):
        return tilenumber==9
