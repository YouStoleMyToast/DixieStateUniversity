from django.http import HttpResponse, HttpResponseRedirect
from django.shortcuts import render, get_object_or_404
from django.core.urlresolvers import reverse
from django.core.exceptions import ObjectDoesNotExist
from django.contrib.auth.models import User
from django.contrib.auth.decorators import login_required
from django.contrib.auth.views import login
from django.utils.decorators import method_decorator

from django.views.generic import ListView, FormView, UpdateView, CreateView, DeleteView, DetailView

from checkin.models import Record, Project
from checkin.forms import UpdateRecordForm, DateRangeForm

class PunchList(ListView):
    model = Record
    context_object_name = 'records'

    def get_queryset(self):
        records = Record.objects.filter(user = self.request.user).order_by('-starttime')
        if self.request.GET.items():
            date_range = DateRangeForm(self.request.GET)
            if date_range.is_valid():
                cd = date_range.cleaned_data
                records = records.filter(starttime__range=[cd.get('fromdate'), cd.get('todate')])
        return records

    def get_context_data(self, **kwargs):
        # Get the superclass to do its job
        context=super(PunchList, self).get_context_data(**kwargs)
        
        # Include the date range form
        context['daterangeform'] = DateRangeForm()
        # improve this by supplying an 'initla' to the DateRangeForm

        # Figure out the total time
        totaltime=0
        records=Record.objects.filter(user=self.request.user)
        
        # Did they use the date range in the form?
        if self.request.GET.items():
            daterange=DateRangeForm(self.request.GET)
            if daterange.is_valid():
                cd=daterange.cleaned_data
                records = records.filter(starttime__range=[cd.get('fromdate'), cd.get('todate')])

		for record in records:
			if record.endtime is not None: 
				totaltime += (record.endtime - record.starttime).seconds

		hours, remainder=divmod(totaltime, 3600)
		minutes, seconds=divmod(remainder, 60)
		totaltimestring="%02d:%02d:%02d" % (hours, minutes, seconds)
		context['totaltime']=totaltimestring
		return context


    @method_decorator(login_required)
    def dispatch(self, *args, **kwargs):
        return super(PunchList, self).dispatch(*args, **kwargs)


class ClockIn(FormView):
    pass

class ClockOut(FormView):
    pass

class RecordUpdate(UpdateView):
    model = Record
    form_class = UpdateRecordForm

    def get_object(self):
        return get_object_or_404(Record, user = self.request.user, pk = self.kwargs['pk'])

    @method_decorator(login_required)
    def dispatch(self, *args, **kwargs):
        return super(RecordUpdate, self).dispatch(*args, **kwargs)

class RecordDelete(DeleteView):
    pass

class RecordAdd(CreateView):
    model = Record
    form_class = UpdateRecordForm

    def get_form(self, form_class):
        form = super(RecordAdd, self).get_form(form_class)
        form.instance.user = self.request.user
        return form

    @method_decorator(login_required)
    def dispatch(self, *args, **kwargs):
        return super(RecordAdd, self).dispatch(*args, **kwargs)

class RecordDetail(DetailView):
    model = Record
    context_object_name = 'record'

    def get_object(self):
        return get_object_or_404(Record, user = self.request.user, pk = self.kwargs['pk'])

    @method_decorator(login_required)
    def dispatch(self, *args, **kwargs):
        return super(RecordDetail, self).dispatch(*args, **kwargs)

	
	
	
#class PunchList(ListView):
#	model=Record
#	context_object_name='records' #for record in record (in html page)	
#	def get_querryset(self):
#		if self.request.GET.items='GET':
#			date_range=DateRangeForm(request.GET)
#			if date_range.is_valid():
#				cd=date_range.clean_data
#				records=records.filter(start_time__range=[cd.get('from_date'),cd.get('to_date')])
#		return Record.objects.filter(user=self.request.user).order_by('-starttime')
#	def get_context_data(self,**kwargs):
#		#get the super class to do its job
#		context=super(PunchList,self).get_context_data(**kwargs)
#		#include date range form
#		context['date_range_form']=DateRangeForm()
#		#improve this by supplying an "initial" to the daterangeform
#		#figure out time
#		total_time=0
#		for record in Record.objects.filter(user=self.request.user).order_by('-starttime'):
#			if record.end_time is not None:
#				total_time= end-start
#		#total_time_string="%02d%02d%02d"%(hours,min,sec) #for better formating
#		context['total-time']=total_time
#		return context
#	@method_decorator(login_required)
#	def dispatch(self, *args, **kwargs):
#		return super(PunchList, self).dispatch(*args,**kwargs)

#class RecordUpdate(UpdateView):
#	model=Record
#	context_object_name='record'
#	#in models you could do #def get_absolute_url(self) #note:where self.pk comes from
#	#or we can do this here
#	#def get_success_url(self):
#		#return reverse('timeclock:record-detail', args=(self.kwargs.get('pk'),))
#	def get_object(self):
#		return get_object_or_404(Record, user=self.request.user, pk=self.kwargs['pk'])
#	@method_decorator(login_required)
#	def dispatch(self, *args, **kwargs):
#		return super(RecordUpdate, self).dispatch(*args,**kwargs)	
	
	
