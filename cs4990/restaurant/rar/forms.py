from django.forms import ModelForm
from django import forms
from django.contrib.auth.models import User

from rar.models import Review, Restaurant

class RestaurantForm(ModelForm):
	class Meta:
		model=Restaurant
		
class ReviewForm(ModelForm):
	class Meta:
		model=Review
