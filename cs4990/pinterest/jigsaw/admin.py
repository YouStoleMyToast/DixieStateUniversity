from django.contrib import admin
from jigsaw.models import Pin, Board, Comment

class PinAdmin(admin.ModelAdmin):
    search_fields=['image','description','created_by','pub_date','link','is_public']
    list_display=('image','description','created_by','pub_date','link','is_public',)

class BoardAdmin(admin.ModelAdmin):
	pass
    #search_fields=['user','pin','comment']
    #list_display=('user','pin','comment',)

class CommentAdmin(admin.ModelAdmin):
    pass
    #search_fields=['created_by','name']
    #list_display=('created_by','name',)

admin.site.register(Pin, PinAdmin)
admin.site.register(Board, BoardAdmin)
admin.site.register(Comment, CommentAdmin)
