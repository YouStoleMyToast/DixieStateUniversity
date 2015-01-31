import pygame
import game
import math

class Circle(game.Game):
    def __init__(self):
        game.Game.__init__(self, 'Circle demo', 500, 500, 60)
        image = pygame.image.load('tiles.png')
        r1 = pygame.rect.Rect(64, 64, 32, 32)
        self.tile1 = image.subsurface(r1)
        r2 = pygame.rect.Rect(96, 64, 32, 32)
        self.tile2 = image.subsurface(r2)
        self.degrees = 0.0

    def game_logic(self, keys, newkeys):
        self.degrees = (self.degrees + 1.0) % 360.0

    def paint(self, surface):
        radians = self.degrees / 360.0 * 2.0 * math.pi
        x = math.cos(radians) * 200.0 + 250.0 - 16.0
        y = math.sin(radians) * 200.0 + 250.0 - 16.0

        surface.fill(pygame.Color('black'))
        if self.degrees % 6.0 < 3.0:
            surface.blit(self.tile1, (x, y))
        else:
            surface.blit(self.tile2, (x, y))

def main():
    circle = Circle()
    circle.main_loop()

if __name__ == '__main__':
    main()
