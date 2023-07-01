# Description
Phonebook cli app with generator

# Installation
## Phonebook
- To create app compile it. Example: gcc ./src/main.c -o phoneBook
- Then run it. Example on Mac OS: ./phoneBook

## Phonebook data generator
- To generate preset compile generator from generate.c . Example: gcc ./src/generator.c -o generate
- Then run it. Example: ./generate
- To configure amount of generated lines set FILE_SIZE const in the generator.h

# Usage
Application allows to import, search, add, delete, update data in the phoneBook and export it to the csv file.
It also allows to generate some csv prefilled with required random data.
