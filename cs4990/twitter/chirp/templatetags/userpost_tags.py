from django import template
from django.contrib.auth.models import User
from django.conf import settings

from chirp.models import Post, UserProfile

register = template.Library()

@register.inclusion_tag('userpost_tags.html', takes_context=True)	
def userpost_tags(context):
	pageowner = context['object']
	profile = context['user']
	userpost_list=[]
	
	posts=Post.objects.all()
	for post in posts:
		userpost_list.append(post)
		
	print userpost_list
	return {'userpost_list':friend_list, 'MEDIA_URL': settings.MEDIA_URL,'pageowner':pageowner,'profile':profile}
	
	
	
	
	
