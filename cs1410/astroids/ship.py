from polygon import Polygon
import pygame
import point
import config
import math

class Ship(Polygon):
    def __init__(self, position, rotation, color):
        self.position=position
        self.rotation=rotation
        self.color=color
        self.points=[point.Point(400, 300), point.Point(360,290), point.Point(360,310)]
        Polygon.__init__(self, self.points, position, rotation, color)
        
    def game_logic(self, keys, newkeys):
        if pygame.K_LEFT in keys:
            self.rotation-=config.SHIP_ROTATION_RATE
        if pygame.K_RIGHT in keys:
            self.rotation+=config.SHIP_ROTATION_RATE
        if pygame.K_UP in keys:
            self.accelerate(config.SHIP_ACCELERATION_RATE)
        if pygame.K_DOWN in keys:
            self.accelerate(-config.SHIP_ACCELERATION_RATE)
        if self.active==True:
            self.move()
            

