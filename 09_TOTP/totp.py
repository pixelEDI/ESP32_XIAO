#pip install pyotp
import pyotp

# Geheime Schlüssel von Website
## Arduino.cc
#secret_key = 'NB6SU4SBIZSEAIKXNESFGNZGEFJDYURK'

## proton shifter
secret_key = 'DDJPTV5RGRP2U43Q5W6WABXBNOTA7JIV'

totp = pyotp.TOTP(secret_key)
otp = totp.now()

print("Dein TOTP-Code ist:", otp)
