from bottle import get, post, run, request, response
from bottle import redirect, debug, static_file
import xmlrpclib
from page import *

DB_ADDRESS = 'http://youface.cs.dixie.edu/'
DB_SERVER = None

def main():
    global DB_SERVER, DB_ADDRESS

    print 'Using YouFace server at', DB_ADDRESS
    DB_SERVER = xmlrpclib.ServerProxy(DB_ADDRESS, allow_none=True)
    debug(True)
    run(host='localhost', port=8080, reloader=True)

@get('/youface.css')
def stylesheet():
    return static_file('youface.css', root='./')

@get('/loginscreen')
def loginscreen():
    return str(LoginPage())

@get('/')
def index():
    name = request.COOKIES.get('name','')
    password = request.COOKIES.get('password','')
    (status, friends) = DB_SERVER.listFriends(name, password)
    if status != 'success':
        redirect ('/loginscreen')
    (status, updates) = DB_SERVER.listStatusFriends(name, password, 25)
    if status != 'success':
        redirect ('/loginscreen')
    return str(FeedPage(name,updates,friends))

@get('/friend/:fname')
def friend(fname):
    name=request.COOKIES.get('name','')
    password=request.COOKIES.get('password','')
    (status, friends) = DB_SERVER.listFriends(name, password)
    if status != 'success':
        redirect ('/loginscreen') 
    (status, updates) = DB_SERVER.listStatusUser(name, password, fname, 25)
    if status != 'success':
        redirect ('/loginscreen') 
    return str(FriendPage(fname, status, friends))

@post('/status')
def SetStatus():
    name=request.COOKIES.get('name','')
    password=request.COOKIES.get('password','')
    message=request.forms.get('status')
    (status, message)=DB_SERVER.setStatus(name,password, message)
    redirect('/')

@post('/addfriend')
def addfriend():
    name=request.COOKIES.get('name','')
    password=request.COOKIES.get('password','')
    friend=request.forms.get('name')
    (status, message)=DB_SERVER.addFriend(name,password,friend)
    redirect('/')

@post('/unfriend')
def unfriend():
    name=request.COOKIES.get('name','')
    password=request.COOKIES.get('password','')
    friend=request.forms.get('name')
    (status,message)=DB_SERVER.unFriend(name, password, friend)
    redirect('/')
    
@post('/login')
def login():
    name = request.forms.get('name')
    password = request.forms.get('password')

    response.set_cookie('name', name, path='/')
    response.set_cookie('password', password, path='/')
    button=request.forms.get('type')

    if button=='Create':
        (status, mes) = DB_SERVER.newUser(name, password)
    elif button=='Delete':
        (status, mes) = DB_SERVER.deleteUser(name, password)
    redirect('/')
    
@post('/logout')
def logout():
    response.set_cookie('name','', path='/')
    response.set_cookie('password','', path='/')
    redirect('/')
     
if __name__ == '__main__':
    main()
