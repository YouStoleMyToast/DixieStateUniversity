try:
    from html import *
except ImportError as e:
    print e
    print """Unable to locate your html.py file.  Is it in the same folder as this file?"""
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
# This section tests the Img class
#
def imgtest1():
    """image tag"""
    msg = 'Img.__init__'
    try:
        t = Img('images/mandrill.jpg','Colorful primate')
        s = str(t)
    except (AttributeError, NameError) as e:
        msg = e
        s = ''
    return (s, '<img src="images/mandrill.jpg" alt="Colorful primate" />', msg)

def ImgTests():
    tests = [ imgtest1 ]
    error_count = DoTests('Img', tests)
    print ""
    return error_count

#
# This section tests the Meta class
#
def metatest1():
    """meta tag"""
    msg = 'Meta.__init__'
    try:
        t = Meta()
        s = str(t)
    except (AttributeError, NameError) as e:
        msg = e
        s = ''
    return (s, '\n<meta http-equiv="content-type" content="text/html; charset=utf-8" />', msg)

def MetaTests():
    tests = [ metatest1 ]
    error_count = DoTests('Meta', tests)
    print ""
    return error_count

#
# This section tests the Stylesheet class
#
def stylesheettest1():
    """stylesheet tag"""
    msg = 'Stylesheet.__init__'
    try:
        t = Stylesheet('blog.css')
        s = str(t)
    except (AttributeError, NameError) as e:
        msg = e
        s = ''
    return (s, '\n<link rel="stylesheet" href="blog.css" type="text/css" />', msg)

def StylesheetTests():
    tests = [ stylesheettest1 ]
    error_count = DoTests('Stylesheet', tests)
    print ""
    return error_count

#
# This section tests the Br class
#
def brtest1():
    """br tag"""
    msg = 'Br.__init__'
    try:
        t = Br()
        s = str(t)
    except (AttributeError, NameError) as e:
        msg = e
        s = ''
    return (s, '<br />', msg)

def BrTests():
    tests = [ brtest1 ]
    error_count = DoTests('Br', tests)
    print ""
    return error_count

#
# This section tests the Hr class
#
def hrtest1():
    """hr tag"""
    msg = 'Hr.__init__'
    try:
        t = Hr()
        s = str(t)
    except (AttributeError, NameError) as e:
        msg = e
        s = ''
    return (s, '<hr />', msg)

def HrTests():
    tests = [ hrtest1 ]
    error_count = DoTests('Hr', tests)
    print ""
    return error_count

#
# This section tests the A class
#
def atest1():
    """a tag"""
    msg = 'A.__init__'
    try:
        t = A('file.html')
        s = str(t)
    except (AttributeError, NameError) as e:
        msg = e
        s = ''
    return (s, '<a href="file.html" />', msg)

def atest2():
    """a tag"""
    msg = 'A(Container)'
    try:
        t = A('file.html')
        t.addText('target text')
        s = str(t)
    except (AttributeError, NameError) as e:
        msg = e
        s = ''
    return (s, '<a href="file.html">target text</a>', msg)

def ATests():
    tests = [ atest1, atest2 ]
    error_count = DoTests('A', tests)
    print ""
    return error_count

#
# This section tests the Title class
#
def titletest1():
    """title tag"""
    msg = 'Title.__init__'
    try:
        t = Title()
        s = str(t)
    except (AttributeError, NameError) as e:
        msg = e
        s = ''
    return (s, '\n<title />', msg)

def titletest2():
    """title tag"""
    msg = 'Title(BlockContainer)'
    try:
        t = Title()
        t.addText('My blog')
        s = str(t)
    except (AttributeError, NameError) as e:
        msg = e
        s = ''
    return (s, '\n<title>My blog</title>', msg)

def TitleTests():
    tests = [ titletest1, titletest2 ]
    error_count = DoTests('Title', tests)
    print ""
    return error_count

#
# This section tests the Div class
#
def divtest1():
    """div tag"""
    msg = 'Div.__init__'
    try:
        t = Div()
        s = str(t)
    except (AttributeError, NameError) as e:
        msg = e
        s = ''
    return (s, '\n<div />', msg)

def divtest2():
    """div tag"""
    msg = 'Div(BlockContainer)'
    try:
        t = Div()
        t.addText('My blog')
        s = str(t)
    except (AttributeError, NameError) as e:
        msg = e
        s = ''
    return (s, '\n<div>My blog</div>', msg)

