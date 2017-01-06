from django.contrib import admin
from django.contrib.auth.admin import UserAdmin
from django.contrib.auth.models import User

from chirp.models import Profile, Post, UserProfile

admin.site.unregister(User)

class ProfileAdmin(admin.ModelAdmin):
	search_fields=['user', 'bio', 'image',]
	list_display=('user', 'bio', 'image',)
	
class PostAdmin(admin.ModelAdmin):
	search_fields=['user','message', 'pubdate']
	list_display=('user','message', 'pubdate',)

class UserProfileInline(admin.StackedInline):
    model = UserProfile
    filter_horizontal = ('friend',)

class CustomUserAdmin(UserAdmin):
    save_on_top = True
    list_display = ('username', 'email', 'first_name', 'last_name', 'is_staff', 'last_login')
    inlines = [UserProfileInline]

admin.site.register(User, CustomUserAdmin)
admin.site.register(Profile, ProfileAdmin)
admin.site.register(Post, PostAdmin)

