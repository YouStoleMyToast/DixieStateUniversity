from django import template
from inventory.models import Category

register = template.Library()

@register.inclusion_tag('inventory/category_links.html')
def category_links():
	category_list=[]
	for category in Category.objects.all():
		category_list.append(category)
		
	return {'category_list':category_list}

