#http://ccbv.co.uk/projects/Django/1.5/django.views.generic.list/ListView/

from django import template
from django.contrib.auth.models import User
from django.conf import settings

from chirp.models import UserProfile

register = template.Library()

@register.inclusion_tag('friend_tags.html', takes_context=True)
def friend_tags(context):
	profile = context['user']
	friend_list=[]
	pro = UserProfile.objects.filter(user=profile)#this is querry set so looped through pro then friends
	for p in pro:
		for friend in p.friend.all():#pointing to objects so use .all()
			friend_list.append(friend)
	return {'friend_list':friend_list, 'MEDIA_URL': settings.MEDIA_URL}
