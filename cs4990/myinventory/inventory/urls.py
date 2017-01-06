from django.conf.urls import patterns, url

from inventory import views

urlpatterns = patterns('',
	url(r'^$', views.category_display, name='category_display'),
    url(r'^(?P<inventory_id>\d+)/$', views.inventory_display, name='inventory_display'),
    url(r'^item_detail/(?P<inventory_id>\d+)/$', views.item_detail, name='item_detail'),
    url(r'^item_detail/(?P<inventory_id>\d+)/get/$', views.get_qty, name='get_qty'),
)

