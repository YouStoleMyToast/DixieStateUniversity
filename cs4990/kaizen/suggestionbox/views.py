from django.http import HttpResponse, HttpResponseRedirect
from django.shortcuts import render, get_object_or_404
from django.contrib.auth.decorators import login_required
from django.views.generic.base import RedirectView
from django.contrib.auth.models import User
from django.core.urlresolvers import reverse
from django.core import serializers

from suggestionbox.models import Suggestion, Comment, Status, Category
from suggestionbox.forms import CommentForm, SuggestionForm

def base(request):
	username=request.user
	suggestions = Suggestion.objects.all().filter(user=username)
	context = {
		'suggestions': suggestions,
		'user':username,
		}
	return render(request, 'suggestionbox/base.html', context)

def index(request):
	username=request.user
	categories=Category.objects.all()
	context = {
		'categories': categories,
		'user':username,
		}
	return render(request, 'suggestionbox/index.html', context)

def categorysuggestions(request, category_id):
	username=request.user
	categorys = Category.objects.all().order_by('pub_date')
	category = get_object_or_404(Category, pk=category_id)
	suggestions=Suggestion.objects.all().filter(category=category_id)
	stats=Status.objects.all()

	thesuggestion=Suggestion()
	thesuggestion.user=username
	thesuggestion.title=request.POST.get('title')
	thesuggestion.description=request.POST.get('description')
	thesuggestion.status=stats[0]
	thesuggestion.category=category
	
	form=SuggestionForm(request.POST, request.FILES or None, instance=thesuggestion)
	context = {
		'categorys': categorys,
		'category':category,
		'suggestions':suggestions,
		'user':username,
		'form':form,
		}
	if form.is_valid():
		form.save()
		return HttpResponseRedirect('')
		
	return render(request, 'suggestionbox/categorysuggestions.html', context)

def contact(request):
	return render(request, 'suggestionbox/contact.html')
	
@login_required
def detail(request, suggestion_id):
	username=request.user
	suggestion = get_object_or_404(Suggestion, pk=suggestion_id)
	comments = Comment.objects.all().filter(sid=suggestion_id)
	comment = get_object_or_404(Suggestion, pk=suggestion_id)
	thiscomment=Comment()
	thiscomment.user=username
	thiscomment.comment=request.POST.get('comment')
	thiscomment.sid=suggestion
	comform=CommentForm(request.POST,request.FILES or None, instance=thiscomment)
	context = {
		'suggestion': suggestion,
		'comments':comments,
		'user':username,
		'comform':comform,
	}
	if comform.is_valid():
		comform.save()
		return HttpResponseRedirect('')
		
	return render(request, 'suggestionbox/detail.html', context)







@login_required
def not_detail(request, suggestion_id):
	user=request.user
	suggestion = get_object_or_404(Suggestion, pk=suggestion_id)
	comments = Comment.objects.all().filter(sid=suggestion_id)
	context = {
		'suggestion': suggestion,
		'comments':comments,
		'user':user,
	}
	return render(request, 'suggestionbox/detail.html', context)




