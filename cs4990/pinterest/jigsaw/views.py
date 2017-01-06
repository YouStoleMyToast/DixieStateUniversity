from datetime import datetime

from django.contrib.auth.decorators import login_required
from django.http import HttpResponse, HttpResponseRedirect
from django.shortcuts import render, get_object_or_404
from django.core.urlresolvers import reverse, reverse_lazy
from django.core.exceptions import ObjectDoesNotExist
from django.contrib.auth.models import User
from django.utils import timezone
from django.contrib import messages
from django.core.urlresolvers import reverse_lazy
from django.utils.decorators import method_decorator
from django.views.generic import ListView, DetailView, UpdateView, DeleteView, CreateView
from django.core.files.uploadedfile import SimpleUploadedFile

from endless_pagination.views import AjaxListView
from registration.backends.simple.views import RegistrationView

from jigsaw.models import Comment, Board, Pin
from jigsaw.forms import UpdateCommentForm, CreateCommentForm, CreateBoardForm, CreatePinForm, RepinForm

class MyRegistrationBackend(RegistrationView):
	def get_success_url(self, **kwargs):
		return reverse('jigsaw:boards', args=(self.kwargs.get('pk'),))
           
class ListAll(AjaxListView):
	template_name = 'jigsaw/index.html'
	model = Pin
	context_object_name = 'pins'
	paginate_by = 5
	page_template = 'jigsaw/index_pin_list.html'
	def get_queryset(self):
		return Pin.objects.filter(is_public=True).order_by('-pub_date')
#	def get_context_data(self, **kwargs):
#		context = super(ListAll, self).get_context_data(**kwargs)
#		context['pins'] = Pin.objects.all()
#		return context


class ListPins(AjaxListView):
	template_name = 'jigsaw/pindex.html'
	model = Pin
	context_object_name = 'pins'
	paginate_by = 5
	page_template = 'jigsaw/pin_list.html'
	def get_queryset(self):
		return Pin.objects.filter(created_by=self.request.user).filter(board=self.kwargs['pk']).order_by('-pub_date')
	def get_context_data(self, **kwargs):
		context = super(ListPins, self).get_context_data(**kwargs)
		context['pin'] = Pin.objects.get(id=self.kwargs['pk'])
		return context

class ListBoards(AjaxListView):
	model=Board
	template_name='jigsaw/bindex.html'
	context_object_name = 'boards'
	paginate_by = 5
	page_template = 'jigsaw/board_list.html'
	def get_queryset(self):
		return Board.objects.filter(created_by=self.request.user)
	def get_context_data(self, **kwargs):
		context = super(ListBoards, self).get_context_data(**kwargs)
		return context

class PinDetails(DetailView):
	model=Pin
	context_name='pin'
	
	def get_object(self):
		return get_object_or_404(Pin, pk = self.kwargs['pk'])
	

class CreateBoard(CreateView):
	model=Board
	form_class=CreateBoardForm
	def get_initial(self, **kwargs):
		initial = super(CreateBoard, self).get_initial()
		initial = initial.copy()
		initial['created_by'] = self.request.user.pk
		return initial
	def get_form(self, form_class):
		form = super(CreateBoard, self).get_form(form_class)
		form.instance.created_by = self.request.user
		return form
	def get_context_data(self, **kwargs):
		context = super(CreateBoard, self).get_context_data(**kwargs)
		context['created_by'] = Board.objects.filter(created_by = self.request.user)
		return context
	def form_valid(self, form):
		messages.success(self.request, 'Board created')
		return super(CreateBoard, self).form_valid(form)
	def form_invalid(self, form):
		messages.error(self.request, 'Invalid form')
		return super(CreateBoard, self).form_invalid(form)
	def get_success_url(self, **kwargs):
		return reverse('jigsaw:boards', args=(self.kwargs.get('pk'),))	
		
