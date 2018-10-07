# ask user for height input
height = input("Height: ")

# check that input in numeric and a non-negative integer no greater than 23
while not height.isnumeric() or int(height) < 0 or int(height) > 23:
    height = input("Height: ")

# convert input to integer
height = int(height)

# iterate through heigh and draw each raw
for column in range(height):
    print(" " * (height - 1) + "##" + "#" * (column))
    height -= 1