from django.shortcuts import render

# Create your views here.
from .models import Vote

def poll_view(request):

    vote_obj, created = Vote.objects.get_or_create(id=1)

    if request.method == "POST":
        choice = request.POST.get('vote')

        if choice == "good":
            vote_obj.good += 1
        elif choice == "satisfactory":
            vote_obj.satisfactory += 1
        elif choice == "bad":
            vote_obj.bad += 1

        vote_obj.save()

    total = vote_obj.good + vote_obj.satisfactory + vote_obj.bad

    if total == 0:
        good_per = sat_per = bad_per = 0
    else:
        good_per = round((vote_obj.good/total)*100)
        sat_per = round((vote_obj.satisfactory/total)*100)
        bad_per = round((vote_obj.bad/total)*100)

    context = {
        "good": good_per,
        "sat": sat_per,
        "bad": bad_per
    }

    return render(request,"poll.html",context)