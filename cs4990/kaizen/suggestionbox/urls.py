from django.conf.urls import patterns, url

from suggestionbox import views

urlpatterns=patterns('',
	url(r'^$',views.index, name='index'),
	url(r'^categorysuggestions/(?P<category_id>\d+)/$', views.categorysuggestions, name='categorysuggestions'),
	url(r'^detail/(?P<suggestion_id>\d+)/$', views.detail, name='detail'),
	url(r'^contact/$', views.contact, name='contact'),
)
	
	
	#url(r'^login/$',{'template_name': 'registration/login.html'},name='auth_login'),
	#url(r'^logout/$',{'template_name': 'registration/logout.html'},name='auth_logout'),
	#url(r'^password/change/$',{'template_name': 'registration/password_change_form.html'}, name='auth_password_change'),
	#url(r'^password/change/done/$',{'template_name': 'registration/password_change_done.html'},name='auth_password_change_done'),
	#url(r'^password/reset/$',{'template_name': 'registration/password_reset_form.html'},name='auth_password_reset'),
	#url(r'^password/reset/confirm/(?P<uidb36>[0-9A-Za-z]+)-(?P<token>.+)/$',
	#	{'template_name': 'registration/password_reset_confirm.html'}, name='auth_password_reset_confirm'),
	#url(r'^password/reset/complete/$',{'template_name': 'registration/password_reset_complete.html'},name='auth_password_reset_complete'),
	#url(r'^password/reset/done/$',{'template_name': 'registration/password_reset_done.html'},name='auth_password_reset_done'),





