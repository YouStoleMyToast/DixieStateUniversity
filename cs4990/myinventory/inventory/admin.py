from django.contrib import admin
from inventory.models import Category,Inventory

class CategoryAdmin(admin.ModelAdmin):
	search_fields = ['title','description','picture',]
	list_display = ('title','description','picture',)
	
class InventoryAdmin(admin.ModelAdmin):
	search_fields = ['category','title','description','picture','count']
	list_display = ('category','title','description','picture','count',)
	
admin.site.register(Inventory, InventoryAdmin)
admin.site.register(Category, CategoryAdmin)
