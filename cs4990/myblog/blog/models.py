from django.db import models

# Create your models here.
class Blog(models.Model):
    author = models.CharField(max_length=30)
    title = models.CharField(max_length=200)
    topic = models.CharField(max_length=30)
    body = models.TextField()
    date = models.DateTimeField()
    active = models.BooleanField(choices=((1,"True"),(0,"False")),default=1,)

    def __unicode__(self):
        return self.title

