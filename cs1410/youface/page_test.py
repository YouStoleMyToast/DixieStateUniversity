try:
    import html
except ImportError as e:
    print e
    print """Unable to locate your html.py file.  Is it in the same folder as this file?"""
    exit(1)

try:
    from page import *
except ImportError as e:
    print e
    print """Unable to locate your page.py file.  Is it in the same folder as this file?"""
    exit(1)
    
import re


def DoTest(cmd):
    (actual, goal, msg) = cmd()
    if actual == goal:
        print "'%s' ok." % (actual)
        return True
    else:
        print "*** %s ... failed." % (msg)
        print "*** actual: '%s'" % (actual)
        print "*** goal:   '%s'" % (goal)
        print ""
        return False

def DoTests(section, cmd_list):
    errors = 0
    oks    = 0

    for t in cmd_list:
        if DoTest(t):
            oks += 1
        else:
            errors += 1

    print "%s: %d ok, %d failed" % ( section, oks, errors )
    return errors


#
# This section tests the Form class
#
def formtest1():
    """form tag"""
    msg = 'Form.__init__'
    try:
        t = Form('/savedata')
        t.addText('Hello')
        s = str(t)
    except (AttributeError, NameError) as e:
        msg = e
        s = ''
    return (s, '\n<form method="post" action="/savedata">Hello</form>', msg)

def FormTests():
    tests = [ formtest1 ]
    error_count = DoTests('Form', tests)
    print ""
    return error_count


#
# This section tests the Label class
#
def labeltest1():
    """label tag"""
    msg = 'Label.__init__'
    try:
        t = Label('targetelement')
        t.addText('Name:')
        s = str(t)
    except (AttributeError, NameError) as e:
        msg = e
        s = ''
    return (s, '<label for="targetelement">Name:</label>', msg)

def LabelTests():
    tests = [ labeltest1 ]
    error_count = DoTests('Label', tests)
    print ""
    return error_count

#
# This section tests the Input class
#
def inputtest1():
    """input tag"""
    msg = 'Input.__init__'
    try:
        t = Input('text', 'title')
        s = str(t)
    except (AttributeError, NameError) as e:
        msg = e
        s = ''
    return (s, '<input type="text" name="title" />', msg)

def InputTests():
    tests = [ inputtest1 ]
    error_count = DoTests('Input', tests)
    print ""
    return error_count


#
# This section tests the Box class
#
def boxtest1():
    """box class"""
    msg = 'Box.__init__'
    try:
        t = Box('Login')
        s = str(t)
    except (AttributeError, NameError) as e:
        msg = e
        s = ''
    return (s, '\n<div class="box">\n<h1>Login</h1>\n</div>', msg)

def BoxTests():
    tests = [ boxtest1 ]
    error_count = DoTests('Box', tests)
    print ""
    return error_count

#
# This section tests the StatusBox class
#
def statusboxtest1():
    """statusbox class"""
    msg = 'StatusBox.__init__'
    try:
        t = StatusBox('Alice')
        s = str(t)
    except (AttributeError, NameError) as e:
        msg = e
        s = ''
    return (s, '\n<div class="box">\n<h1>Welcome, Alice</h1>\n<form method="post" action="/status">\n<p><label for="status">Change your status:</label><input type="text" name="status" /></p>\n<p><input type="submit" name="change" value="Change" /></p>\n</form>\n</div>', msg)

def StatusBoxTests():
    tests = [ statusboxtest1 ]
    error_count = DoTests('StatusBox', tests)
    print ""
    return error_count


#
# This section tests the RecentActivityBox class
#
def recentactivityboxtest1():
    """recentactivitybox class"""
    msg = 'RecentActivityBox.__init__'
    try:
        t = RecentActivityBox(['eating lunch', 'doing homework'])
        s = str(t)
    except (AttributeError, NameError) as e:
        msg = e
        s = ''
    return (s, '\n<div class="box">\n<h1>Recent status updates</h1>\n<ul>\n<li>eating lunch</li>\n<li>doing homework</li>\n</ul>\n</div>', msg)

def RecentActivityBoxTests():
    tests = [ recentactivityboxtest1 ]
    error_count = DoTests('RecentActivityBox', tests)
    print ""
    return error_count


#
# This section tests the UnFriendBox class
#
def unfriendboxtest1():
    """unfriendbox class"""
    msg = 'UnFriendBox.__init__'
    try:
        t = UnFriendBox('Alice')
        s = str(t)
    except (AttributeError, NameError) as e:
        msg = e
        s = ''
    return (s, '\n<div class="box">\n<h1>You are currently friends with Alice</h1>\n<p>\n<form method="post" action="/unfriend"><input type="hidden" name="name" value="Alice" />\n<p><input type="submit" name="unfriend" value="Unfriend" /></p></form>\n</p>\n</div>', msg)

