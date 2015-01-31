import cgi

class Tag:
    def __init__(self, name):
        self.name = name
        self.Id=""
        self.classes=[]
        self.atter=[]
        
    def setId(self,Id):
        self.Id = Id
        return self
        
    def addClass(self,name):
        self.classes.append(name)
        return self
    
    def addAttr(self, key, value):
        self.atter.append((key,value))
        return self
        
    def attrs(self):
        classstr=""
        if self.Id !="":
            value = cgi.escape(self.Id, True)
            classstr +=' id="'+str(value)+'"'
        if len(self.classes) != 0:
            classstr +=' class="'
            for i in range(len(self.classes)):
                if i ==0:
                    value = cgi.escape(self.classes[i], True)
                    classstr +=str(value)
                else:
                    value = cgi.escape(self.classes[i], True)
                    classstr +=" "+str(value)
            classstr +='"'
        if len(self.atter) !=0:
            for i in range(len(self.atter)):
                value = cgi.escape(self.atter[i][1], True)
                classstr +=" "+str(self.atter[i][0]) + '="'+str(value) +'"'
        return classstr

    def makeTag(self, contents):
        classstr=self.attrs()
        if len(contents)==0:
            return '<'+self.name+classstr+' />'
        else:
            return '<'+self.name+classstr+'>'+contents+'</'+self.name+'>'
        
    def __str__(self):
        return self.makeTag('')
    
    def __repr__(self):
        return self.__str__()
        
class BlockTag(Tag):
    def __init__(self, name):
        Tag.__init__(self, name)
        
    def __str__(self):
        return '\n'+Tag.__str__(self)

class Container(Tag):
    def __init__(self, name):
        Tag.__init__(self, name)
        self.child = []
        
    def addTag(self, child):
        self.child.append(child)
        return self
    
    def addText(self,text):
        safetext = cgi.escape(text)
        self.child.append(safetext)
        return self

    def __str__(self):
        cont = ""
        for i in self.child:
            cont += str(i)
        return self.makeTag(cont)
        
class BlockContainer(Container):
    def __init__(self,name):
        Container.__init__(self,name)
        print self.child
        
    def __str__(self):
        t=""
        for i in self.child:
            t += str(i)
        if t.startswith('\n') and not t.endswith('\n'):
            t += '\n'
        return '\n' + self.makeTag(t)
        
#Part 2
class Img(Tag):
    def __init__(self,src,alt):
        Tag.__init__(self,'img')
        self.addAttr('src',src)
        self.addAttr('alt',alt)

class Meta(BlockTag):
    def __init__(self):
        BlockTag.__init__(self,'meta')
        self.addAttr('http-equiv', 'content-type')
        self.addAttr('content', 'text/html; charset=utf-8')

class Stylesheet(BlockTag):
    def __init__(self,href):
        BlockTag.__init__(self,'link')
        self.addAttr('rel','stylesheet')
        self.addAttr('href',href)
        self.addAttr('type','text/css')
        
class Br(Tag):
    def __init__(self):
        Tag.__init__(self,'br')
        
class Hr(Tag):
    def __init__(self):
        Tag.__init__(self,'hr')

class A(Container):
    def __init__(self,target):
        Container.__init__(self,'a')
        self.addAttr('href',target)

class Title(BlockContainer):
    def __init__(self):
        BlockContainer.__init__(self,'title')
        
class Div(BlockContainer):
    def __init__(self):
        BlockContainer.__init__(self,'div')

class Strong(BlockContainer):
    def __init__(self):
        BlockContainer.__init__(self,'strong')

class Em(BlockContainer):
    def __init__(self):
        BlockContainer.__init__(self,'em')

class P(BlockContainer):
    def __init__(self):
        BlockContainer.__init__(self,'p')

class H(BlockContainer):
    def __init__(self,num):
        cnum = int(num)
        if cnum < 1:
            cnum =1
        if cnum > 6:
            cnum =6
        BlockContainer.__init__(self,"h"+str(cnum))
        
class Ul(BlockContainer):
    def __init__(self):
        BlockContainer.__init__(self,'ul')
        
class Ol(BlockContainer):
    def __init__(self):
        BlockContainer.__init__(self,'ol')

class Li(BlockContainer):
    def __init__(self):
        BlockContainer.__init__(self,'li')

class Head(BlockContainer):
    def __init__(self):
        BlockContainer.__init__(self,'head')

class Body(BlockContainer):
    def __init__(self):
        BlockContainer.__init__(self,'body')

class Html(BlockContainer):
    def __init__(self):
        BlockContainer.__init__(self,'html')
        self.addAttr('xmlns','http://www.w3.org/1999/xhtml')

    def __str__(self):
        openhtml='<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">'
        return openhtml+BlockContainer.__str__(self)
