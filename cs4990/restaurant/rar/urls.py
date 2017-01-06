from django.conf.urls import patterns, url

from rar import views

urlpatterns = patterns('',
	url(r'^$', views.RestaurantList.as_view(), name="resaurants"),
	url(r'^(?P<pk>\d+)/$', views.RestaurantDetails.as_view(), name="details"),
)

