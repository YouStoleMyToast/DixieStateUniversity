from django import forms
from django.forms import ModelForm, Textarea

from chirp.models import Profile, Post,UserProfile

		
class ProfileForm(ModelForm):
	class Meta:
		model=Profile
		
class PostForm(ModelForm):
	class Meta:
		model=Post
		
class UserProfileForm(ModelForm):	
	class Meta:
		model=UserProfile
