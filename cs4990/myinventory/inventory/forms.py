from django import forms
from django.forms import ModelForm, Textarea
from inventory.models import Inventory, Category

class CategoryForm(ModelForm):
	class Meta:
		model=Category
		fields=['title','description']
		
class InventoryForm(ModelForm):
	class Meta:
		model=Inventory
		fields=['count']
