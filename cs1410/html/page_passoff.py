from page import *

import difflib

def compare(lines, filename):
    f = open(filename, "r")
    filelines = f.readlines()
    f.close()
    diffs = difflib.context_diff(lines, filelines, fromfile='Your Code', tofile=filename)
    count = 0
    for l in diffs:
        print l,
        count += 1
    return count == 0

def add_newline(s):
    s += '\n'
    return s

def object_to_string_list(obj):
    s = str(obj)
    lst = s.split('\n')
    lst = map(add_newline, lst)
    return lst

def main():
    loginpage = object_to_string_list(LoginPage())
    if compare(loginpage, "login-mockup.html"):
        print "LoginPage is correct."
    print
    
    name = 'Alice'
    status = ['working on cs1410', 'eating lunch', 'sleeping in class']
    friends = ['Bob', 'Charlie', 'Dorothy']
    feedpage = object_to_string_list(FeedPage(name, status, friends))
    if compare(feedpage, "feed-mockup.html"):
        print "FeedPage is correct."
    print
    
    name = 'Bob'
    status = ['eating lunch', 'driving while online']
    friends = ['Alice', 'Dorothy']
    friendpage = object_to_string_list(FriendPage(name, status, friends))
    if compare(friendpage, "friend-mockup.html"):
        print "FriendPage is correct."
    print
    


main()