def UnFriendBoxTests():
    tests = [ unfriendboxtest1 ]
    error_count = DoTests('UnFriendBox', tests)
    print ""
    return error_count


#
# This section tests the LoginBox class
#
def loginboxtest1():
    """loginbox class"""
    msg = 'LoginBox.__init__'
    try:
        t = LoginBox()
        s = str(t)
    except (AttributeError, NameError) as e:
        msg = e
        s = ''
    return (s, '\n<div class="box">\n<h1>Login</h1>\n<form method="post" action="/login">\n<p><label for="name">Name:</label><input type="text" name="name" /></p>\n<p><label for="password">Password:</label><input type="password" name="password" /></p>\n<p><input type="submit" name="type" value="Login" /><input type="submit" name="type" value="Create" /><input type="submit" name="type" value="Delete" /></p>\n</form>\n</div>', msg)

def LoginBoxTests():
    tests = [ loginboxtest1 ]
    error_count = DoTests('LoginBox', tests)
    print ""
    return error_count

#
# This section tests the Gadget class
#
def gadgettest1():
    """gadget class"""
    msg = 'Gadget.__init__'
    try:
        t = Gadget('Links')
        s = str(t)
    except (AttributeError, NameError) as e:
        msg = e
        s = ''
    return (s, '\n<div class="gadget">\n<h1>Links</h1>\n</div>', msg)

def GadgetTests():
    tests = [ gadgettest1 ]
    error_count = DoTests('Gadget', tests)
    print ""
    return error_count


#
# This section tests the LinksGadget class
#
def linksgadgettest1():
    """linksgadget class"""
    msg = 'LinksGadget.__init__'
    try:
        links = [('http://cit.cs.dixie.edu/', 'CIT'), ('/loginscreen', 'Login')]
        t = LinksGadget(links)
        s = str(t)
    except (AttributeError, NameError) as e:
        msg = e
        s = ''
    return (s, '\n<div class="gadget">\n<h1>Links</h1>\n<ul>\n<li><a href="http://cit.cs.dixie.edu/">CIT</a></li>\n<li><a href="/loginscreen">Login</a></li>\n</ul>\n</div>', msg)

def LinksGadgetTests():
    tests = [ linksgadgettest1 ]
    error_count = DoTests('LinksGadget', tests)
    print ""
    return error_count


#
# This section tests the FriendsGadget class
#
def friendsgadgettest1():
    """friendsgadget class"""
    msg = 'FriendsGadget.__init__'
    try:
        friends = ['Alice', 'Bob', 'Charlie', 'Dorothy']
        t = FriendsGadget(friends)
        s = str(t)
    except (AttributeError, NameError) as e:
        msg = e
        s = ''
    return (s, '\n<div class="gadget">\n<h1>Friends</h1>\n<ul>\n<li><a href="/friend/Alice">Alice</a></li>\n<li><a href="/friend/Bob">Bob</a></li>\n<li><a href="/friend/Charlie">Charlie</a></li>\n<li><a href="/friend/Dorothy">Dorothy</a></li>\n</ul>\n<form method="post" action="/addfriend">\n<p><input type="text" name="name" /><input type="submit" name="addfriend" value="Add Friend" /></p>\n</form>\n</div>', msg)

def FriendsGadgetTests():
    tests = [ friendsgadgettest1 ]
    error_count = DoTests('FriendsGadget', tests)
    print ""
    return error_count


#
# This section tests the LogoutGadget class
#
def logoutgadgettest1():
    """logoutgadget class"""
    msg = 'LogoutGadget.__init__'
    try:
        t = LogoutGadget()
        s = str(t)
    except (AttributeError, NameError) as e:
        msg = e
        s = ''
    return (s, '\n<div class="gadget">\n<h1>Logout</h1>\n<form method="post" action="/logout">\n<p><input type="submit" name="logout" value="Logout" /></p>\n</form>\n</div>', msg)

def LogoutGadgetTests():
    tests = [ logoutgadgettest1 ]
    error_count = DoTests('LogoutGadget', tests)
    print ""
    return error_count



