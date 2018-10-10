import sys
import crypt
import string

# function returnes salt


def get_salt():

    hash_val = sys.argv[1]
    salt = ""

    for letter in hash_val[0:2:]:
        salt += letter

    return salt


# check that there are onyl 2 command line arguments
def main():
    if len(sys.argv) != 2:

        # print usage message and exit with code 1
        print("Usage: ./crack hash")
        exit(1)

    else:

        # get the salt
        salt = get_salt()

        # iterate through 1 letter password
        for i in string.ascii_letters:

            password = ""
            password += i

            if crypt.crypt(password, salt) == sys.argv[1]:

                print(password)
                exit(0)

        print("Pregledu 1")

        # iterate through 2 letter password
        for i in string.ascii_letters:

            password = ""
            password += i

            if crypt.crypt(password, salt) == sys.argv[1]:

                print(password)

            else:
                for i in string.ascii_letters:

                    password_1 = password
                    password_1 += i

                    if crypt.crypt(password_1, salt) == sys.argv[1]:

                        print(password_1)
                        exit(0)

        print("Pregledu 2")

        # iterate through 3 letter password
        for i in string.ascii_letters:

            password = ""
            password += i

            if crypt.crypt(password, salt) == sys.argv[1]:

                print(password)

            else:
                for j in string.ascii_letters:

                    password_1 = password
                    password_1 += j

                    if crypt.crypt(password_1, salt) == sys.argv[1]:

                        print(password_1)

                    else:
                        for k in string.ascii_letters:

                            password_2 = password_1
                            password_2 += k

                            if crypt.crypt(password_2, salt) == sys.argv[1]:

                                print(password_2)
                                exit(0)

        print("Pregledu 3")

        # iterate through 4 letter password
        for i in string.ascii_letters:

            password = ""
            password += i

            if crypt.crypt(password, salt) == sys.argv[1]:

                print(password)

            else:
                for j in string.ascii_letters:

                    password_1 = password
                    password_1 += j

                    if crypt.crypt(password_1, salt) == sys.argv[1]:

                        print(password_1)

                    else:
                        for k in string.ascii_letters:

                            password_2 = password_1
                            password_2 += k

                            if crypt.crypt(password_2, salt) == sys.argv[1]:

                                print(password_2)

                            else:
                                for l in string.ascii_letters:

                                    password_3 = password_2
                                    password_3 += l

                                    if crypt.crypt(password_3, salt) == sys.argv[1]:

                                        print(password_3)
                                        exit(0)

        print("Pregledu 4")

        # iterate through 5 letter password
        for i in string.ascii_letters:

            password = ""
            password += i

            if crypt.crypt(password, salt) == sys.argv[1]:

                print(password)

            else:
                for j in string.ascii_letters:

                    password_1 = password
                    password_1 += j

                    print(f"Zdele sem pri črki {password_1}")

                    if crypt.crypt(password_1, salt) == sys.argv[1]:

                        print(password_1)

                    else:
                        for k in string.ascii_letters:

                            password_2 = password_1
                            password_2 += k

                            if crypt.crypt(password_2, salt) == sys.argv[1]:

                                print(password_2)

                            else:
                                for l in string.ascii_letters:

                                    password_3 = password_2
                                    password_3 += l

                                    if crypt.crypt(password_3, salt) == sys.argv[1]:

                                        print(password_3)

                                    else:
                                        for m in string.ascii_letters:

                                            password_4 = password_3
                                            password_4 += m

                                            if crypt.crypt(password_4, salt) == sys.argv[1]:

                                                print(password_4)
                                                exit(0)


# call main function
if __name__ == "__main__":
    main()