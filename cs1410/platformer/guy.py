import config
import math
import pygame

class Guy:
    def __init__(self,tiles,map,screen,x,y):
        self.Tileset=tiles
        self.Map=map
        self.screen=screen
        self.x=x
        self.y=y

        self.startx=x
        self.starty=y

        self.faceright=True
        self.footdown=True
        self.dx=0.0
        self.dy=0.0
        self.steps=0
        self.death=False
        self.carrying=False
        self.levelchange=False
        self.button=False
        self.mouse_x=0
        self.mouse_y=0
        

        
    def pushX(self,ddx):
        self.dx+=ddx
        maxx=config.MAXIMUM_RATE_X
        if self.dx>maxx:
            self.dx=maxx
        elif self.dx<-maxx:
            self.dx=-maxx
        if self.dx<0.0:
            self.faceright=False
        elif self.dx>0.0:
            self.faceright=True

    def pushY(self,ddy):
        self.dy+=ddy
        maxy=config.MAXIMUM_RATE_Y
        if self.dy>maxy:
            self.dy=maxy
        elif self.dy<-maxy:
            self.dy=-maxy

    def left(self):
        self.pushX(-config.ACCELERATION_PER_FRAME)

    def right(self):
        self.pushX(config.ACCELERATION_PER_FRAME)

    def friction(self):
        fri=config.FRICTION_PER_FRAME
        if self.dx>0.0:
            self.pushX(max(-fri,-self.dx))
        elif self.dx<0.0:
            self.pushX(min(fri,-self.dx))

    def gravity(self):
        g=config.GRAVITY_PER_FRAME
        self.pushY(g)

    def jump(self):
        maxy=config.MAXIMUM_RATE_Y
        if self.feetOnGround():
            self.pushY(2.0*-maxy)
    
    def roundUp(self, n):
        to = config.MINIMUM_PIXELS_PER_FRAME
        return ((int(math.ceil(n)) + to-1) / to) * to

    def move(self):
        xMove=self.roundUp(abs(self.dx))
        if self.dx > 0.0:
            xSign = 1
        else:
            xSign = -1
        yMove=self.roundUp(abs(self.dy))
        if self.dy > 0.0:
            ySign = 1
        else:
            ySign = -1

        for i in range(xMove):
            if self.collision(self.x+xSign,self.y):
                self.dx=0.0
                xMove=i
                break
            else:
                self.x+=xSign

        for i in range(yMove):
            if self.collision(self.x,self.y+ySign):
                self.dy=0.0
                break
            else:
                self.y+=ySign

        self.steps=(xMove+self.steps)%(2*config.PIXELS_PER_STEP)
        if self.steps>=0 and self.steps<config.PIXELS_PER_STEP:
            self.footdown=False
        else:
            self.footdown=True

        if abs(self.dx)<0.01:
            self.steps=0
            self.footdown=True

        if not self.feetOnGround():
            self.footdown=False
            self.steps=0
            
        if self.death==True:
            self.death=False
            self.x=self.startx
            self.y=self.starty

    def shoot(self): 
        red=self.Tileset.red()
        blue=self.Tileset.blue()
        ball=self.Tileset.ball()
        pygame.event.get()
        if event.type==MOUSEBUTTONDOWN:
            self.screen.blit(self.Tileset.getTile(red), (self.mouse_x, self.mouse_y))
        elif event.type==MOUSEBUTTONDOWN:
            self.screen.blit(self.Tileset.getTile(blue), (self.mouse_x, self.mouse_y))

    def act(self):
        left=self.x+config.HOWSLIM
        right=self.x+self.Tileset.tile_size_x-1-config.HOWSLIM
        top=self.y
        bottom=self.y+self.Tileset.tile_size_y-1
        cube=self.Tileset.cube(25)
        door1=self.Tileset.opendoor1(3)
        door2=self.Tileset.opendoor2(4)
        door3=self.Tileset.opendoor3(8)
        door4=self.Tileset.opendoor4(9)
        
        if self.Map.isswitch(left,top) or self.Map.isswitch(right,top) or self.Map.isswitch(left,bottom) or self.Map.isswitch(right,bottom):
            self.screen.blit(self.Tileset.getTile(cube), (self.x, self.y))
            pygame.display.flip()

        elif self.carrying==True:
            self.carrying=False
        elif self.carrying==False:
            self.carrying=True
    
    def collision(self, x, y):
        swamp=self.Tileset.getTile(20)
        left=x+config.HOWSLIM
        right=x+self.Tileset.tile_size_x-1-config.HOWSLIM
        top=y
        bottom=y+self.Tileset.tile_size_y-1
        if (self.Map.willkill(left,bottom-75) or self.Map.willkill(right,bottom-75)):
            self.death=True
        if self.Map.lasser(left,bottom) or self.Map.lasser(right,bottom):
            self.playturretdeath()
            self.death=True
            
        if self.Map.isbutton(left,top) or self.Map.isbutton(right,top) or self.Map.isbutton(left,bottom) or self.Map.isbutton(right,bottom):
            self.button=True
