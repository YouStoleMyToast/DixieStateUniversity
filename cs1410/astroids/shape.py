import math
import config
import point

class Shape:
    def __init__(self, position, rotation, color):
        self.position=position
        self.rotation=rotation
        self.color=color
        self.dx=0
        self.dy=0
        self.active=False

    def paint(self, surface):
        raise NotImplementedError()
    
    def game_logic(self, keys, newkeys):
        raise NotImplementedError()

    def move(self):       
        new = self.position
        new.x+=self.dx
        new.y+=self.dy
        (x, y) = new.x, new.y
        if x>config.SCREEN_X:
            x-=config.SCREEN_X
        if x<0:
            x+=config.SCREEN_X
        if y>config.SCREEN_Y:
            y-=config.SCREEN_Y
        if y<0:
            y+=config.SCREEN_Y
        self.position = point.Point(x, y)

    def accelerate(self, acceleration):
        angleinradians=math.radians(self.rotation)
        self.dx = self.dx + acceleration * math.cos(angleinradians)
        self.dy = self.dy + acceleration * math.sin(angleinradians)

    def intersect(self, other_polygon):
        points=self.getPoints()
        for i in points:
            if other_polygon.contains(i):
                return True
        points=other_polygon.getPoints()
        for i in points:
            if self.contains(i):
                return True
        return False

    def contains(self, point):
        raise NotImplementedError()

    def getPoints(self):
        raise NotImplementedError()

    def get_rotation(self):
        return self.rotation

    def set_active(self):
        self.active=True



        
