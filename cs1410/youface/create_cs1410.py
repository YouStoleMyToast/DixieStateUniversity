from html import *

link_data = [ ('/degrees/', 'Degrees'),
              ('/courses/', 'Courses'),
              ('/faculty/', 'Faculty'),
              ('/facilities/', 'Facilities'),
              ('/contact/', 'Contact'),
              ('/citjobs/', 'Jobs'),
              ('/scholarships.php', 'Scholarships'),
              ('http://acm.dixie.edu/', 'ACM Club'), ]
left_menu_links =  Ul()
for d in link_data:
    li = ( Li().addTag( A(d[0]).addClass('citcss').addText(d[1]) ) )
    left_menu_links.addTag(li)

left_menu = ( Div().setId('left-menu')
              .addTag( A('/')
                       .addTag( Img('images/cit.gif', 'CIT Logo').addAttr('border', '0') )
                       )
              .addTag( Br() )
              .addTag( Br() )
              .addTag( H(3).addText('Computer and Information Technology') )
              .addTag( left_menu_links )
              )

center_header = Div().setId('center-header')
center_header_data = [ ('http://www.dixie.edu/', 'dixie'),
                       ('/', 'cit'),
                       ('/cs', 'cs'),
                       ('/it', 'it'),
                       ('/vt', 'vt'),
                       ('/degrees/', 'degrees'),
                       ('/courses/', 'courses'),
                       ('/faculty/', 'faculty'),
                       ('/facilities/', 'facilities'),
                       ('/citjobs/', 'jobs'),
                       ('https://submit.cs.dixie.edu/', 'submit'),
                       ('http://www.cs.dixie.edu/vt/', 'login'),
                       ]
for d in center_header_data:
    center_header.addTag( A(d[0]).addClass('citcss').addText(d[1]) )
    if d != center_header_data[-1]:
        center_header.addText(' | ')

class_header = Div().setId('class-header')
class_header_data = [ ('/cs/cs1410/index.php', 'Home'),
                       ('/cs/cs1410/syllabus.php', 'Syllabus'),
                       ('/cs/cs1410/schedule.php', 'Schedule'),
                       ('/cs/cs1410/examples-01.php', 'Examples-01'),
                       ('/cs/cs1410/examples-02.php', 'Examples-02'),
                       ('https://moodle.cs.dixie.edu/course/view.php?id=55', 'Grading'),
                       ]
for d in class_header_data:
    class_header.addTag( A(d[0]).addClass('citcss').addText(d[1]) )
    if d != class_header_data[-1]:
        class_header.addText(' | ')


class_content = Div().setId('class-content').addClass('text')
class_content.addTag( H(1).addText('Object Oriented Programming') )
class_content.addTag( Hr() )
class_content.addTag( H(2).addText('Course Information for Spring 2011') )
class_content.addTag( P()
                      .addTag( Strong().addText('Instructor:') )
                      .addText(' ')
                      .addTag( A('/faculty/ross/').addText('Dr Russ Ross') )
                      )

class_content.addTag( P()
                      .addTag( A('syllabus.php').addText('Syllabus') )
                      )
class_content.addTag( P()
                      .addTag( A('schedule.php').addText('Schedule and outline') )
                      )
class_content.addTag( P()
                      .addTag( A('log.php').addText('Topics covered by day') )
                      )
class_content.addTag( P()
                      .addTag( A('https://moodle.cs.dixie.edu/course/view.php?id=55').addText('Assignment submission/grading (login required)') )
                      )
class_content.addTag( P()
                      .addTag( Strong().addText('Textbooks:') )
                      )
class_content.addTag( Ul()
                      .addTag( Li()
                               .addTag( Em().addText('Python Programming: An Introduction to Computer Science') )
                               .addText(' by John Zelle, ')
                               .addTag( A('http://www.google.com/search?q=1887902996')
                                        .addText('ISBN: 1-997902-99-6') )
                               .addText(' (recommended)')
                               )
                      .addTag( Li()
                               .addTag( Em().addText('Python in a Nutshell, Second Edition') )
                               .addText(' by Alex Martelli, ')
                               .addTag( A('http://www.google.com/search?q=9780596100469')
                                        .addText('ISBN: 978-0-596-10046-9') )
                               .addText(' (recommended)')
                               )
                      )
class_content.addTag( Hr() )
class_content.addTag( H(2).addText('Resources') )


resource_data = [ ('http://docs.python.org/tutorial/', 'Python Tutorial'),
                  ('http://docs.python.org/library/', 'Python Library Reference'),
                  ('http://docs.python.org/reference/', 'Python Language Reference'),
                  ('tiled.jar', 'Map editor file (download)'),
                  ('http://www.java.com/en/download/index.jsp', 'Download Java (required for map editor)'),
                  ]
resource_list = Ul()
for d in resource_data:
    resource_list.addTag( Li().addTag( A(d[0]).addText(d[1]) ) ) 
class_content.addTag( resource_list )                      

center_column = ( Div().setId('center-column')
                  .addTag(center_header)
                  .addTag(class_header)
                  .addTag(class_content)
                  )

right_menu = Div().setId("right-menu")
right_menu.addTag( H(3).addText('Computer Science Courses') )

class_list_data = [ '1010', '1400', '1410', '2005', '2420',
                    '2450', '2810', '3310', '3400', '3410',
                    '3500', '3510', '3520', '3530', '3600',
                    '4300', '4550', '4600',
                  ]
class_list = Ul()
for d in class_list_data:
    class_list.addTag( Li().addTag( A('/cs/cs'+d+'/').addClass('citcss').addText('CS '+d) ) )
right_menu.addTag( class_list )

page = (Html()
        .addTag( Head()
                 .addTag( Meta() )
                 .addTag( Stylesheet('css/cit.css') )
                 .addTag( Title().addText('CS 1410') )
                 )
        .addTag( Body()
                 .addTag( Div().setId('full-page')
                          .addTag(left_menu)
                          .addTag(center_column)
                          .addTag(right_menu)
                          )
                 )
        )

file = open('student-cs1410.html', 'w')
file.write(str(page))
file.close()
