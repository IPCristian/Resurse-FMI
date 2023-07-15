import secrets


# 1.

letters = "abcdefghijklmnopqrstuvwxyz"
numbers = "0123456789"
special = ".!$@"
total = letters + numbers + special + letters.upper()

minimum = [secrets.choice(s) for s in [letters,letters.upper(),numbers,special]] # Minimum required characters for password
rest_of_password = [secrets.choice(total) for _ in range(6)]

password = ''.join(minimum + rest_of_password) # Poate fi utilizata pentru un 2FA

# 2.

secrets.token_urlsafe(32) # Poate fi folosita la generarea unui URL unic pentru un utilizator

# 3.

secrets.token_hex(32) # Poate fi folosit drept cheie la criptare

# 4.

a = secrets.token_hex(64)
b = secrets.token_hex(64)
c = b

secrets.compare_digest(a,b)
secrets.compare_digest(b,c)

# 5.

secrets.randbits(800) # 1 character -> 8 bits






