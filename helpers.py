from nltk.tokenize import sent_tokenize


def lines(a, b):
    """Return lines in both a and b"""

    line1 = a.splitlines()
    line2 = b.splitlines()

    match = []

    for line_a in line1:

        for line_b in line2:

            if line_a == line_b:

                if match.count(line_a) == 0:

                    match.append(line_a)

    return match


def sentences(a, b):
    """Return sentences in both a and b"""

    sent1 = sent_tokenize(a)
    sent2 = sent_tokenize(b)

    match = []

    for sent_a in sent1:

        for sent_b in sent2:

            if sent_a == sent_b:

                if match.count(sent_a) == 0:

                    match.append(sent_a)

    return match


def substrings(a, b, n):
    """Return substrings of length n in both a and b"""

    list1 = []
    list2 = []
    match = []

    for i, let in enumerate(a):

        if len(a[i:n+i]) == n:
            list1.append(a[i:n+i])

    for i, let in enumerate(b):
        if len(b[i:n+i]) == n:
            list2.append(b[i:n+i])

    for sub_1 in list1:

        for sub_2 in list2:

            if sub_1 == sub_2:

                if match.count(sub_1) == 0:

                    match.append(sub_1)

    return match
