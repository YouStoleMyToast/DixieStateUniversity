from django.contrib import admin
from checkin.models import Record, Project

class RecordAdmin(admin.ModelAdmin):
	search_fields=['user','project','starttime','endtime','message']
	list_display=('user','project','starttime','endtime','message',)

class ProjectAdmin(admin.ModelAdmin):
	search_fields=['title','description']
	list_display=('title','description',)
    
admin.site.register(Record, RecordAdmin)
admin.site.register(Project, ProjectAdmin)
