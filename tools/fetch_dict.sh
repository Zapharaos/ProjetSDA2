#!/bin/bash

dict_dir='../dict'

german_url='https://raw.githubusercontent.com/enz/german-wordlist/master/words'
english_url='https://raw.githubusercontent.com/dwyl/english-words/master/words_alpha.txt'
french_url='https://raw.githubusercontent.com/Mcas4150/french-wordlist/master/words.txt'

german_filename='german-wordlist.txt'
english_filename='english-wordlist.txt'
french_filename='french-wordlist.txt'

# 'wget -qO-' : download url and display it on the standard output
# 'iconv -f utf8 -t ascii//TRANSLIT' : remove diacritics 
# and replace them with ascii equivalent, e.g. à -> a, é -> e, etc...
# 'tr A-Z a-z' : every char to lowercase

mkdir -p $dict_dir

# get german wordlist
wget -qO- $german_url | iconv -f utf8 -t ascii//TRANSLIT | tr A-Z a-z | tr -d "-" > $dict_dir/$german_filename

# get french wordlist
wget -qO- $french_url | iconv -f utf8 -t ascii//TRANSLIT | tr A-Z a-z | tr -d "-" > $dict_dir/$french_filename

# get english wordlist
wget -qO- $english_url | iconv -f utf8 -t ascii//TRANSLIT | tr A-Z a-z | tr -d "-" > $dict_dir/$english_filename

dos2unix $dict_dir/$german_filename $dict_dir/$french_filename $dict_dir/$english_filename