from django.db import models
from django.contrib.auth.models import User
from django.core.urlresolvers import reverse
from time import strftime

class Project(models.Model):
    title = models.CharField(max_length=100)
    description = models.TextField()
    def __unicode__(self):
        return self.title
    def get_absolute_url(sefl):
        return reverse('checkin:projectdetail', args=(self.pk,))

class Record(models.Model):
    user=models.ForeignKey(User,editable=True)
    project=models.ForeignKey(Project)
    starttime=models.DateTimeField()
    endtime=models.DateTimeField(null=True,blank=True)
    message=models.TextField(null=True,blank=True)
    def elapsedtime(self):
        if self.endtime is not None:
            difftime=self.endtime-self.starttime
            hours,remainder=divmod(difftime.seconds,3600)
            minutes,seconds=divmod(remainder,60)
            return "%02d:%02d:%02d"%(hours,minutes,seconds)
        else:
            return None
    def __unicode__(self):
        return "Started "+self.starttime.strftime("%Y-%m-%d %I:%M:%S %p")
    def get_absolute_url(self):
        return reverse('checkin:recorddetail',args=(self.pk,))
