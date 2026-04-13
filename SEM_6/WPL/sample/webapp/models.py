from django.db import models

"""
Model = database table schema.
You can use models directly even without Django forms (create() in views, shell, admin, APIs).
"""
class loginModel(models.Model):
    username = models.CharField(max_length=100, default="")
    password = models.CharField(max_length=100, default="")
    created_at = models.DateTimeField(auto_now_add=True, null=True, blank=True)
    # def __str__(self):
    #     # This is what you see in Django admin list/dropdowns.
    #     return self.username