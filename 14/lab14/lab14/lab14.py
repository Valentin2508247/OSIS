
import re
import sys
import winreg
from itertools import count
 
try:
    key = winreg.OpenKey(winreg.HKEY_LOCAL_MACHINE, 
                         "System\\MountedDevices",
                         0, winreg.KEY_READ)
except EnvironmentError:
    print('this doesnt exists')
    sys.exit(1)
    
VALUE_NAME = "\\DosDevices\\E:"
 
value, _ = winreg.QueryValueEx(key, VALUE_NAME)
result = None
 
for i in count():
    try:
        name, val, _ = winreg.EnumValue(key, i)
        if val == value and name != VALUE_NAME:
            result = re.search(r"\{(.*?)\}", name).group(1)
            break
    except OSError:
        break
print(result)