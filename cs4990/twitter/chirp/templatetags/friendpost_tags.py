from django import template
from django.contrib.auth.models import User
from django.conf import settings

from chirp.models import Post, UserProfile

register = template.Library()

@register.inclusion_tag('friendpost_tags.html', takes_context=True)	
def friendpost_tags(context):
	pageowner = context['object']
	profile = context['user']
	
	friend_list=[]
	pro = UserProfile.objects.filter(user=profile)#this is querry set so looped through pro then friends
	for p in pro:
		for friend in p.friend.all():#pointing to objects so use .all()
			friend_list.append(friend)
	
	pageownerpost_list=[]
	for post in Post.objects.all():
		p=post.user
		m=post.message
		profiles=post.user.profile_set.all()
		for pro in profiles:
			i=pro.image
			if post.user==pageowner.user:
				pageownerpost_list.append((p,m,i))	
	
	friendpost_list=[]
	if pageowner.user==profile:
		for post in Post.objects.all():
			p=post.user
			m=post.message
			profiles=post.user.profile_set.all()
			for bro in profiles:
				i=bro.image
				friendpost_list.append((p,m,i))
	
	person_list=[]
	for person in friendpost_list:
		if person[0]==profile:
			person_list.append(person)
		for friend in friend_list:
			if person[0]==friend.user:
				person_list.append(person)
	
	return {'pageownerpost_list':pageownerpost_list, 'person_list':person_list,'MEDIA_URL': settings.MEDIA_URL,'pageowner':pageowner,'profile':profile}
	

	
#@register.inclusion_tag('friendpost_tags.html', takes_context=True)	
#def friendpost_tags(context):
#	pageowner = context['object']
#	profile = context['user']
#	friend_list=[]
#	pro = UserProfile.objects.filter(user=profile)#this is querry set so looped through pro then friends
#	for p in pro:
#		friend_list.append(p)
#		for friend in p.friend.all():#pointing to objects so use .all()
#			friend_list.append(friend)
#	friendpost_list=[]
#	posts = Post.objects.all()
#	for post in posts:
#		p=post.user
#		m=post.message
#		profiles=post.user.profile_set.all()
#		for bro in profiles:
#			i=bro.image
#			friendpost_list.append((p,m,i))
#	combo_list=[]
#	for fl in friendpost_list:
#		if fl in friend_list:
#			combo_list.append(fl)
#	return {'friend_list':friend_list, 'friendpost_list':friendpost_list, 'MEDIA_URL': settings.MEDIA_URL,'pageowner':pageowner,'profile':profile}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
