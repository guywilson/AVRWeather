from django.http import HttpResponseForbidden

class FilterHostMiddleware(object):

    def __init__(self, process_request):
        self.process_request = process_request

    def __call__(self, request):
        response = self.process_request(request)
        return response

    def process_request(self, request):

        # specify complete host names here
        ALLOWED_HOSTS = [
            '127.0.0.1',
            '1.0.0.127.in-addr.arpa',
            'localhost',
        ]

        host = request.META.get('HTTP_HOST')

        if host[len(host)-10:] == 'dyndns.org':  # if the host ends with dyndns.org then add to the allowed hosts
            ALLOWED_HOSTS.append(host)

        elif host[:7] == '192.168':  # if the host starts with 192.168 then add to the allowed hosts
            ALLOWED_HOSTS.append(host)

        if host not in ALLOWED_HOSTS:
            raise HttpResponseForbidden

        return None