from circle import Circle
import config

class Bullet(Circle):
    def __init__(self, position, radius, rotation, color):
        Circle.__init__(self, position, radius, rotation, color)
        self.position=position
        self.dx=0
        self.dy=0
        self.active=False
        self.onscreen=True

    def game_logic(self, keys, newkeys):
        new = self.position
        (x, y) = new.x, new.y
        if self.active==False:
            return
        if self.active==True and self.onscreen==True:
            if x+self.dx>config.SCREEN_X:
                self.onscreen==False
            if x+self.dx<0:
                self.onscreen==False
            if y+self.dy>config.SCREEN_Y:
                self.onscreen==False
            if y+self.dy<0:
                self.onscreen==False
            self.move()
        if self.onscreen==False:
            self.active=False
            self.onscreen=True

    def fire(self, position, rotation):
        self.position=position
        self.rotation=rotation
        self.set_active()
        self.dx=0
        self.dy=0
        self.accelerate(config.BULLET_SPEED)

        
        