class CreatePin(CreateView):
	model=Pin
	form_class=CreatePinForm
	def get_initial(self, **kwargs):
		initial = super(CreatePin, self).get_initial()
		initial = initial.copy()
		initial['created_by'] = self.request.user.pk
		initial['board'] = Board.objects.filter(id=self.kwargs['pk'])
		return initial
	def get_form(self, form_class):
		form = super(CreatePin, self).get_form(form_class)
		form.instance.created_by = self.request.user
		return form
	def get_context_data(self, **kwargs):
		context = super(CreatePin, self).get_context_data(**kwargs)
		context['created_by'] = Pin.objects.filter(created_by = self.request.user)
		return context
	def form_valid(self, form):
		messages.success(self.request, 'Pin created')
		return super(CreatePin, self).form_valid(form)
	def form_invalid(self, form):
		print form.errors
		messages.error(self.request, 'Invalid form')
		return super(CreatePin, self).form_invalid(form)
	def get_success_url(self, **kwargs):
		return reverse('jigsaw:boards', args=(self.kwargs.get('pk'),))
	
class CreateComment(CreateView):
	model=Comment
	form_class=CreateCommentForm
	def get_initial(self):
		initial = super(CreateComment, self).get_initial()
		initial = initial.copy()
		initial['user'] = self.request.user.pk
		initial['pin'] = get_object_or_404(Pin, pk = self.kwargs['pk'])
		return initial
	def get_form(self, form_class):
		form = super(CreateComment, self).get_form(form_class)
		form.instance.created_by = self.request.user
		return form
	def get_context_data(self, **kwargs):
		context = super(CreateComment, self).get_context_data(**kwargs)
		context['user'] = Comment.objects.filter(user = self.request.user)
		return context
	def form_valid(self, form):
		print form
		messages.success(self.request, 'Comment created')
		return super(CreateComment, self).form_valid(form)
	def form_invalid(self, form):
		print form
		messages.error(self.request, 'Invalid form')
		return super(CreateComment, self).form_invalid(form)
	def get_success_url(self, **kwargs):
		return reverse('jigsaw:boards', args=(self.kwargs.get('pk'),))
		
class CommentUpdate(UpdateView):
	model=Comment
	form_class=UpdateCommentForm
	def get_object(self):
		return get_object_or_404(Comment, user = self.request.user, pk = self.kwargs['pk'])
	@method_decorator(login_required)
	def dispatch(self, *args, **kwargs):
		return super(CommentUpdate, self).dispatch(*args, **kwargs)
	
class BoardDelete(DeleteView):
	model = Board
	def get_context_data(self, **kwargs):
		board = get_object_or_404(Board, pk = self.kwargs['pk'])
		context = super(BoardDelete, self).get_context_data(**kwargs)
		context['user'] = self.request.user
		return context
	def get_success_url(self, **kwargs):
		return reverse('jigsaw:boards', args=(self.kwargs.get('pk'),))
		
class PinDelete(DeleteView):
	model = Pin
	def get_context_data(self, **kwargs):
		pin = get_object_or_404(Pin, pk = self.kwargs['pk'])
		context = super(PinDelete, self).get_context_data(**kwargs)
		context['user'] = self.request.user
		return context
	def get_success_url(self, **kwargs):
		return reverse('jigsaw:boards', args=(self.kwargs.get('pk'),))

class CommentDelete(DeleteView):
	model = Comment
	def get_context_data(self, **kwargs):
		comment = get_object_or_404(Comment, pk = self.kwargs['pk'])
		context = super(CommentDelete, self).get_context_data(**kwargs)
		context['user'] = self.request.user
		return context
	def get_success_url(self, **kwargs):
		return reverse('jigsaw:pins', args=(self.kwargs.get('pk'),))
		
class CommentEdit(UpdateView):
	model = Comment
	def get_success_url(self, **kwargs):
		return reverse('jigsaw:pins', args=(self.kwargs.get('pk'),))
			
