# the longest word


- Create the dictionary (i.e., TypeChoisi dicos[n])
- Read the file "francais.txt" and load it into the array "dicos"
- Launch your algorithm for finding the longest word


The array "dicos" will be used as follows. Let's assume that n = 6 and the letters given to your program are ybxrtu. To find the longest word contained in this sequence, your program will first sort this series in ascending order of its letters. This will result in:

brtuxy

Next, you search in the list of 6-letter words in "dicos" (dicos[5]) for the first "Article" object whose "pmot" field matches the sorted sequence. If such a word exists, the algorithm terminates, and the longest word is the one corresponding to the "mot" field of the found object. In the example above, no object will be found because there are no 6-letter words for the sequence.

If no match is found, the algorithm then constructs all the words obtained by removing one letter from "brtuxy." For the example, the following words are obtained:

brtux brtuy brtxy bruxy btuxy rtuxy

As before, for each of these words, you search for an object whose permutation matches. For a given word in the list, you stop at the first found object. You recursively iterate the same procedure of removing a letter if no match has been found for the word. And so on, and so forth...