##        else:
##            self.button=False

        if self.Map.opendoor(left,top) or self.Map.opendoor(right,top) or self.Map.opendoor(left,bottom) or self.Map.opendoor(right,bottom):
            self.levelchange=True

        if self.Map.cake(left,top) or self.Map.cake(right,top) or self.Map.cake(left,bottom) or self.Map.cake(right,bottom):
            self.playfinish()
##            self.levelchange=True
            
        if self.Map.isSolidAt(left,top) or self.Map.isSolidAt(right,top) or self.Map.isSolidAt(left,bottom) or self.Map.isSolidAt(right,bottom):
            return True
        else:
            return False
        
    def playintro(self):
            pygame.mixer.init()
            pygame.mixer.music.load('GLaDOS_10_part1_entry-2.wav')
            pygame.mixer.music.set_volume(1.0)
            pygame.mixer.music.play(0,0.0)

    def playfinish(self):
            pygame.mixer.init()
            pygame.mixer.music.load('GLaDOS_15_part1_into_the_fire-1.wav')
            pygame.mixer.music.set_volume(1.0)
            pygame.mixer.music.play(0,0.0)

    def playturretdeath(self):
            pygame.mixer.init()
            pygame.mixer.music.load('Turret_turret_active_6.wav')
            pygame.mixer.music.set_volume(1.0)
            pygame.mixer.music.play(0,0.0)
            
    def feetOnGround(self):
        return self.collision(self.x, self.y+1)
        
    def drawGuy(self):
        x = (self.Map.view_x - 1) / 2 * self.Tileset.tile_size_x
        y = (self.Map.view_y - 1) / 2 * self.Tileset.tile_size_y

        char1=self.Tileset.getFirstCharacterTileNumber()
        char2=self.Tileset.getFirstCharacterTileNumber()+1
        char3=self.Tileset.getFirstCharacterTileNumber()+2
        char4=self.Tileset.getFirstCharacterTileNumber()+3
        
        if self.faceright==False and self.footdown==False:
            self.screen.blit(self.Tileset.getTile(char1), (x, y))
        elif self.faceright==False and self.footdown==True:
            self.screen.blit(self.Tileset.getTile(char2), (x, y))
        elif self.faceright==True and self.footdown==True:
            self.screen.blit(self.Tileset.getTile(char3), (x, y))
        elif self.faceright==True and self.footdown==False:
            self.screen.blit(self.Tileset.getTile(char4), (x, y))

        cube=self.Tileset.cube(25)
        
        if self.carrying==True:
            if self.faceright==False and self.footdown==False:
                self.screen.blit(self.Tileset.getTile(cube), (x-self.Tileset.tile_size_x, y))
            elif self.faceright==False and self.footdown==True:
                self.screen.blit(self.Tileset.getTile(cube), (x-self.Tileset.tile_size_x, y))
            elif self.faceright==True and self.footdown==True:
                self.screen.blit(self.Tileset.getTile(cube), (x+self.Tileset.tile_size_x, y))
            elif self.faceright==True and self.footdown==False:
                self.screen.blit(self.Tileset.getTile(cube), (x+self.Tileset.tile_size_x, y))

        width=len(self.Map.map[0])
        height=len(self.Map.map)
        
        if self.button==True:
            self.Map.map[height-3][width-4]=3
            self.Map.map[height-3][width-3]=4
            self.Map.map[height-2][width-4]=8
            self.Map.map[height-2][width-3]=9

##        if self.button==False:
##            self.Map.map[height-3][width-4]=1
##            self.Map.map[height-3][width-3]=2
##            self.Map.map[height-2][width-4]=6
##            self.Map.map[height-2][width-3]=7

            
    def repaint(self):
        x = self.x - (((self.Map.view_x -1)/ 2) * self.Tileset.tile_size_x)
        y = self.y - (((self.Map.view_y -1)/ 2) * self.Tileset.tile_size_y)
        
        self.Map.drawMap(x,y)
        self.drawGuy()
















    
