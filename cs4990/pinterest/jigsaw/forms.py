from django.forms import ModelForm
from django import forms
from django.contrib.auth.models import User

from jigsaw.models import Board, Pin, Comment

class CreateBoardForm(ModelForm):
	class Meta:
		model=Board

class CreatePinForm(ModelForm):
	class Meta:
		model=Pin

class RepinForm(ModelForm):
	class Meta:
		model=Pin
	
class CreateCommentForm(ModelForm):
	class Meta:
		model=Comment
		
class UpdateCommentForm(ModelForm):
	class Meta:
		model=Comment
		
class CreateRepinForm(ModelForm):
	class Meta:
		model=Pin
