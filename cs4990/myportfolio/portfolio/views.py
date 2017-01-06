from django.http import HttpResponse, HttpResponseRedirect
from django.shortcuts import render, get_object_or_404

from portfolio.models import CaseStudy

def index(request):
    studies = CaseStudy.objects.all()
    context = {'studies' : studies}
    return render(request, 'portfolio/index.html', context)

def detail(request, study_id):
    study = get_object_or_404(CaseStudy, pk=study_id)
    context = {'study' : study}
    return render(request, 'portfolio/detail.html', context)
	
	
	
	

