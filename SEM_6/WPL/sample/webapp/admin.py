from django.contrib import admin
from .models import loginModel

@admin.register(loginModel)
class LoginModelAdmin(admin.ModelAdmin):
	"""
	Columns visible in Django admin list page.
	"""
	list_display = ("id", "username", "password", "created_at")
	search_fields = ("username",)
