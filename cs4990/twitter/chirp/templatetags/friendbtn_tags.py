from django import template
from django.contrib.auth.models import User
from django.conf import settings

from chirp.models import UserProfile

register = template.Library()

@register.inclusion_tag('friendbtn_tags.html', takes_context=True)
def friendbtn_tags(context):

	pageowner = context['object']
	profile = context['user']
	
	friendbtn_list=[]
	profiles = UserProfile.objects.filter(user=profile)
	for profile in profiles:
		for friend in profile.friend.all():#pointing to objects so use .all()
			friendbtn_list.append(friend)

	if pageowner in friendbtn_list:
		return {"isfriend": True,"profile":profile,"pageowner":pageowner}
	else:
		return {"isfriend": False,"profile":profile,"pageowner":pageowner}
		
			
			
	#return {'friendbtn_list':friendbtn_list,'profile':profile}

	
	
