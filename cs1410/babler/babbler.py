#!/usr/bin/env python

import random
import re
import sys

def main():
    if len(sys.argv) < 2 or len(sys.argv) > 4:
        print >>sys.stderr, 'Usage: %s <filename> [wordcount] [n]' % sys.argv[0]
        sys.exit(1)
    filename = sys.argv[1]
    if len(sys.argv) >= 3:
        wordcount = int(sys.argv[2])
    else:
        wordcount = 100
    if len(sys.argv) >= 4:
        n = int(sys.argv[3])
    else:
        n = 3

    # read the input file
    fp = open(filename)
    contents = fp.read()
    fp.close()

    # generate n-grams
    (ngrams, starter) = makengrams(contents, n)

    # babble the output
    babble(ngrams, n, wordcount, starter)

def makengrams(contents, n):
    # get a list of words
    fields = contents.split()
    words = []
    for elt in fields:
        elt = elt.lower()
        elt = re.sub(r'\W', '', elt)
        if elt != "":
            words.append(elt)
    words.extend(words[:n-1])

    # do the shingling
    ngrams = {}
    for i in range(len(words) - (n-1)):
        ngram = words[i:i+n]
        key = tuple(ngram[:-1])
        if key not in ngrams:
            ngrams[key] = []
        ngrams[key].append(ngram[-1])

    start = random.randint(0, len(words) - (n-1))
    return (ngrams, words[start:start+n-1])

def babble(ngrams, n, words, prefix):
    for i in range(words):
        t = tuple(prefix)
        lst = ngrams[t]
        suffix = random.choice(lst)
        print suffix,
        prefix.append(suffix)
        prefix = prefix[1:]

if __name__ == '__main__':
    main()
