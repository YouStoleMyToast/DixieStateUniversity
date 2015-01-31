#
# This script will exercise the Tag/BlockTag/Container/BlockContainer
# classes from the html module for the CS 1410 assignment.
# 8 Feb 2010
#
try:
    from html import *
except ImportError as e:
    print e
    print """Unable to locate your html.py file.  Is it in the same folder as this file?"""
    exit(1)
import re

#
# This section tests the Tag class
#
def test1():
    """raw tag"""
    msg = 'Tag.__init__, Tag.__str__, Tag.makeTag'
    try:
        t = Tag('x')
        s = str(t)
    except (AttributeError, NameError) as e:
        msg = e
        s = ''
    return (s, '<x />', msg)

def test2():
    """tag with id"""
    msg = 'Tag.__init__, Tag.__str__, Tag.makeTag, Tag.setId, Tag.attrs'
    try:
        t = Tag('x')
        t.setId('idvalue')
        s = str(t)
    except (AttributeError, NameError) as e:
        msg = e
        s = ''
    return (s, '<x id="idvalue" />', msg)

def test3():
    """tag with class"""
    msg = 'Tag.__init__, Tag.__str__, Tag.makeTag, Tag.addClass, Tag.attrs'
    try:
        t = Tag('x')
        t.addClass('red')
        t.addClass('white')
        t.addClass('blue')
        s = str(t)
    except (AttributeError, NameError) as e:
        msg = e
        s = ''
    return (s, '<x class="red white blue" />', msg)

def test4():
    """tag with attributes"""
    msg = 'Tag.__init__, Tag.__str__, Tag.makeTag, Tag.addAttr, Tag.attrs'
    try:
        t = Tag('x')
        t.addAttr('a', '0')
        t.addAttr('b', '1')
        t.addAttr('c', '2')
        s = str(t)
    except (AttributeError, NameError) as e:
        msg = e
        s = ''
    return (s, '<x a="0" b="1" c="2" />', msg)

def test5():
    """tag with id, classes, attributes"""
    msg = 'Tag.__init__, Tag.__str__, Tag.makeTag, Tag.setId, Tag.addClass, Tag.addAttr, Tag.attrs'
    try:
        t = Tag('x')
        t.setId('idvalue')
        t.addClass('red')
        t.addClass('white')
        t.addClass('blue')
        t.addAttr('a', '0')
        t.addAttr('b', '1')
        t.addAttr('c', '2')
        s = str(t)
    except (AttributeError, NameError) as e:
        msg = e
        s = ''
    return (s, '<x id="idvalue" class="red white blue" a="0" b="1" c="2" />', msg)

def test6():
    """tag with id, classes, attributes: chaining of methods"""
    msg = 'Tag.__init__, Tag.__str__, Tag.makeTag, Tag.setId, Tag.addClass, Tag.addAttr, Tag.attrs'
    try:
        t = (Tag('x')
             .setId('idvalue')
             .addClass('red')
             .addClass('white')
             .addClass('blue')
             .addAttr('a', '0')
             .addAttr('b', '1')
             .addAttr('c', '2')
             )
        s = str(t)
    except (AttributeError, NameError) as e:
        msg = e
        s = ''
    return (s, '<x id="idvalue" class="red white blue" a="0" b="1" c="2" />', msg)

def test7():
    """tag with escape in attribute value"""
    msg = 'Tag.__init__, Tag.__str__, Tag.makeTag, Tag.addAttr, Tag.attrs'
    try:
        t = Tag('x')
        t.addAttr('a', '<')
        s = str(t)
    except (AttributeError, NameError) as e:
        msg = e
        s = ''
    return (s, '<x a="&lt;" />', msg)

def test8():
    """tag with escape in id value and class value"""
    msg = 'Tag.__init__, Tag.__str__, Tag.makeTag, Tag.setId, Tag.addClass, Tag.attrs'
    try:
        t = Tag('x')
        t.setId('<')
        t.addClass('<')
        t.addAttr('a', '<')
        s = str(t)
    except (AttributeError, NameError) as e:
        msg = e
        s = ''
    return (s, '<x id="&lt;" class="&lt;" a="&lt;" />', msg)

