from django.db import models

# Create your models here.

class Vote(models.Model):
    good = models.IntegerField(default=0)
    satisfactory = models.IntegerField(default=0)
    bad = models.IntegerField(default=0)