#
# This section tests the Page class
#
def pagetest1():
    """page class"""
    msg = 'Page.__init__'
    try:
        t = Page()
        lg = LogoutGadget()
        t.addGadget(lg)
        rab = RecentActivityBox(['eating lunch', 'doing homework'])
        t.addBox(rab)
        s = str(t)

    except (AttributeError, NameError) as e:
        msg = e
        s = ''
    return (s, '<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">\n<html xmlns="http://www.w3.org/1999/xhtml">\n<head>\n<meta http-equiv="content-type" content="text/html; charset=utf-8" />\n<title>YouFace</title>\n<link rel="stylesheet" href="youface.css" type="text/css" />\n</head>\n<body>\n<div id="maincontainer">\n<div id="header">\n<h1><a href="/">YouFace</a></h1>\n<h2>A billion dollars and it\'s yours!</h2>\n</div>\n<div id="maincolumn">\n<div class="box">\n<h1>Recent status updates</h1>\n<ul>\n<li>eating lunch</li>\n<li>doing homework</li>\n</ul>\n</div>\n</div>\n<div id="sidebar">\n<div class="gadget">\n<h1>Logout</h1>\n<form method="post" action="/logout">\n<p><input type="submit" name="logout" value="Logout" /></p>\n</form>\n</div>\n</div>\n</div>\n</body>\n</html>', msg)

def PageTests():
    tests = [ pagetest1 ]
    error_count = DoTests('Page', tests)
    print ""
    return error_count



#
# This section tests the LoginPage class
#
def loginpagetest1():
    """loginpage class"""
    msg = 'LoginPage.__init__'
    try:
        t = LoginPage()
        s = str(t)

    except (AttributeError, NameError) as e:
        msg = e
        s = ''
    return (s, """<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="content-type" content="text/html; charset=utf-8" />
<title>YouFace</title>
<link rel="stylesheet" href="youface.css" type="text/css" />
</head>
<body>
<div id="maincontainer">
<div id="header">
<h1><a href="/">YouFace</a></h1>
<h2>A billion dollars and it's yours!</h2>
</div>
<div id="maincolumn">
<div class="box">
<h1>Login</h1>
<form method="post" action="/login">
<p><label for="name">Name:</label><input type="text" name="name" /></p>
<p><label for="password">Password:</label><input type="password" name="password" /></p>
<p><input type="submit" name="type" value="Login" /><input type="submit" name="type" value="Create" /><input type="submit" name="type" value="Delete" /></p>
</form>
</div>
</div>
<div id="sidebar">
<div class="gadget">
<h1>Links</h1>
<ul>
<li><a href="http://cit.cs.dixie.edu/cs/cs1410/">CS 1410</a></li>
<li><a href="http://new.dixie.edu/reg/syllabus/">College calendar</a></li>
</ul>
</div>
</div>
</div>
</body>
</html>"""
, msg)

def LoginPageTests():
    tests = [ loginpagetest1 ]
    error_count = DoTests('LoginPage', tests)
    print ""
    return error_count



#
# This section tests the UserPage class
#
def userpagetest1():
    """userpage class"""
    msg = 'UserPage.__init__'
    try:
        friends = ['Alice', 'Bob', 'Charlie', 'Dorothy']
        t = UserPage(friends)
        s = str(t)

    except (AttributeError, NameError) as e:
        msg = e
        s = ''
    return (s, """<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="content-type" content="text/html; charset=utf-8" />
<title>YouFace</title>
<link rel="stylesheet" href="youface.css" type="text/css" />
</head>
<body>
<div id="maincontainer">
<div id="header">
<h1><a href="/">YouFace</a></h1>
<h2>A billion dollars and it's yours!</h2>
</div>
<div id="maincolumn" />
<div id="sidebar">
<div class="gadget">
<h1>Logout</h1>
<form method="post" action="/logout">
<p><input type="submit" name="logout" value="Logout" /></p>
</form>
</div>
<div class="gadget">
<h1>Friends</h1>
<ul>
<li><a href="/friend/Alice">Alice</a></li>
<li><a href="/friend/Bob">Bob</a></li>
<li><a href="/friend/Charlie">Charlie</a></li>
<li><a href="/friend/Dorothy">Dorothy</a></li>
</ul>
<form method="post" action="/addfriend">
<p><input type="text" name="name" /><input type="submit" name="addfriend" value="Add Friend" /></p>
</form>
</div>
<div class="gadget">
<h1>Links</h1>
<ul>
<li><a href="http://cit.cs.dixie.edu/cs/cs1410/">CS 1410</a></li>
<li><a href="http://new.dixie.edu/reg/syllabus/">College calendar</a></li>
</ul>
</div>
</div>
</div>
</body>
</html>"""
, msg)

def UserPageTests():
    tests = [ userpagetest1 ]
    error_count = DoTests('UserPage', tests)
    print ""
    return error_count


