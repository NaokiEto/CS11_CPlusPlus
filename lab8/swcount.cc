#include <iostream>
#include <map>
#include <set>
#include <string>


// So we don't have to type "std::" everywhere...
using namespace std;


void initSkipList(set<string>& skipList);
string processWord(string word);
void processText(set<string>& skipList, map<string, int>& wordCounts);
void outputWordsByCount(map<string, int>& wordCounts);


int main()
{
  set<string> skipList;
  map<string, int> wordCounts;

  // Initialize the skip-list.
  initSkipList(skipList);

  // Process the text on console-input, using the skip-list.
  processText(skipList, wordCounts);

  // Finally, output the word-list and the associated counts.
  outputWordsByCount(wordCounts);
}


/*
 * This function initializes the skip-list of words.
 *
 * skipList = the set of words to skip
 */
void initSkipList(set<string>& skipList)
{
  // Use a pre-specified skip-list.

  const char *swords[] = {
    "a", "all", "am", "an", "and", "are", "as", "at",
    "be", "been", "but", "by",
    "did", "do",
    "for", "from",
    "had", "has", "have", "he", "her", "hers", "him", "his",
    "i", "if", "in", "into", "is", "it", "its",
    "me", "my",
    "not",
    "of", "on", "or",
    "so",
    "that", "the", "their", "them", "they", "this", "to",
    "up", "us",
    "was", "we", "what", "who", "why", "will", "with",
    "you", "your",
    0
  };

  for (int i = 0; swords[i] != 0; i++)
    skipList.insert(string(swords[i]));
}


/*
 * This helper-function converts a word to all lower-case, and then removes
 * any leading and/or trailing punctuation.
 *
 * Parameters:
 *   word    The word to process.  It is passed by-value so that it can be
 *           manipulated within the function without affecting the caller.
 *
 * Return value:
 *   The word after all leading and trailing punctuation have been removed.
 *   Of course, if the word is entirely punctuation (e.g. "--") then the result
 *   may be an empty string object (containing "").
 */
string processWord(string word)
{
  // make each character of the word lower case
  for (int i = 0; i < int(word.length()); i++)
  {
    word[i] = tolower(word[i]);
  }

  // now remove the punctuation from beginning of word
  int begin = 0;
  while (word.length() != 0 && ispunct(word[begin]))
  {
    word.erase(begin,1);
  }

  // now remove the punctuation from end of word
  int end = word.length() - 1;
  while (word.length() != 0 && ispunct(word[end]))
  {
    word.erase(end,1);
    end--;
  }
  // output the processed word
  return word;
}

/*
 * This helper-function counts the total number of words processed,
 * the number of unique words, and the number of skipped words in 
 * this document.
 *
 * Parameters:
 * skipList   The set containing the words that are to be skipped
 * wordCounts The map containing both the word and the number of times
 *            the particular word has appeared.
 *
 * No return value (void), but cout's the total number of words
 * processed, the number of unique words, and the number of skipped
 * words in the document
 */ 
void processText(set<string>& skipList, map<string, int>& wordCounts)
{
  // counter for total number of words (not including empty strings)
  int totalwords = 0;

  // counter for number of skipped words
  int skippedwords = 0;

  // for the cin
  string word;

  // Read input until there is no more!
  while (cin >> word)
  {
    string wordprocessed = processWord(word);
    if (wordprocessed != "")
    {
      // update the total word count of the document
      totalwords += 1;

      if (skipList.find(wordprocessed) != skipList.end())
      {
        skippedwords += 1;
      }
      else
      {
        // Update the map for the count of the particular word
        wordCounts[wordprocessed]++;
      }
    }
  }

  // output the number of words in document
  cout << "Total words in document: " << totalwords << endl;

  // output the number of unique words in document
  cout << "Unique words: " << wordCounts.size() << endl;

  // output the number of skipped words in document
  cout << "Skipped words: " << skippedwords << endl;
}


/*
 * This helper-function outputs the generated word-list in descending order
 * of count.  The function uses an STL associative container to sort the words
 * by how many times they appear.  Because multiple words can have the same
 * counts, a multimap is used.
 */
void outputWordsByCount(map<string, int>& wordCounts)
{
  multimap<int, string, greater<int> > sortByCount;
  map<string, int>::const_iterator wIter;

  for (wIter = wordCounts.begin(); wIter != wordCounts.end(); wIter++)
    sortByCount.insert(pair<int, string>(wIter->second, wIter->first));

  multimap<int, string>::const_iterator cIter;
  for (cIter = sortByCount.begin(); cIter != sortByCount.end(); cIter++)
    cout << cIter->second << "\t" << cIter->first << endl;
}