class Repin(CreateView):
	model=Pin
	form_class=RepinForm
	template_name = 'jigsaw/repin_form.html'
	def get_initial(self, **kwargs):
		initial = super(Repin, self).get_initial()
		initial = initial.copy()
		pin = get_object_or_404(Pin, pk = self.kwargs['pk'])
		initial['image'] = pin.image
		initial['description'] = pin.description
		initial['created_by'] = self.request.user
		initial['link'] = pin.link
		print initial
		return initial
		
	def get_form(self, form_class):
		form = super(Repin, self).get_form(form_class)
		form.fields['board'].queryset = Board.objects.filter(created_by = self.request.user)
		form.instance.created_by = self.request.user
		return form
		
	def get_context_data(self, **kwargs):
		context = super(Repin, self).get_context_data(**kwargs)
		context['user'] = self.request.user
		return context
		
	def form_valid(self, form):
		messages.success(self.request, 'Pin created')
		return super(Repin, self).form_valid(form)
		
	def form_invalid(self, form):
		messages.error(self.request, 'Invalid form')
		return super(Repin, self).form_invalid(form)
		
	def get_success_url(self, **kwargs):
		return reverse('jigsaw:repin', args=(self.kwargs.get('pk'),))





#from ListPins
#	def get(self, *args, **kwargs):
#		if self.request.is_ajax():
#			self.template_name = 'jigsaw/paginated_pins.html'
#		return super(ListPins, self).get(*args, **kwargs)

#     def get_template_names(self):
#         if self.request.is_ajax():
#             return 'pinboard/pin_list.html'
#         else:
#             return 'pinboard/index.html'



#from ListBoards
#	def get(self, *args, **kwargs):
#		if self.request.is_ajax():
#			self.template_name = 'jigsaw/paginated_boards.html'
#		return super(ListPins, self).get(*args, **kwargs)      
#	def get_queryset(self):
#		return Board.objects.all()
	


	#def get_initial(self):
	#	initial = super(CreateComment, self).get_initial()
	#	initial = initial.copy()
	#	initial['user'] = self.request.user.pk
	#	return initial
	
	
	
#class CreateBoard(CreateView):
#	model=Board
#	form_class=CreateBoardForm
#	def get_form(self, form_class):
#		username = self.request.user
#		form = super(CreateBoard, self).get_form(form_class)
#		form.instance.created_by = username
#		return form
#	def get_context_data(self, **kwargs):
#		username = self.request.user
#		context = super(CreateBoard, self).get_context_data(**kwargs)
#		context['created_by'] = Board.objects.filter(created_by = username)
#		return context
#	def form_valid(self, form):
#		messages.success(self.request, 'Board created')
#		return super(CreateBoard, self).form_valid(form)
#	def form_invalid(self, form):
#		messages.error(self.request, 'Invalid form')
#		return super(CreateBoard, self).form_invalid(form)
		
#class CreatePin(CreateView):
#	model=Pin
#	form_class=CreatePinForm
#	def get_form(self, form_class):
#		username = self.request.user
#		form = super(CreatePin, self).get_form(form_class)
#		form.instance.created_by = username
#		return form
#	def get_context_data(self, **kwargs):
#		username = self.request.user
#		context = super(CreatePin, self).get_context_data(**kwargs)
#		context['user'] = Board.objects.filter(created_by = username)
#		return context
#	def form_valid(self, form):
#		messages.success(self.request, 'Board created')
#		return super(CreatePin, self).form_valid(form)
#	def form_invalid(self, form):
#		messages.error(self.request, 'Invalid form')
#		return super(CreatePin, self).form_invalid(form)
#		
#class CreateComment(CreateView):
#	model=Comment
#	form_class=CreateCommentForm
#	def get_initial(self,**kwargs):
#		initial = super(CreateComment, self).get_context_data(**kwargs)
#		initial = initial.copy()
#		initial['user'] = self.request.user.pk
#		return initial
#	
#	def get_form(self, form_class):
#		username = self.request.user
#		form = super(CreateComment, self).get_form(form_class)
#		form.instance.user = username
#		return form
#	def get_context_data(self, **kwargs):
#		username = self.request.user
#		context = super(CreateComment, self).get_context_data(**kwargs)
#		context['user'] = Comment.objects.filter(user = username)
#		return context
#	def form_valid(self, form):
#		messages.success(self.request, 'Board created')
#		return super(CreateComment, self).form_valid(form)
#	def form_invalid(self, form):
#		messages.error(self.request, 'Invalid form')
#		return super(CreateComment, self).form_invalid(form)

	
