from django.conf.urls import patterns, include, url
from django.views.generic.base import RedirectView
from registration.backends.default.views import RegistrationView
from django.conf import settings
from django.conf.urls.static import static

from chirp.views import MyRegistrationBackend

# Uncomment the next two lines to enable the admin:
from django.contrib import admin

from django.db.models.loading import cache as model_cache
if not model_cache.loaded:
    model_cache.get_models()

admin.autodiscover()

urlpatterns = patterns('',
    url(r'^users/', RedirectView.as_view(url='/')),
    url(r'^admin/', include(admin.site.urls)),
    url(r'^accounts/', include('registration.backends.simple.urls')),
    url(r'^accounts/', MyRegistrationBackend.as_view(),name='registration_register'),
	url(r'^',include('chirp.urls', namespace='chirp')),
	
)+static(settings.STATIC_URL, document_root=settings.STATIC_ROOT)+static(settings.MEDIA_URL, document_root=settings.MEDIA_ROOT)

