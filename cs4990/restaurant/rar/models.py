from django.db import models
from geopy import geocoders

class Restaurant(models.Model):
	restaurant = models.CharField(max_length = 100)
	description = models.TextField()
	address = models.CharField(max_length = 200)
	city = models.CharField(max_length = 100)
	state = models.CharField(max_length = 2)
	zipcode = models.CharField(max_length = 10)
	latitude = models.CharField(editable = False, null = True, blank = True, max_length = 20)
	longitude = models.CharField(editable = False, null = True, blank = True, max_length = 20)
	def __unicode__(self):
		return self.restaurant
		
	def save(self, *args, **kwargs):
		g = geocoders.GoogleV3()
		place, (lat,lng) = g.geocode(self.address+" "+self.city+" "+self.state+" "+self.zipcode)
		self.latitude = lat
		self.longitude = lng
		super(Restaurant, self).save(*args, **kwargs)
		
		
class Review(models.Model):
	restaurant = models.ForeignKey(Restaurant)
	title = models.CharField(max_length = 100)
	rating = models.IntegerField()
	comment = models.TextField()
	
	def __unicode__(self):
		return unicode(self.restaurant)
