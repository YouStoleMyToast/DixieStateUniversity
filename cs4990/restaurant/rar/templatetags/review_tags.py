from django import template
from django.contrib.auth.models import User
from django.conf import settings

from rar.models import Review

register = template.Library()

@register.inclusion_tag('rar/restaurant_detail.html')

def review_tags():
	review_list=[]
	for review in Review.objects.all():
		review_list.append(review)
	return review_list
