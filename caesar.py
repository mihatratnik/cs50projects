# import library sys
import sys

# check that there are only 2 command line arguments


def caesar():
    if len(sys.argv) == 2:

        # make a list of command line argument
        argv_list = list(sys.argv)

        # get the key
        for x in argv_list[1::]:
            key = int(x)

        # ask user for plaintext input
        plaintext = input("plaintext: ")

        ciphertext = ""

        # iterate through each letter in plaintext and encrypt
        for letter in plaintext:

            if letter.isupper():

                ciphertext += chr((((ord(letter) - 65) + key) % 26) + 65)

            elif letter.islower():

                ciphertext += chr((((ord(letter) - 97) + key) % 26) + 97)

            else:

                ciphertext += letter

        print(f"ciphertext: {ciphertext}")

    # if there are not 2 command line args, exit
    else:
        print("Usage: ceasar.py {key}")
        exit(1)


if __name__ == "__main__":
    caesar()