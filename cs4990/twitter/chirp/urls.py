from django.conf.urls import patterns, url

from chirp import views

urlpatterns=patterns('',
	url(r'^$',views.Home.as_view(), name='home'),
	url(r'^profile/(?P<pk>\d+)/$',views.Profile.as_view(),name='profile'),
	url(r'^edit/(?P<pk>\d+)/$',views.Edit.as_view(),name='edit'),
	url(r'^add/(?P<pk>\d+)/$',views.Add.as_view(),name='add'),
	url(r'^postform/(?P<post_id>\d+)/$', views.AddPost.as_view(), name='postform'),
	url(r'^follow/(?P<friend_id>\d+)/(?P<status_id>\d+)$',views.FriendChange,name='friendchange'),
	
	
	#url(r'^profile/(?P<pk>\d+)/$',views.Stranger.as_view(),name='stranger'),
	#url(r'^follow/(?P<pk>\d+)/$',views.Follow.as_view(),name='follow'),
	#url(r'^unfollow/(?P<pk>\d+)/$',views.Unfollow.as_view(),name='unfollow'),
)