#
# This section tests the FeedPage class
#
def feedpagetest1():
    """feedpage class"""
    msg = 'FeedPage.__init__'
    try:
        username = 'Eve'
        status = ['eating lunch', 'doing homework']
        friends = ['Alice', 'Bob', 'Charlie', 'Dorothy']
        t = FeedPage(username, status, friends)
        s = str(t)

    except (AttributeError, NameError) as e:
        msg = e
        s = ''
    return (s, """<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="content-type" content="text/html; charset=utf-8" />
<title>YouFace</title>
<link rel="stylesheet" href="youface.css" type="text/css" />
</head>
<body>
<div id="maincontainer">
<div id="header">
<h1><a href="/">YouFace</a></h1>
<h2>A billion dollars and it's yours!</h2>
</div>
<div id="maincolumn">
<div class="box">
<h1>Welcome, Eve</h1>
<form method="post" action="/status">
<p><label for="status">Change your status:</label><input type="text" name="status" /></p>
<p><input type="submit" name="change" value="Change" /></p>
</form>
</div>
<div class="box">
<h1>Recent status updates</h1>
<ul>
<li>eating lunch</li>
<li>doing homework</li>
</ul>
</div>
</div>
<div id="sidebar">
<div class="gadget">
<h1>Logout</h1>
<form method="post" action="/logout">
<p><input type="submit" name="logout" value="Logout" /></p>
</form>
</div>
<div class="gadget">
<h1>Friends</h1>
<ul>
<li><a href="/friend/Alice">Alice</a></li>
<li><a href="/friend/Bob">Bob</a></li>
<li><a href="/friend/Charlie">Charlie</a></li>
<li><a href="/friend/Dorothy">Dorothy</a></li>
</ul>
<form method="post" action="/addfriend">
<p><input type="text" name="name" /><input type="submit" name="addfriend" value="Add Friend" /></p>
</form>
</div>
<div class="gadget">
<h1>Links</h1>
<ul>
<li><a href="http://cit.cs.dixie.edu/cs/cs1410/">CS 1410</a></li>
<li><a href="http://new.dixie.edu/reg/syllabus/">College calendar</a></li>
</ul>
</div>
</div>
</div>
</body>
</html>"""
, msg)

def FeedPageTests():
    tests = [ feedpagetest1 ]
    error_count = DoTests('FeedPage', tests)
    print ""
    return error_count


#
# This section tests the FriendPage class
#
def friendpagetest1():
    """friendpage class"""
    msg = 'FriendPage.__init__'
    try:
        username = 'Alice'
        status = ['cs1410 homework rocks', 'sleeping']
        friends = ['Alice', 'Bob', 'Charlie', 'Dorothy']
        t = FriendPage(username, status, friends)
        s = str(t)

    except (AttributeError, NameError) as e:
        msg = e
        s = ''
    return (s, """<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="content-type" content="text/html; charset=utf-8" />
<title>YouFace</title>
<link rel="stylesheet" href="youface.css" type="text/css" />
</head>
<body>
<div id="maincontainer">
<div id="header">
<h1><a href="/">YouFace</a></h1>
<h2>A billion dollars and it's yours!</h2>
</div>
<div id="maincolumn">
<div class="box">
<h1>You are currently friends with Alice</h1>
<p>
<form method="post" action="/unfriend"><input type="hidden" name="name" value="Alice" />
<p><input type="submit" name="unfriend" value="Unfriend" /></p></form>
</p>
</div>
<div class="box">
<h1>Recent status updates</h1>
<ul>
<li>cs1410 homework rocks</li>
<li>sleeping</li>
</ul>
</div>
</div>
<div id="sidebar">
<div class="gadget">
<h1>Logout</h1>
<form method="post" action="/logout">
<p><input type="submit" name="logout" value="Logout" /></p>
</form>
</div>
<div class="gadget">
<h1>Friends</h1>
<ul>
<li><a href="/friend/Alice">Alice</a></li>
<li><a href="/friend/Bob">Bob</a></li>
<li><a href="/friend/Charlie">Charlie</a></li>
<li><a href="/friend/Dorothy">Dorothy</a></li>
</ul>
<form method="post" action="/addfriend">
<p><input type="text" name="name" /><input type="submit" name="addfriend" value="Add Friend" /></p>
</form>
</div>
<div class="gadget">
<h1>Links</h1>
<ul>
<li><a href="http://cit.cs.dixie.edu/cs/cs1410/">CS 1410</a></li>
<li><a href="http://new.dixie.edu/reg/syllabus/">College calendar</a></li>
</ul>
</div>
</div>
</div>
</body>
</html>"""
, msg)

def FriendPageTests():
    tests = [ friendpagetest1 ]
    error_count = DoTests('FriendPage', tests)
    print ""
    return error_count


def main():
    for test in [ FormTests, LabelTests, InputTests,
                  BoxTests, StatusBoxTests, RecentActivityBoxTests,
                  UnFriendBoxTests, LoginBoxTests,
                  GadgetTests, LinksGadgetTests, FriendsGadgetTests,
                  LogoutGadgetTests, 
                  PageTests, LoginPageTests, UserPageTests,
                  FeedPageTests, FriendPageTests, ]:
        if test() > 0:
            return

    print "Congratulations, all tests appear to be successful."


if __name__ == '__main__':
    main()
