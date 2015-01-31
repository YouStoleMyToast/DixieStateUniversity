from shape import Shape
import pygame
import point
import math
import config

class Circle(Shape):
    def __init__(self, position, radius, rotation, color):  
        self.position=position
        self.radius=radius
        self.rotation=rotation
        self.color=color
        self.active=True

        self.cache_points = (None, None, None)

    def paint(self, surface):
        pygame.draw.circle(surface, self.color, self.position.pair(), int(self.radius))

    def game_logic(self, keys, newkeys):
        NotImplementedError()
        
    def move(self):
        (x, y) = self.position.x+self.dx, self.position.y+self.dy
        self.position = point.Point(x, y)
    
    def rotate(self, degrees):
        pass
   
    def accelerate(self, acceleration):
        angleinradians=math.radians(self.rotation)
        self.dx = self.dx + acceleration * math.cos(angleinradians)
        self.dy = self.dy + acceleration * math.sin(angleinradians)

    def contains(self, point):
        dist_x = self.position.x - point.x
        dist_y = self.position.y - point.y
        return dist_x*dist_x + dist_y*dist_y <= self.radius*self.radius

    def getPoints(self):
        self.points=[]
        for i in range(0,360,360/config.BULLET_POINT_COUNT):
            radius=config.BULLET_RADIUS
            r = math.radians(i)
            x = (math.cos(r) * radius)+self.position.x
            y = (math.sin(r) * radius)+self.position.y
            self.points.append(point.Point(x, y))
        return self.points

    def is_active(self):
        return self.active

    def set_inactive(self):
        self.active=False
