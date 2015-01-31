from circle import Circle
import config
import random
import point

class Star(Circle):
    def __init__(self, position, radius, rotation, color):
        Circle.__init__(self, position, radius, rotation, color)
        self.sposition=point.Point(random.randint(0,config.SCREEN_X),random.randint(0,config.SCREEN_Y))
        self.sradius=config.STAR_RADIUS
        self.srotation=0.0
        self.scolornum=random.uniform(0,255)
        self.color=(self.scolornum, self.scolornum, self.scolornum)
        self.add=True

    def game_logic(self, keys, newkeys):
        if self.add==True:
            self.scolornum+=random.uniform(0,config.STAR_TWINKLE_SPEED)
            if self.scolornum >=255:
                self.scolornum=255
            self.color=(self.scolornum, self.scolornum, self.scolornum)
            self.add=False
            
        if self.add==False:
            self.scolornum-=random.uniform(0,config.STAR_TWINKLE_SPEED)
            if self.scolornum <=0:
                self.scolornum=0
            self.color=(self.scolornum, self.scolornum, self.scolornum)
            self.add=True
