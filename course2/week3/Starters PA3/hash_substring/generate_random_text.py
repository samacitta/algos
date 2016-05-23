# create a string of random printable characters and write them to a file

import string
import random

def get_random_char():
    return random.choice(string.letters)

random_chars = []
for i in range(100000):
    random_char = get_random_char()
    random_chars.append(random_char)

pattern = "abcdefghijkl"

with open("text.txt", 'w') as f:
    f.write(pattern+"\n")
    f.write("".join(random_chars))

