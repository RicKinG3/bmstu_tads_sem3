import random
import string

def get_random_str(length):
    letters = string.ascii_lowercase + string.ascii_uppercase
    rand_string = ''.join(random.choice(letters) for i in range(length))
    return rand_string

with open("in.txt", "w") as f:
    f.write("1000")
    f.write("\n")

    for i in range (1, 1001):
        if (i % 2 == 0):
            f.write("home")
        else:
            f.write("hostel")

        f.write("\n")
        f.write(get_random_str(6))
        f.write("\n")
        f.write(get_random_str(5))
        f.write("\n")
        f.write(get_random_str(3))
        f.write("\n")
        f.write("m")
        f.write("\n")
        f.write(str(random.randint(1,100)))
        f.write("\n")
        f.write(str(random.randint(1,100)))
        f.write("\n")
        f.write(str(random.randint(1901,2023)))
        f.write("\n")
            
        if (i % 2 == 0):
            f.write(get_random_str(7))
            f.write("\n")

        f.write(str(random.randint(1,99)))
        f.write("\n")
        f.write(str(random.randint(1,99)))
        f.write("\n")
    
