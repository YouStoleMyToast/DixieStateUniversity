from django.forms import ModelForm
from django import forms

from checkin.models import Record

class UpdateRecordForm(ModelForm):
	class Meta:
		model=Record
		fields=['project','starttime','endtime','message']

class DateRangeForm(forms.Form):
	fromdate=forms.DateField()
	todate=forms.DateField()
