from django.http import HttpResponse, HttpResponseRedirect
from django.shortcuts import render, get_object_or_404, render_to_response
from django.core.urlresolvers import reverse
from django.core.exceptions import ObjectDoesNotExist
from django.contrib.auth.models import User
from django.contrib import messages
from django.views.generic import ListView, DetailView, UpdateView, DeleteView, CreateView, FormView
from django import forms
from django.views.generic.detail import SingleObjectMixin
from django.core import serializers

from gmapi import maps
from gmapi.forms.widgets import GoogleMap

from rar.models import Restaurant, Review

class RestaurantList(ListView):
	model = Restaurant
	context_object_name = "restaurants"
	
class RestaurantDetails(DetailView):
	model = Restaurant
	def get_context_data(self, **kwargs):
		restaurant = get_object_or_404(Restaurant, pk = self.kwargs['pk'])
		review = get_object_or_404(Review, pk = self.kwargs['pk'])
		context = super(RestaurantDetails, self).get_context_data(**kwargs)
		context['restaurant'] = restaurant
		context['review'] = review
		return context

	
	
	
	
	
