from django.db import models
from django.contrib.flatpages.models import FlatPage
from django import forms
from django.forms import ModelForm

class Category(models.Model):
    title=models.CharField(max_length=200)
    description=models.CharField(max_length=200)
    picture=models.ImageField(upload_to='photos/%y/%m/%d',blank=True)
    def __unicode__(self):
        return self.title

class Inventory(models.Model):
    title=models.CharField(max_length=200)
    description=models.CharField(max_length=200)
    count=models.CharField(max_length=5)
    picture=models.ImageField(upload_to='photos/%y/%m/%d',blank=True)
    category=models.ForeignKey(Category)
    def __unicode__(self):
        return self.title
	
class Meta:
	model = FlatPage
	
	
	