def DivTests():
    tests = [ divtest1, divtest2 ]
    error_count = DoTests('Div', tests)
    print ""
    return error_count

#
# This section tests the Strong class
#
def strongtest1():
    """strong tag"""
    msg = 'Strong.__init__'
    try:
        t = Strong()
        s = str(t)
    except (AttributeError, NameError) as e:
        msg = e
        s = ''
    return (s, '\n<strong />', msg)

def strongtest2():
    """strong tag"""
    msg = 'Strong(BlockContainer)'
    try:
        t = Strong()
        t.addText('My blog')
        s = str(t)
    except (AttributeError, NameError) as e:
        msg = e
        s = ''
    return (s, '\n<strong>My blog</strong>', msg)

def StrongTests():
    tests = [ strongtest1, strongtest2 ]
    error_count = DoTests('Strong', tests)
    print ""
    return error_count

#
# This section tests the Em class
#
def emtest1():
    """em tag"""
    msg = 'Em.__init__'
    try:
        t = Em()
        s = str(t)
    except (AttributeError, NameError) as e:
        msg = e
        s = ''
    return (s, '\n<em />', msg)

def emtest2():
    """em tag"""
    msg = 'Em(BlockContainer)'
    try:
        t = Em()
        t.addText('My blog')
        s = str(t)
    except (AttributeError, NameError) as e:
        msg = e
        s = ''
    return (s, '\n<em>My blog</em>', msg)

def EmTests():
    tests = [ emtest1, emtest2 ]
    error_count = DoTests('Em', tests)
    print ""
    return error_count

#
# This section tests the P class
#
def ptest1():
    """p tag"""
    msg = 'P.__init__'
    try:
        t = P()
        s = str(t)
    except (AttributeError, NameError) as e:
        msg = e
        s = ''
    return (s, '\n<p />', msg)

def ptest2():
    """p tag"""
    msg = 'P(BlockContainer)'
    try:
        t = P()
        t.addText('My blog')
        s = str(t)
    except (AttributeError, NameError) as e:
        msg = e
        s = ''
    return (s, '\n<p>My blog</p>', msg)

def PTests():
    tests = [ ptest1, ptest2 ]
    error_count = DoTests('P', tests)
    print ""
    return error_count

#
# This section tests the H class
#
def htest1():
    """h tag"""
    msg = 'H.__init__'
    try:
        t = H(2)
        s = str(t)
    except (AttributeError, NameError) as e:
        msg = e
        s = ''
    return (s, '\n<h2 />', msg)

def htest2():
    """h tag"""
    msg = 'H.__init__'
    try:
        t = H(0)
        s = str(t)
    except (AttributeError, NameError) as e:
        msg = e
        s = ''
    return (s, '\n<h1 />', msg)

def htest3():
    """h tag"""
    msg = 'H.__init__'
    try:
        t = H(7)
        s = str(t)
    except (AttributeError, NameError) as e:
        msg = e
        s = ''
    return (s, '\n<h6 />', msg)

def htest4():
    """h tag"""
    msg = 'H.__init__'
    try:
        t = H(6)
        s = str(t)
    except (AttributeError, NameError) as e:
        msg = e
        s = ''
    return (s, '\n<h6 />', msg)

def htest5():
    """h tag"""
    msg = 'H.__init__'
    try:
        t = H(4)
        s = str(t)
    except (AttributeError, NameError) as e:
        msg = e
        s = ''
    return (s, '\n<h4 />', msg)

def htest6():
    """h tag"""
    msg = 'H.__init__'
    try:
        t = H("3")
        s = str(t)
    except (AttributeError, NameError) as e:
        msg = e
        s = ''
    return (s, '\n<h3 />', msg)

def HTests():
    tests = [ htest1, htest2, htest3, htest4, htest5, htest6 ]
    error_count = DoTests('H', tests)
    print ""
    return error_count

#
# This section tests the Ul class
#
def ultest1():
    """ul tag"""
    msg = 'Ul.__init__'
    try:
        t = Ul()
        s = str(t)
    except (AttributeError, NameError) as e:
        msg = e
        s = ''
    return (s, '\n<ul />', msg)

def ultest2():
    """ul tag"""
    msg = 'Ul(BlockContainer)'
    try:
        t = Ul()
        t.addText('My blog')
        s = str(t)
    except (AttributeError, NameError) as e:
        msg = e
        s = ''
    return (s, '\n<ul>My blog</ul>', msg)