def TagTests():
    tests = [ test1, test2, test3, test4, test5, test6, test7, test8 ]
    error_count = DoTests('Tag', tests)
    print ""
    return error_count


#
# This section tests the BlockTag class
#
def btest1():
    """raw block tag"""
    msg = 'BlockTag.__init__, BlockTag.__str__, Tag.__str__'
    try:
        t = BlockTag('x')
        s = str(t)
    except (AttributeError, NameError) as e:
        msg = e
        s = ''
    return (s, '\n<x />', msg)

def BlockTagTests():
    tests = [ btest1 ]
    error_count = DoTests('BlockTag', tests)
    print ""
    return error_count


#
# This section tests the Container class
#
def ctest1():
    """raw container"""
    msg = 'Container.__init__, Tag.__str__'
    try:
        t = Container('x')
        s = str(t)
    except (AttributeError, NameError) as e:
        msg = e
        s = ''
    return (s, '<x />', msg)

def ctest2():
    """container with child"""
    msg = 'Container.__init__, Container.__str__, Container.addTag, Tag.makeTag'
    try:
        t = Container('x')
        t.addTag( Tag('y') )
        s = str(t)
    except (AttributeError, NameError) as e:
        msg = e
        s = ''
    return (s, '<x><y /></x>', msg)

def ctest3():
    """container with text"""
    msg = 'Container.__init__, Container.__str__, Container.addText, Tag.makeTag'
    try:
        t = Container('x')
        t.addText('Call me Ishmael.')
        s = str(t)
    except (AttributeError, NameError) as e:
        msg = e
        s = ''
    return (s, '<x>Call me Ishmael.</x>', msg)

def ctest4():
    """container with escaped text"""
    msg = 'Container.__init__, Container.__str__, Container.addText, Tag.makeTag'
    try:
        t = Container('x')
        t.addText('3 + 7 < 20')
        s = str(t)
    except (AttributeError, NameError) as e:
        msg = e
        s = ''
    return (s, '<x>3 + 7 &lt; 20</x>', msg)

def ctest5():
    """container with chaining"""
    msg = 'Container.__init__, Container.__str__, Container.addText, Container.addTag, Tag.makeTag'
    try:
        t = (Container('x')
             .addText('3 + 7 < 20')
             .addTag( Tag('y') )
             )
        s = str(t)
    except (AttributeError, NameError) as e:
        match = re.search("'NoneType' object has no attribute", str(e))
        if match:
            msg = 'Container method chaining'
        else:
            msg = e
        s = ''
    return (s, '<x>3 + 7 &lt; 20<y /></x>', msg)

def ContainerTests():
    tests = [ ctest1, ctest2, ctest3, ctest4, ctest5 ]
    error_count = DoTests('Container', tests)
    print ""
    return error_count


#
# This section tests the BlockContainer class
#
def bctest1():
    """block container"""
    msg = 'BlockContainer.__init__, BlockContainer.__str__'
    try:
        t = BlockContainer('x')
        s = str(t)
    except (AttributeError, NameError) as e:
        msg = e
        s = ''
    return (s, '\n<x />', msg)

def bctest2():
    """block container with child"""
    msg = 'BlockContainer.__init__, BlockContainer.__str__'
    try:
        t = BlockContainer('x')
        t.addTag( Tag('y') )
        s = str(t)
    except (AttributeError, NameError) as e:
        msg = e
        s = ''
    return (s, '\n<x><y /></x>', msg)

def bctest3():
    """block container with block child"""
    msg = 'BlockContainer.__init__, BlockContainer.__str__'
    try:
        t = BlockContainer('x')
        t.addTag( BlockTag('y') )
        s = str(t)
    except (AttributeError, NameError) as e:
        msg = e
        s = ''
    return (s, '\n<x>\n<y />\n</x>', msg)

def BlockContainerTests():
    tests = [ bctest1, bctest2, bctest3 ]
    error_count = DoTests('BlockContainer', tests)
    print ""
    return error_count


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



def main():
    if TagTests() > 0:
        return
    if BlockTagTests() > 0:
        return
    if ContainerTests() > 0:
        return
    if BlockContainerTests() > 0:
        return

    print "Congratulations, all tests appear to be successful."

if __name__ == '__main__':
    main()


