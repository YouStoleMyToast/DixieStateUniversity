from django import template
from django.contrib.auth.models import User

from jobboard.models import Employer

register = template.Library()

@register.inclusion_tag('jobboard/loged_in.html')
def loged_in():
	employer_list=[]
	for employer in Employer.objects.all():
		employer_list.append(employer.user)

	return {'employer_list':employer_list}


#	for employer in Employer.objects.all():
#		if employer.user==username:
#			print username
#			employer_list.append(employer.user)
#	return {'employer_list':employer_list}
