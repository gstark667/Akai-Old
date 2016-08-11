from configobj import ConfigObj
from voluptuous import *


def get_config():
    schema = Schema({
        'cert_path': str,
        'key_path': str,
        'port': Coerce(int),
        'udp_port': Coerce(int)
    });
    return schema(ConfigObj('/etc/akai_server.conf')['main'])