def UlTests():
    tests = [ ultest1, ultest2 ]
    error_count = DoTests('Ul', tests)
    print ""
    return error_count

#
# This section tests the Ol class
#
def oltest1():
    """ol tag"""
    msg = 'Ol.__init__'
    try:
        t = Ol()
        s = str(t)
    except (AttributeError, NameError) as e:
        msg = e
        s = ''
    return (s, '\n<ol />', msg)

def oltest2():
    """ol tag"""
    msg = 'Ol(BlockContainer)'
    try:
        t = Ol()
        t.addText('My blog')
        s = str(t)
    except (AttributeError, NameError) as e:
        msg = e
        s = ''
    return (s, '\n<ol>My blog</ol>', msg)

def OlTests():
    tests = [ oltest1, oltest2 ]
    error_count = DoTests('Ol', tests)
    print ""
    return error_count

#
# This section tests the Li class
#
def litest1():
    """li tag"""
    msg = 'Li.__init__'
    try:
        t = Li()
        s = str(t)
    except (AttributeError, NameError) as e:
        msg = e
        s = ''
    return (s, '\n<li />', msg)

def litest2():
    """li tag"""
    msg = 'Li(BlockContainer)'
    try:
        t = Li()
        t.addText('My blog')
        s = str(t)
    except (AttributeError, NameError) as e:
        msg = e
        s = ''
    return (s, '\n<li>My blog</li>', msg)

def LiTests():
    tests = [ litest1, litest2 ]
    error_count = DoTests('Li', tests)
    print ""
    return error_count

#
# This section tests the Head class
#
def headtest1():
    """head tag"""
    msg = 'Head.__init__'
    try:
        t = Head()
        s = str(t)
    except (AttributeError, NameError) as e:
        msg = e
        s = ''
    return (s, '\n<head />', msg)

def headtest2():
    """head tag"""
    msg = 'Head(BlockContainer)'
    try:
        t = Head()
        t.addText('My blog')
        s = str(t)
    except (AttributeError, NameError) as e:
        msg = e
        s = ''
    return (s, '\n<head>My blog</head>', msg)

def HeadTests():
    tests = [ headtest1, headtest2 ]
    error_count = DoTests('Head', tests)
    print ""
    return error_count

#
# This section tests the Body class
#
def bodytest1():
    """body tag"""
    msg = 'Body.__init__'
    try:
        t = Body()
        s = str(t)
    except (AttributeError, NameError) as e:
        msg = e
        s = ''
    return (s, '\n<body />', msg)

def bodytest2():
    """body tag"""
    msg = 'Body(BlockContainer)'
    try:
        t = Body()
        t.addText('My blog')
        s = str(t)
    except (AttributeError, NameError) as e:
        msg = e
        s = ''
    return (s, '\n<body>My blog</body>', msg)

def BodyTests():
    tests = [ bodytest1, bodytest2 ]
    error_count = DoTests('Body', tests)
    print ""
    return error_count


#
# This section tests the Html class
#
def htmltest1():
    """html tag"""
    msg = 'Html.__init__'
    try:
        t = Html()
        s = str(t)
    except (AttributeError, NameError) as e:
        msg = e
        s = ''
    return (s, '<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">\n<html xmlns="http://www.w3.org/1999/xhtml" />', msg)

def htmltest2():
    """html tag"""
    msg = 'Html(BlockContainer)'
    try:
        t = Html()
        t.addTag(Body())
        s = str(t)
    except (AttributeError, NameError) as e:
        msg = e
        s = ''
    return (s, '<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">\n<html xmlns="http://www.w3.org/1999/xhtml">\n<body />\n</html>', msg)

def HtmlTests():
    tests = [ htmltest1, htmltest2 ]
    error_count = DoTests('Html', tests)
    print ""
    return error_count


def main():
    for test in [ ImgTests, MetaTests, StylesheetTests,
                  BrTests, HrTests, ATests, TitleTests,
                  DivTests, StrongTests, EmTests, PTests,
                  HTests, UlTests, OlTests, LiTests,
                  HeadTests, BodyTests, HtmlTests ]:
        if test() > 0:
            return

    print "Congratulations, all tests appear to be successful."


if __name__ == '__main__':
    main()
