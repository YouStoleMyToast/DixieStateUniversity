from django import template
from portfolio.models import CaseStudy

register = template.Library()

@register.inclusion_tag('portfolio/portfolio_images.html')
def portfolio_images():
    img_list = []
    for study in CaseStudy.objects.all():
        img_list.append(study.picture)

    return {'img_list': img_list}
