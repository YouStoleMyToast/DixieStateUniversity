from django.contrib import admin
from jobboard.models import Employer, Post, Employee

class EmployerAdmin(admin.ModelAdmin):
	search_fields=['user','company','compdesc','compwebsite','compemail','compcontact']
	list_display=('user','company','compdesc','compwebsite','compemail','compcontact',)

class EmployeeAdmin(admin.ModelAdmin):
	search_fields=['user','email','reciever']
	list_display=('user','email','reciever',)

class PostAdmin(admin.ModelAdmin):
	search_fields=['employer','title','postdesc','posttype','wage','pubdate','expdate','active']
	list_display=('employer','title','postdesc','posttype','wage','pubdate','expdate','active',)
	
admin.site.register(Employer, EmployerAdmin)
admin.site.register(Employee, EmployeeAdmin)
admin.site.register(Post, PostAdmin)
