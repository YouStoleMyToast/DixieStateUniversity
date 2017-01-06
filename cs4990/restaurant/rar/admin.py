from django.contrib import admin
from rar.models import Restaurant, Review

class RestaurantAdmin(admin.ModelAdmin):
	list_display = ('restaurant', 'description', 'address','city','state','zipcode','latitude','longitude',)


class ReviewAdmin(admin.ModelAdmin):
	list_display = ('restaurant','title','rating','comment',)


admin.site.register(Restaurant, RestaurantAdmin)
admin.site.register(Review, ReviewAdmin)
