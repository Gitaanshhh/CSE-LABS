from django.db import models

class Product(models.Model):
    title = models.CharField(max_length=200)
    price = models.FloatField()
    description = models.TextField()

    def __str__(self):
        return self.title