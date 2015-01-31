# Eric Beilmann
# This code creates a random maze, and draws it.
# You must enhance this code to solve the maze, and to draw the solution

from graphics import *
import random

M = 5
N = 4
CELL_SIZE = 100
MARGIN = 10
screen_x = M*CELL_SIZE + 2*MARGIN
screen_y = N*CELL_SIZE + 2*MARGIN

class Cell:
    def __init__(self):
        self.l = self.t = self.r = self.b = True
        self.visited = False

    def Draw(self, win, i,j):
        x1 = MARGIN + i*CELL_SIZE
        y1 = MARGIN + j*CELL_SIZE
        x2 = x1 + CELL_SIZE
        y2 = y1 + CELL_SIZE
        if self.l:
            line = Line( Point(x1,y1), Point(x1,y2) )
            line.draw(win)
        if self.t:
            line = Line( Point(x1,y1), Point(x2,y1) )
            line.draw(win)
        if self.r:
            line = Line( Point(x2,y1), Point(x2,y2) )
            line.draw(win)
        if self.b:
            line = Line( Point(x1,y2), Point(x2,y2) )
            line.draw(win)
class Maze:
    def __init__(self):
        self.cells = []
        for i in range(M):
            cellColumn = []
            for j in range(N):
                cellColumn.append(Cell())
            self.cells.append(cellColumn)
        self.VisitR(0,0)
        self.cells[0][0].t = False
        self.cells[M-1][N-1].b = False
        self.index=0
        
    def VisitR(self, i,j):
        self.cells[i][j].visited = True
        while True:
            nexti = []
            nextj = []
            # determine which cells we could move to next
            if i>0 and not self.cells[i-1][j].visited: # left
                nexti.append(i-1)
                nextj.append(j)
            if i<M-1 and not self.cells[i+1][j].visited: # right
                nexti.append(i+1)
                nextj.append(j)
            if j>0 and not self.cells[i][j-1].visited: # up
                nexti.append(i)
                nextj.append(j-1)
            if j<N-1 and not self.cells[i][j+1].visited: # down
                nexti.append(i)
                nextj.append(j+1)

            if len(nexti) == 0:
                return # nowhere to go from here

            # randomly choose 1 direction to go
            index = random.randrange(len(nexti))
            ni = nexti[index]
            nj = nextj[index]

            # knock out walls between this cell and the next cell
            if ni == i+1: # right move
                self.cells[i][j].r = self.cells[i+1][j].l = False
            if ni == i-1: # left move
                self.cells[i][j].l = self.cells[i-1][j].r = False
            if nj == j+1: # down move
                self.cells[i][j].b = self.cells[i][j+1].t = False
            if nj == j-1: # up move
                self.cells[i][j].t = self.cells[i][j-1].b = False

            # recursively visit the next cell
            self.VisitR(ni,nj)
            
    def Draw(self, win):
        for i in range(M):
            for j in range(N):
                self.cells[i][j].Draw(win,i,j)
        

    # Write this method.
    # It should return True if this is the end cell, OR if it leads to the end cell.
    # It should return False if this is a loser cell.
    def SolveR( self, i,  j):
        while i<M-1 and j<N-1:
            # Mark this cell as visited.
            print 'i',i
            print 'j',j
            self.cells[i][j].visited=True
            # Get index number of this cell
            index=j*M+i
            self.mMoves.append(self.index)
            #Record the index in the class variable mMoves.
            # If we are at the end cell, return true.
            if i==M and j==N:
                return True
            
            # move left if there is no wall, and it hasn't been visited. Return true if it returns true.
            elif self.cells[i][j].l==False and self.cells[i-1][j].visited==False:
                print 'current cell visited',self.cells[i][j].visited
                
                print 'new cell visited',self.cells[i][j].visited
                print 'moves',self.mMoves
                print 'self.cells[i][j].l',self.cells[i][j].l
                print 'self.cells[i][j].r',self.cells[i][j].r
                print 'self.cells[i][j].b',self.cells[i][j].b
                print 'self.cells[i][j].t',self.cells[i][j].t
                print 'you go left'
                self.SolveR(i,j)
                #return True
            # move right if there is no wall, and it hasn't been visited. Return true if it returns true.
            elif self.cells[i][j].r==False and self.cells[i+1][j].visited==False:
                print 'current cell visited',self.cells[i][j].visited
                i=self.index%M
                j=self.index/M
                print 'new cell visited',self.cells[i][j].visited
                print 'moves',self.mMoves
                print 'self.cells[i][j].l',self.cells[i][j].l
                print 'self.cells[i][j].r',self.cells[i][j].r
                print 'self.cells[i][j].b',self.cells[i][j].b
                print 'self.cells[i][j].t',self.cells[i][j].t
                print 'you go right'
                self.SolveR(i,j)
                #return True
            # move down if there is no wall, and it hasn't been visited. Return true if it returns true.
            elif self.cells[i][j].b==False and self.cells[i][j+1].visited==False:
                print 'current cell visited',self.cells[i][j].visited
                i=self.index%M
                j=self.index/M
                print i
                print j
                print 'new cell visited',self.cells[i][j].visited
                print 'moves',self.mMoves
                print 'self.cells[i][j].l',self.cells[i][j].l
                print 'self.cells[i][j].r',self.cells[i][j].r
                print 'self.cells[i][j].b',self.cells[i][j].b
                print 'self.cells[i][j].t',self.cells[i][j].t
                print 'you go down'
                self.SolveR(i,j)
                #return True
            # move up if there is no wall, and it hasn't been visited. Return true if it returns true.
            elif self.cells[i][j].t==False and self.cells[i][j-1].visited==False:
                print 'current cell visited',self.cells[i][j].visited
                i=self.index%M
                j=self.index/M
                print 'new cell visited',self.cells[i][j].visited
                print 'moves',self.mMoves
                print 'self.cells[i][j].l',self.cells[i][j].l
                print 'self.cells[i][j].r',self.cells[i][j].r
                print 'self.cells[i][j].b',self.cells[i][j].b
                print 'self.cells[i][j].t',self.cells[i][j].t
                print 'you go up'
                self.SolveR(i,j)
                #return True

            # This is a loser cell, so undo the move from self.mMoves, and return false to the previous cell.
            else:
                x=self.mMoves.pop()
                i=x%M
                j=x/M
                print 'pop i',i
                print 'pop j',j
                return False


    # Write this method.
    # Use a depth first search.
    def Solve(self):
        self.mMoves=[]
        # Initialize mMoves array
        for i in range(M):
            for j in range(N):
                self.cells[i][j].visited=False
                
        # Initialize all cells to not visited
        # Start searching recursively from 0,0
        i=0
        j=0
        self.SolveR(i,j)

    # Write this method.
    def DrawSolution(self, win):
        for k in range(len(self.mMoves)-1):
            i=0
            j=0
            icenter=self.mMoves[k]%M*CELL_SIZE+CELL_SIZE/2
            jcenter=self.mMoves[k]/M*CELL_SIZE+CELL_SIZE/2
            nexticenter=self.mMoves[k+1]%M*CELL_SIZE+CELL_SIZE/2
            nextjcenter=self.mMoves[k+1]/M*CELL_SIZE+CELL_SIZE/2
            line = Line(Point(icenter,jcenter), Point(nexticenter,nextjcenter))
            line.draw(win)

def main():
    win = GraphWin("Maze Solver", screen_x, screen_y)
    theMaze = Maze()
    theMaze.Draw(win)
    theMaze.Solve()
    theMaze.DrawSolution(win)

main()

    
