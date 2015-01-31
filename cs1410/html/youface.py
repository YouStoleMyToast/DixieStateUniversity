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
    return 'Hello, world!'











if __name__ == '__main__':
    main()
