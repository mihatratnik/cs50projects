# Luhn’s algorithm
def luhn_al(card_num):

    card_num = list(card_num)
    rev_card_num = []

    total_sum = 0

    while len(card_num) != 0:
        rev_card_num += card_num.pop()

    for i, num in enumerate(rev_card_num):

        if i % 2 != 0:

            if int(num) * 2 >= 10:
                total_sum += 1 + ((int(num) * 2) % 10)

            else:
                total_sum += int(num) * 2

        else:
            total_sum += int(num)

    # check if total sum modulo 10 is equal to 0
    if total_sum % 10 == 0:
        return True
    else:
        return False


# ask user for credit card number
card_num = input("Please input your credit card number: ")

# make sure input is numeric
while card_num.isnumeric() == False:
    card_num = input("Please input your credit card number: ")

# check validity
if luhn_al(card_num) == True:

    # check if Visa
    if (len(card_num) == 13 or len(card_num) == 16) and card_num[0] == "4":
        print("VISA")

    # check if Mastercard
    elif len(card_num) == 16 and card_num[0] == "5" and (card_num[1] == "1" or card_num[1] == "2" or card_num[1] == "3" or card_num[1] == "4" or card_num[1] == "5" or card_num[1] == "6"):
        print("MASTERCARD")

    # check for American Express
    elif len(card_num) == 15 and card_num[0] == "3" and (card_num[1] == "4" or card_num[1] == "7"):
        print("AMEX")

else:
    print("INVALID")