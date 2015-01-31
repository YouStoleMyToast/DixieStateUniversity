from html import *

TITLE = 'YouFace'
SUBTITLE = "A billion dollars and it's yours!"
STYLESHEET = 'youface.css'
LINKLIST = [
    ('http://cit.cs.dixie.edu/cs/cs1410/', 'CS 1410'),
    ('http://new.dixie.edu/reg/syllabus/', 'College calendar'),
]
class Form(BlockContainer):
    def __init__(self,action):
        BlockContainer.__init__(self,'form')
        self.addAttr('method','post')
        self.addAttr('action',action)

class Label(Container):
    def __init__(self,label):
        Container.__init__(self,'label')
        self.addAttr('for',label)

class Input(Tag):
    def __init__(self,text,name):
        Tag.__init__(self,'input')
        self.addAttr('type',text)
        self.addAttr('name',name)

class Box(Div):
    def __init__(self,name):
        Div.__init__(self)
        self.addAttr('class','box')
        t=H(1)
        t.addText(name)
        self.addTag(t)
        
class StatusBox(Box):
    def __init__(self,name):
        Box.__init__(self,'Welcome, '+name)
        self.addTag(Form('/status')
        .addTag(P()
        .addTag(Label('status')
        .addText('Change your status:'))
        .addTag(Input('text','status')))
        .addTag(P()
        .addTag(Input('submit','change')
        .addAttr('value','Change'))))

class RecentActivityBox(Box):
    def __init__(self,activity):
        Box.__init__(self,'Recent status updates')
        u=Ul()
        for i in range(len(activity)):
            u.addTag(Li()
            .addText(activity[i]))
        self.addTag(u)

class UnFriendBox(Box):
    def __init__(self,name):
        Box.__init__(self,'You are currently friends with '+name)
        self.addTag(P()
        .addTag(Form('/unfriend')
        .addTag(Input('hidden','name')
        .addAttr('value',name))
        .addTag(P()
        .addTag(Input('submit','unfriend')
        .addAttr('value','Unfriend')))))
        
class LoginBox(Box):
    def __init__(self):
        Box.__init__(self,'Login')
        self.addTag(Form('/login')
        .addTag(P()
        .addTag(Label('name').addText('Name:'))
        .addTag(Input('text','name')))
        .addTag(P()
        .addTag(Label('password').addText('Password:'))
        .addTag(Input('password','password')))
        .addTag(P()
        .addTag(Input('submit','type').addAttr('value','Login'))
        .addTag(Input('submit','type').addAttr('value','Create'))
        .addTag(Input('submit','type').addAttr('value','Delete'))))

class Gadget(Div):
    def __init__(self,name):
        Div.__init__(self)
        self.addAttr('class','gadget')
        self.addTag(H(1)
        .addText(name))

class LinksGadget(Gadget):
    def __init__ (self,links):
        Gadget.__init__(self,'Links')
        u=Ul()
        for i in range(len(links)):
            (url,text)=links[i]
            u.addTag(Li()
            .addTag(A(url)
            .addText(text)))
        self.addTag(u)
        
class FriendsGadget(Gadget):
    def __init__ (self,friends):
        Gadget.__init__(self,'Friends')
        u=Ul()
        for i in range(len(friends)):
            u.addTag(Li()
            .addTag(A('/friend/'+friends[i])
            .addText(friends[i])))
        self.addTag(u)
        self.addTag(Form('/addfriend')
            .addTag(P()
                .addTag(Input('text','name'))
                .addTag(Input('submit','addfriend').addAttr('value','Add Friend'))
                ))
                    

class LogoutGadget(Gadget):
    def __init__(self):
        Gadget.__init__(self,'Logout')
        self.addTag(Form('/logout')
        .addTag(P()
        .addTag(Input('submit','logout').addAttr('value','Logout'))))
                    
class Page():
    def __init__(self):
        self._html=Html()
        self.boxes=Div().setId('maincolumn')
        self.gadgets=Div().setId('sidebar')

        #set up html page
        self._html.addTag(
            Head()
                .addTag(Meta())
                .addTag(Title().addText(TITLE))
                .addTag(Stylesheet(STYLESHEET))
            ).addTag(Body()
                .addTag(Div().setId('maincontainer')
                .addTag(Div().setId('header')
                    .addTag(H(1).addTag(A('/').addText(TITLE)))
                    .addTag(H(2).addText(SUBTITLE)))
                .addTag(self.boxes)
                .addTag(self.gadgets)))                
        
    def addBox(self, Box):
        self.boxes.addTag(Box)
        
    def addGadget(self, Gadget):
        self.gadgets.addTag(Gadget)

    def __str__(self):
        return str(self._html)

    def __repr__ (self):
        return self.__str__()
  
class LoginPage(Page):
    def __init__(self):
        Page.__init__(self)
        self.addBox(LoginBox())
        self.addGadget(LinksGadget(LINKLIST))

class UserPage(Page):
    def __init__(self, friends):
        Page.__init__(self)
        self.addGadget(LogoutGadget())
        self.addGadget(FriendsGadget(friends))
        self.addGadget(LinksGadget(LINKLIST))
        
class FeedPage(UserPage):
    def __init__(self,user,activity,friends):
        UserPage.__init__(self,friends)
        self.addBox(StatusBox(user))
        self.addBox(RecentActivityBox(activity))

class FriendPage(UserPage):
    def __init__(self,friend,activity,friends):
        UserPage.__init__(self,friends)
        self.addBox(UnFriendBox(friend))
        self.addBox(RecentActivityBox(activity))
