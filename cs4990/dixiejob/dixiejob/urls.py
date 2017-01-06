from django.conf.urls import patterns, include, url
from django.views.generic.base import RedirectView
from django.conf.urls.static import static
from django.conf import settings

#from jobboard.views import MyRegistrationBackend

from django.contrib import admin
admin.autodiscover()

urlpatterns = patterns('',
    url(r'^users', RedirectView.as_view(url='/')),
    url(r'^admin/', include(admin.site.urls)),
    url(r'^accounts/', include('registration.backends.simple.urls')),
	url(r'^',include('jobboard.urls', namespace='jobboard')),
)+static(settings.STATIC_URL, document_root=settings.STATIC_ROOT)

#url(r'^accounts/', MyRegistrationBackend.as_view(), name='registration_register'),
