from django.conf.urls import patterns, url
from django.conf import settings
from django.conf.urls.static import static

from portfolio import views

urlpatterns = patterns('',
    url(r'^$', views.index, name='index'),
    url(r'^(?P<study_id>\d+)/$', views.detail, name='detail'),
)+static(settings.STATIC_URL, document_root=settings.STATIC_ROOT)+static(settings.MEDIA_URL, document_root=settings.MEDIA_ROOT)


