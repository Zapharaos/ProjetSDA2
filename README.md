# ProjetSDA2

Automatic Language Detection (ALD) is an application that recognises the language of a sentence given to it.

## Installation

Use make to install the project.

To build the project :
```
make
```

To download the dictionaries needed :
```
make dict
```

## User mode

The program has a user mode. You can try out two different versions, either a Trie stucture or a Dawg structure.

To run the program using the Trie structure, type either one of the following commands :
```
make trie
./bin/ald -sentence -trie
```

To run the program using the Dawg structure, type either one of the following commands :
```
make dawg
./bin/ald -sentence -dawg
```

# Tests

This mode is only used in order to check if the program works properly in each languages and structures.

Type either one of the following commands :
```
make test
./bin/ald -test
```

## Performances

This mode allows us to time the insertion and research in both structures in order to compare them.

To start the perfomance test in both structures :
```
make -perf
```

To run the performance test using the Trie structure, type either one of the following commands :
```
./bin/ald -perf -trie
```

To run the performance test using the Dawg structure, type either one of the following commands :
```
./bin/ald -perf -dawg
```
## Help

The executable has a set of arguments that you can use.

To find this list, type either one of the following commands :
```
make list
make help
./bin/ald -help
```

## Enjoy
