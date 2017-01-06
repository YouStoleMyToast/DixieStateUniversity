from django.db import models
from django.contrib.auth.models import User
from django.core.urlresolvers import reverse
from datetime import datetime, timedelta

class Profile(models.Model):
	user=models.ForeignKey(User,editable=True)
	bio=models.CharField(max_length=1000)
	image=models.ImageField(upload_to='photos/%y/%m/%d',blank=True)
	def __unicode__(self):
		return unicode(self.user)
		
class Post(models.Model):
	user=models.ForeignKey(User,editable=True)
	message=models.CharField(max_length=140)
	pubdate=models.DateTimeField(auto_now_add=True)
	def __unicode__(self):
		return unicode(self.user)

class UserProfile(models.Model):
    user = models.OneToOneField(User, unique=True)
    friend = models.ManyToManyField(Profile)
    def __unicode__(self):
    	return unicode(self.user)

