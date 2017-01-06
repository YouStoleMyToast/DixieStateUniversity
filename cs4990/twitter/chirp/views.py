from django.http import HttpResponse, HttpResponseRedirect
from django.shortcuts import render, get_object_or_404
from django.contrib.auth.decorators import login_required
from django.contrib.auth.models import User
from django.db.models import Sum
from registration.backends.simple.views import RegistrationView
from django.utils.decorators import method_decorator

from django.views.generic import ListView, FormView, UpdateView, CreateView, DeleteView, DetailView

from django.template import RequestContext, loader
from django.core.mail import send_mail

from chirp.models import Profile, Post, UserProfile
from chirp.forms import UserProfileForm, PostForm
	
class MyRegistrationBackend(RegistrationView):
	def get_success_url(self,request,user):
		return reverse('chirp:home')
		
	
class Home(ListView):
	model=Post
	template_name='post_list.html'
	context_object_name='posts'
	def get_qeury_set(self):
		return Post.objects.all().order_by('-pudate')[:20]

class Profile(DetailView):
	model=Profile
	template_name='profile_detail.html'
	context_object_name='profile'
	form_class=UserProfileForm
	def get_qeury_set(self):
		return get_object_or_404(Post, user = self.request.user, pk = self.kwargs['pk'])
		
	def get_form(self,form):
		form = super(Profile, self).get_form(form_class)
		form.instance.user = self.request.user
		return form
        
	@method_decorator(login_required)
	def dispatch(self, *args, **kwargs):
		return super(Profile, self).dispatch(*args, **kwargs)

class Edit(DetailView):
	pass
		
class Add(FormView):
	pass

def follow():
	pass
	
def unfollow():
	pass
	
def FriendChange(request, friend_id, status_id):
	user=request.user
	profile=get_object_or_404(UserProfile, pk=user.id)
	friend=get_object_or_404(UserProfile, pk=friend_id)
	print profile
	print friend
	if status_id==0:
		profile.friend.add(friend)
		return HttpResponseRedirect(reverse('chirp:profile', args=(friend.id)))
	elif status_id==1:
		profile.friend.remove(friend)
		return HttpResponseRedirect(reverse('chirp:home'))

class AddPost(CreateView):
	model=Post
	form_class = PostForm
	
	def get_form(self, form_class):
		form = super(AddPost, self).get_form(form_class)
		form.instance.user = self.request.user
		return form
	
	def form_invalid(self,form):
		return HttpResponse("Invalid Form")

	def get_success_url(self):
		return reverse('.')	
	
	
