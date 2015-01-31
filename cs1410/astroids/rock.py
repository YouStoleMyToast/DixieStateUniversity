import config
import math
import point
from polygon import Polygon
import pygame
import random


class Rock(Polygon):
    def __init__(self, position, rotation, color, rotationspeed, rockspeed):
        self.position=position
        self.rotation=rotation
        self.color=color
        self.rotationspeed=rotationspeed
        self.points=[]
        for i in range(0, 360, 360/config.ROCK_POLYGON_SIZE):
            radius = random.uniform(config.ROCK_MIN_RADIUS, config.ROCK_MAX_RADIUS)
            r = math.radians(i)
            x = (math.cos(r) * radius)
            y = (math.sin(r) * radius)
            self.points.append(point.Point(x, y))
        Polygon.__init__(self, self.points, position, rotation, color)
        self.rockspeed=rockspeed
        self.accelerate(self.rockspeed)
    
    def game_logic(self, keys, newkeys):
        if self.is_active()==True:
            self.rotate(self.rotationspeed)
            self.move()


    
