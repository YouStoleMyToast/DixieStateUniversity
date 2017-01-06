from django.http import HttpResponse, HttpResponseRedirect
from django.shortcuts import render, get_object_or_404
from django.core.urlresolvers import reverse
from django.core import serializers

from inventory.models import Category, Inventory
from inventory.forms import InventoryForm, CategoryForm

################ category ################
def category_display(request):
    categoryentries = Category.objects.all()
    context = {'categoryentries' : categoryentries}
    return render(request, 'inventory/category.html', context)
    
def category_add(request, category_id):
	messages=""
	if request.method=='POST':
		category_form=EditCategory(request.POST, request.FILES)
		
		if category_form.is_valid():
			category_form.save()
			return HttpResponseRedirect('/inventory/')
		else:
			messages="Category saved."
			new_category.save()
		context={
			'update_form':category_form,
			'messages':messages,
		}
	return render(request, 'inventory/category_add.html',)
	    
################ inventory ################
def inventory_display(request, inventory_id):
	inventoryentries = Inventory.objects.all()
	inventoryentry=get_object_or_404(Inventory, pk=inventory_id)
	category=inventoryentry.category
	categoryentries = Category.objects.all()
	context = {
		'inventoryentries' : inventoryentries,
		'inventoryentry' : inventoryentry,
		'category' : category,
	}
	return render(request, 'inventory/inventory.html', context) 
	

def item_detail(request, inventory_id):
	inventoryentry=get_object_or_404(Inventory, pk=inventory_id)
	form=InventoryForm(request.POST or None, instance=inventoryentry)
	if form.is_valid():
		form.save()
    	
	context={
		'inventoryentry':inventoryentry,
		'form':form,
	}
	return render(request, 'inventory/item_detail.html',context)
	
def get_qty(request, inventory_id):
	inventory=get_object_or_404(Inventory, pk=inventory_id)
	return HttpResponse(inventory.count)	
	

