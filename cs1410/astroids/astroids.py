import config
import game
import point
import polygon
import pygame
import random
import rock
from bullet import Bullet
from polygon import Polygon
from ship import Ship
from star import Star

class Astroids(game.Game):
    def __init__(self, name, screen_x, screen_y, frames_per_second):
        self.name=config.TITLE
        self.screen_x=config.SCREEN_X
        self.screen_y=config.SCREEN_Y
        self.frames_per_second=config.FRAMES_PER_SECOND
        game.Game.__init__(self, config.TITLE,config.SCREEN_X,config.SCREEN_Y)

        self.shipshape=[point.Point(400, 300), point.Point(360,290), point.Point(360,310)]
        self.center=point.Point(self.screen_x/2, self.screen_y/2)
        self.rotation=config.SHIP_INITIAL_DIRECTION
        self.color=config.SHIP_COLOR
        self.ship=Ship(self.center, self.rotation, self.color)
        self.rocks=[]
        for i in range(config.ROCK_COUNT):
            self.rockspeed=random.uniform(config.ROCK_MIN_SPEED,config.ROCK_MAX_SPEED)
            self.rotationspeed=random.uniform(config.ROCK_MIN_ROTATION_SPEED,config.ROCK_MAX_ROTATION_SPEED) * random.randrange(-1, 2, 2)
            self.rockplace=point.Point(random.randint(0,config.SCREEN_X),random.randint(0,config.SCREEN_Y))
            self.rock=rock.Rock(self.rockplace,random.uniform(0.0,359.99),config.ROCK_COLOR,self.rotationspeed, self.rockspeed)
            self.rocks.append(self.rock)

        self.bposition=self.ship.getPoints()[0]
        self.brotation=self.ship.get_rotation()
        self.bradius=config.BULLET_RADIUS
        self.bcolor=config.BULLET_COLOR
        self.bullet=Bullet(self.bposition, self.bradius, self.brotation, self.bcolor)

        self.stars=[]
        for i in range(config.STAR_COUNT):
            self.sposition=point.Point(random.randint(0,config.SCREEN_X),random.randint(0,config.SCREEN_Y))
            self.sradius=config.STAR_RADIUS
            self.srotation=0.0
            self.scolornum=random.uniform(0,255)
            self.scolor=(self.scolornum, self.scolornum, self.scolornum)
            self.star=Star(self.sposition, self.sradius, self.srotation, self.scolor)
            self.stars.append(self.star)
        
    def game_logic(self, keys, newkeys):
        for i in self.stars:
            i.game_logic(keys,newkeys)
        if self.ship.is_active()==True:
            Ship.game_logic(self.ship, keys, newkeys)
        for i in self.rocks:
            if i.is_active()==True:
                if self.ship.intersect(i):
                    self.ship.set_inactive()
                i.game_logic(keys,newkeys)
                
            if i.is_active()==True:
                p=i.getPoints()
                w=self.bullet.getPoints()
                if self.bullet.is_active()==True:
                    for l in p:
                        if self.bullet.contains(l):
                            i.set_inactive()
                            self.bullet.set_inactive()
                    for e in w:
                        if i.contains(e):
                            i.set_inactive()
                            self.bullet.set_inactive()
                
        if pygame.K_SPACE in newkeys:
            if self.ship.is_active()==True:
                self.bposition=self.ship.getPoints()[0]
                self.brotation=self.ship.get_rotation()
                self.bullet.fire(self.bposition,self.brotation)
        self.bullet.game_logic(keys, newkeys)
            
    def paint(self, surface):
        surface.fill(config.BACKGROUND_COLOR)
        for star in self.stars:
            star.paint(surface)
        if self.ship.is_active()==True:
            self.ship.paint(surface)
        for rock in self.rocks:
            if rock.is_active()==True:
                rock.paint(surface)
        if self.bullet.active==True:
            self.bullet.paint(surface)

def main():
    AS=Astroids(config.TITLE, config.SCREEN_X, config.SCREEN_Y, config.FRAMES_PER_SECOND)
    game.Game.main_loop(AS)

main()
