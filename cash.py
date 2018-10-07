# make sure that the input is numeric and greater than 0 than convert it to pennies
def check_con(change):
    while True:
        try:
            change = float(change)
        except:
            change = input("Change: ")
        else:
            while float(change) <= 0:
                change = input("Change: ")
            return float(change) * 100


# get amout of change from the user
change = input("Change: ")

# make sure that the input is numeric and greater than 0 than convert it to pennies
change = check_con(change)

# declare dictionary containing change values
change_list = {"quarter": 25, "dime": 10, "nickle": 5, "pennie": 1}

# initiate a coin counter
coin_counter = 0

# check to use quarters
while change >= change_list["quarter"]:
    change -= change_list["quarter"]
    coin_counter += 1

# check to use dimes
while change >= change_list["dime"]:
    change -= change_list["dime"]
    coin_counter += 1

# check to use nickles
while change >= change_list["nickle"]:
    change -= change_list["nickle"]
    coin_counter += 1

# check to use pennies
while change >= change_list["pennie"]:
    change -= change_list["pennie"]
    coin_counter += 1

print(f"{coin_counter}")