from django.conf.urls import patterns, url

from jigsaw.views import MyRegistrationBackend

from jigsaw import views

urlpatterns = patterns('',

	url(r'^accounts/profile/', MyRegistrationBackend.as_view(), name="index"),

	url(r'^$', views.ListAll.as_view(), name="index"),# Index page to show a list of latest entries
    url(r'^pins/(?P<pk>\d+)/$', views.ListPins.as_view(), name="pins"), 
    url(r'^boards/(?P<pk>\d+)/$', views.ListBoards.as_view(), name="boards"),
    
    url(r'^pin/(?P<pk>\d+)/$', views.PinDetails.as_view(), name="pindetails"), 
    
    url(r'^boards/create/(?P<pk>\d+)/$', views.CreateBoard.as_view(), name="boardcreate"),#pk to show which user
    url(r'^pins/create/(?P<pk>\d+)/$', views.CreatePin.as_view(), name="pincreate"),#pk to show which board
    url(r'^comment/create/(?P<pk>\d+)/$', views.CreateComment.as_view(), name="commentcreate"),#pk to show which pin
    
    url(r'^boards/delete/(?P<pk>\d+)/$', views.BoardDelete.as_view(), name="boarddelete"),
    url(r'^pin/delete/(?P<pk>\d+)/$', views.PinDelete.as_view(), name="pindelete"),
    url(r'^comment/delete/(?P<pk>\d+)/$', views.CommentDelete.as_view(), name="commentdelete"),
    
    url(r'^comment/edit/(?P<pk>\d+)/$', views.CommentEdit.as_view(), name="commentedit"),
    
    url(r'^repin/(?P<pk>\d+)/$', views.Repin.as_view(), name="repin"),
)
