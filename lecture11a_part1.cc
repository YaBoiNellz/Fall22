#include <map>
#include <string>
#include <iostream>
#include <vector>
using namespace std;

// Shows how the map that is eventually produced, used to print the required answers
void printHighChangeables(const map<string, vector<string>> & adjacentWords, int minWords=15){

	// Steps through the map to print and entrues that are pairs consisting of a word and vector of words
	// const references are used to replace complicated expressions and avoid making unneeded copies
	for( auto &entry: adjacentWords){
		const vector<string> & words = entry.second; // const

		if( words.size() >= minWords){
			cout << entry.first << " (" << words.size() << "):";
			for(auto &str: words){
				cout << " " << str; 
			}
			cout << endl;
		}
	}
}

// Test to see if two words are the same except one character
bool oneCharOff( const string & word1, const string & word2){

	// if they are not the same length then they cannot be the same except one character
	if (word1.length() != word2.length())
		return false; 

	int diffs =  0; // count of differences

	// traversing through the word
	for (int i = 0; i < word1.length(); i++)
		//checking character by character of word if they are equal
		if( word1[i] != word2[i])
			// return false if difference is more than 1
			if (++diffs > 1)
				return false;

	// boolean expression that should evaluate to true
	return diffs == 1; 
}

// Method 1
// Brute-force: test all pairs of words
map<string, vector<string>> computeAdjacentWordsMethod1( const vector<string> & words){

	map<string, vector<string>> adjWords; 

	for(int i=0; i < words.size(); ++i)
		for (int j=i+1; j < words.size(); ++j)
			// if we find a part that differ only one character, update the map
			if( oneCharOff(words[i], words[j])){
				adjWords[words[i]].push_back(words[j]);
				adjWords[words[j]].push_back(words[i]);
			}
	return adjWords;
}

// Method 2
// Grip the words by their length, to avoid comparing words of different lengths
map<string, vector<string>> computeAdjacentWordsMethod2( const vector<string> & words){

	map<string, vector<string>> adjWords; 
	map<int, vector<string>> wordsByLength; 

	// Group the words by length
	for (auto & thisWord: words)
		// key is the intereger representing a word length
		// value is the vector of all the words of that length
		wordsByLength[thisWord.length()].push_back(thisWord);

	// Work on each group separately
	for (auto & entry: wordsByLength){
		const vector<string> & groupsWords = entry.second;

		for(int i=0; i < groupsWords.size(); ++i)
			for (int j=i+1; j < groupsWords.size(); ++j)
				if( oneCharOff(groupsWords[i], groupsWords[j])){
					adjWords[groupsWords[i]].push_back(groupsWords[j]);
					adjWords[groupsWords[j]].push_back(groupsWords[i]);
				}
	}

	return adjWords;
}

// Method 3
map<string, vector<string>> computeAdjacentWordsMethod3( const vector<string> & words){

	map<string, vector<string>> adjWords; 
	map<int, vector<string>> wordsByLength; 

	// Group the words by length
	for (auto & str: words)
		wordsByLength[str.length()].push_back(str);

	// Work on each group separately
	for (auto & entry: wordsByLength){
		const vector<string> & groupsWords = entry.second;
		int groupNum = entry.first;

		for(int i=0; i < groupNum; ++i){
			map<string, vector<string>> repToWord; 

			for (auto & str: groupsWords){
				string rep = str; 
				rep.erase(i,1);
				repToWord[rep].push_back(str);
			}
			for (auto &entry: repToWord){
				const vector<string> & clique = entry.second; if( clique.size( ) >= 2 )

				for( int p = 0; p < clique.size( ); ++p )
					for( int q = p + 1; q < clique.size( ); ++q ) {
						adjWords[ clique[ p ] ].push_back( clique[ q ] );
						adjWords[ clique[ q ] ].push_back( clique[ p ] ); 
					}
			}
		}
	}
	
	return adjWords;
}

int main( )
{
    map<string, vector<string>> wordsOneChar;
    vector<string> words;

    //Part 1

    words.push_back("dine");
    words.push_back("fine");
    words.push_back("line");
    words.push_back("mine");
    words.push_back("nine");
    words.push_back("pipe");
    words.push_back("vine");
    words.push_back("wide");
    words.push_back("wife");
    words.push_back("wire");
    words.push_back("wind");
    words.push_back("wing");
    words.push_back("wink");
    words.push_back("wins");

    wordsOneChar[ "wine" ] = words;

   printHighChangeables(wordsOneChar);

   // Adding more words
   words.push_back("print");
   words.push_back("trint");
   words.push_back("prilt");

   // Method 1
   cout << "METHOD 1" << endl;
   wordsOneChar = computeAdjacentWordsMethod1(words);
   printHighChangeables(wordsOneChar, 2);

   // Method 2
   cout << "METHOD 2" << endl;
   wordsOneChar = computeAdjacentWordsMethod2(words);
   printHighChangeables(wordsOneChar, 2);

   // Method 3
   cout << "METHOD 3" << endl;
   wordsOneChar = computeAdjacentWordsMethod2(words);
   printHighChangeables(wordsOneChar, 2);

    return 0;
}