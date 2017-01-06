from django.conf.urls import patterns, include, url
from django.views.generic.base import RedirectView
from django.conf.urls.static import static
from django.conf import settings

from django.contrib import admin
admin.autodiscover()

urlpatterns = patterns('',
    url(r'^users', RedirectView.as_view(url='/')),
    url(r'^grappelli/', include('grappelli.urls')),
    url(r'^admin/', include(admin.site.urls)),
    url(r'^accounts/', include('registration.backends.simple.urls')),
	url(r'^',include('rar.urls', namespace='rar')),
)+static(settings.MEDIA_URL, document_root=settings.MEDIA_ROOT)
