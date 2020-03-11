#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

vector <string> removeDuplicates (vector <string> &hand, vector <string> &standard_deck);
vector <string> eraseDuplicates3 (vector <string> &hand3, const vector <string> hand2, const vector <string> hand1, const vector <string> hand0, vector <string> &standard_deck);
vector <string> eraseDuplicates2 (vector <string> &hand2, const vector <string> hand1, const vector <string> hand0,  vector <string> &standard_deck);
vector <string> eraseDuplicates1 (vector <string> &hand1, const vector <string> hand0, vector <string> &standard_deck);
vector <string> removeFromStandardDeck (vector <string> &standard_deck, const vector <string> hand);
vector <string> addToUsedPile (vector <string> &used_pile, const string used_card);
void printPlayersHand (const vector <string> hand);
int getMatchingClover (vector <string> hand);
int getMatchingDiamond (vector <string> hand);
int getMatchingSpade (vector <string> hand);
int getMatchingHeart (vector <string> hand);
bool matchFoundClover (vector <string> hand);
bool matchFoundDiamond (vector <string> hand);
bool matchFoundSpade (vector <string> hand);
bool matchFoundHeart (vector <string> hand);


int main()
{
    srand(time(0));
    vector <string> deck_suite;
    deck_suite.insert (deck_suite.end(), {"C", "D", "S", "H"});
    vector <string> deck_rank;
    deck_rank.insert (deck_rank.end(), {"A","2","3","4","5","6","7","8","9","10","J","Q","K"});
    vector <string> hand0, hand1, hand2, hand3;
	vector <string> standard_deck;
	vector <string> original_deck;
	int tempIndexHolder;
	for (unsigned int i = 0; i < 4; i++) // this is to get the standard deck of cards (all 52) in one place
	{
		for (unsigned int j = 0; j < 13; j++)
		{
			standard_deck.push_back (deck_suite.at(i) + deck_rank.at(j));
			original_deck.push_back (deck_suite.at(i) + deck_rank.at(j));
		}
	}
    int random_rank, random_suite;


	// ------------------ For player 0 -----------------------------------

    for (unsigned int i = 1; i <= 6; i++) // this is to get the 6 starting cards
    {
       random_rank = rand () % 13;
       random_suite = rand () % 4;
       string card =  deck_suite.at(random_suite) + deck_rank.at(random_rank);
       hand0.push_back(card);
    }
    removeDuplicates (hand0, standard_deck);
	removeFromStandardDeck (standard_deck, hand0);
	


	// -------------------- For player 1 ---------------------------------------

    for (unsigned int i = 1; i <= 6; i++) // this is to get the 6 starting cards
    {
       random_rank = rand () % 13;
       random_suite = rand () % 4;
       string card =  deck_suite.at(random_suite) + deck_rank.at(random_rank);
       hand1.push_back(card);
    }

	eraseDuplicates1 (hand1, hand0, standard_deck); // this is to remove duplicates from player 1 and player 0
	removeDuplicates (hand1, standard_deck);
	eraseDuplicates1 (hand1, hand0, standard_deck); 
	removeDuplicates (hand1, standard_deck);
	removeFromStandardDeck (standard_deck, hand1);



	// --------------------- For Player 2 -----------------------------------

	for (unsigned int i = 1; i <= 6; i++) // this is to get the 6 starting cards
    {
       random_rank = rand () % 13;
       random_suite = rand () % 4;
       string card =  deck_suite.at(random_suite) + deck_rank.at(random_rank);
       hand2.push_back(card);
    }
	eraseDuplicates2 (hand2, hand1, hand0, standard_deck);
	removeDuplicates (hand2, standard_deck);
	eraseDuplicates2 (hand2, hand1, hand0, standard_deck);
	removeDuplicates (hand2, standard_deck);
	removeFromStandardDeck (standard_deck, hand2);
	

	// ---------------------- For player 3 -----------------------------------------
	
	for (unsigned int i = 1; i <= 6; i++) // this is to get the 6 starting cards
    {
       random_rank = rand () % 13;
       random_suite = rand () % 4;
       string card =  deck_suite.at(random_suite) + deck_rank.at(random_rank);
       hand3.push_back(card);
    }
	eraseDuplicates3 (hand3, hand2, hand1, hand0, standard_deck);
	removeDuplicates (hand3, standard_deck);
	eraseDuplicates3 (hand3, hand2, hand1, hand0, standard_deck);
	removeDuplicates (hand3, standard_deck);
	removeFromStandardDeck (standard_deck, hand3);
	
// ----------------------------------------- For Player 3 end ----------------------------------------


	vector <string> used_pile;
	int random_card_for_used_pile = rand() % standard_deck.size(); // If the beginning of the game is crazy eight reshuffle it
	while (standard_deck.at(random_card_for_used_pile) == "C8" || standard_deck.at(random_card_for_used_pile) == "D8" || standard_deck.at(random_card_for_used_pile) == "S8" || standard_deck.at(random_card_for_used_pile) == "H8")
	{
		random_card_for_used_pile = rand() % standard_deck.size();
		if (standard_deck.at(random_card_for_used_pile) != "C8" && standard_deck.at(random_card_for_used_pile) != "D8" && standard_deck.at(random_card_for_used_pile) != "S8" && standard_deck.at(random_card_for_used_pile) != "H8")break;
	}
	addToUsedPile(used_pile, standard_deck.at(random_card_for_used_pile)); // first card to start the game
	removeFromStandardDeck (standard_deck, used_pile);
	char player_choice;
	char options [26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
	vector <string> eightHolder;
	char suiteToPlay [4] = {'C', 'D', 'S', 'H'};
	char playerSuiteDeclare;
	bool flag = false;
	
	cout << "Pile has " << used_pile.back() << " <--- your turn\n\n";
	while (hand0.size() != 0 && hand1.size() != 0 && hand2.size() != 0 && hand3.size() != 0)  // The game starts from here and continues until conditions are met
	{
		if (standard_deck.size() == 0) break;
		cout << " "; printPlayersHand (hand0); cout << endl;
		cout << "Which one to play? ";
		cin >> player_choice;
		if (player_choice == '?') // cheating option
		{
			cout << "Player 1 "; printPlayersHand(hand1); cout << endl;
			cout << "Player 2 "; printPlayersHand(hand2); cout << endl;
			cout << "player 3 "; printPlayersHand(hand3); cout << endl;
			cout << "Which one to play? ";
			cin >> player_choice;
		}
		int iterator = abs (player_choice - 97);
		while (iterator < 27)
		{
			if  (iterator != hand0.size())
			{
				if (options[iterator] == player_choice)
				{
				cout << "Pile has " << hand0.at(iterator) << endl;
				addToUsedPile (used_pile, hand0.at(iterator));
				hand0.erase (hand0.begin() + iterator);				
				break;
				}
			}
			while (iterator == hand0.size()) // this is the options for draw
			{
				if (standard_deck.size() == 0) break;
				random_card_for_used_pile = rand() % standard_deck.size();
				hand0.push_back (standard_deck.at(random_card_for_used_pile));
				removeFromStandardDeck (standard_deck, hand0);
				printPlayersHand(hand0);
				cout << endl;
				cout << "Which one to play? ";
				cin >> player_choice;
				iterator = abs (player_choice - 97);
				if (player_choice == 'A') iterator = 27;
			}				
		}
		eightHolder.push_back(used_pile.back());
		if (find(eightHolder.begin(), eightHolder.end(), "C8") != eightHolder.end() || find(eightHolder.begin(), eightHolder.end(), "D8") != eightHolder.end() || find(eightHolder.begin(), eightHolder.end(), "S8") != eightHolder.end() || find(eightHolder.begin(), eightHolder.end(), "H8") != eightHolder.end())
		{
			cout << "Which suite you want? ";
			cin >> playerSuiteDeclare;
			eightHolder.erase (eightHolder.begin() + eightHolder.size() - 1 ); // Fix it
		}
		cout << endl;
//-----------------------------------------------------Player 0 has just put down the first card----------------------------------------------
	
//----------------------------------------------------PLayer 1 turn -----------------------------------------------------------
		flag = false;
		vector <string> :: iterator deckIndex = find(original_deck.begin(), original_deck.end(), used_pile.back());
		if (deckIndex != original_deck.end()) // --------------------------------------------- Need to find a matching rank
		{
			tempIndexHolder = distance (original_deck.begin(), deckIndex);
			if (playerSuiteDeclare ==  'C' || playerSuiteDeclare == 'c') tempIndexHolder = 12;  // if an eight is present 
			if (playerSuiteDeclare == 'D' || playerSuiteDeclare == 'd') tempIndexHolder = 25;   // if an eight is present 
			if (playerSuiteDeclare == 'S' || playerSuiteDeclare == 's') tempIndexHolder = 38;   // if an eight is present 
			if (playerSuiteDeclare == 'H' || playerSuiteDeclare == 'h') tempIndexHolder = 51;   // if an eight is present 
			
			if (tempIndexHolder <= 12)   // --------------------------------------- get a card of the matching rank from player's hand
			{
				if (matchFoundClover (hand1))
				{
					tempIndexHolder = getMatchingClover(hand1);
					flag = true;
				}
			}
			else if (tempIndexHolder <= 25) 	// --------------------------------------- get a card of the matching rank from player's hand
			{
				if (matchFoundDiamond (hand1))
				{
					tempIndexHolder = getMatchingDiamond (hand1);
					flag = true;
				}
			}
			else if (tempIndexHolder <= 38)		// --------------------------------------- get a card of the matching rank from player's hand
			{
				if (matchFoundSpade(hand1))
				{
					tempIndexHolder = getMatchingSpade (hand1);
					flag = true;
				}
			}
			else if (tempIndexHolder <= 51)    // --------------------------------------- get a card of the matching rank from player's hand
			{
				if (matchFoundHeart(hand1))
				{
					tempIndexHolder = getMatchingHeart (hand1);
					flag = true;
				}
			}
			if (flag)
			{
				cout << "   Player 1 chose " << hand1.at(tempIndexHolder) << endl << endl;
				cout << "Pile has " << hand1.at(tempIndexHolder) << endl;
				addToUsedPile (used_pile, hand1.at(tempIndexHolder));
				hand1.erase (hand1.begin() + tempIndexHolder);
			}
			else       //-------------------------------------------------- try to get a new card if no match 
			{
				if (tempIndexHolder <= 12)
				{
					while (!(matchFoundClover(hand1)))
					{
						cout << "   Player 1 drawing...\n";
						random_card_for_used_pile = rand() % standard_deck.size();
						hand1.push_back (standard_deck.at(random_card_for_used_pile));
						removeFromStandardDeck (standard_deck, hand1);
					}
					if (matchFoundClover(hand1))
					{
						cout << "   Player 1 chose " << hand1.back() << endl << endl;
						cout << "Pile has " << hand1.back() << endl;
						addToUsedPile(used_pile, hand1.back());
						hand1.erase(hand1.begin() + hand1.size() - 1);
					}
				}
				else if (tempIndexHolder <= 25)
				{
					while (!(matchFoundDiamond(hand1)))
					{
						cout << "   Player 1 drawing...\n";
						if (standard_deck.size() == 0) break;
						random_card_for_used_pile = rand() % standard_deck.size();
						hand1.push_back (standard_deck.at(random_card_for_used_pile));
						removeFromStandardDeck (standard_deck, hand1);
					}
					if (matchFoundDiamond(hand1))
					{
						cout << "   Player 1 chose " << hand1.back() << endl << endl;
						cout << "Pile has " << hand1.back() << endl;
						addToUsedPile(used_pile, hand1.back());
						hand1.erase(hand1.begin() + hand1.size() - 1);
					}
				}
				else if (tempIndexHolder <= 38)
				{
					while (!(matchFoundSpade(hand1)))
					{
						cout << "   Player 1 drawing...\n";
						if (standard_deck.size() == 0) break;
						random_card_for_used_pile = rand() % standard_deck.size();
						hand1.push_back (standard_deck.at(random_card_for_used_pile));
						removeFromStandardDeck (standard_deck, hand1);
					}
					if (matchFoundSpade(hand1))
					{
						cout << "   Player 1 chose " << hand1.back() << endl << endl;
						cout << "Pile has " << hand1.back()  << endl;
						addToUsedPile(used_pile, hand1.back());
						hand1.erase(hand1.begin() + hand1.size() - 1);
					}
				}
				else if (tempIndexHolder <= 51)
				{
					while (!(matchFoundHeart(hand1)))
					{
						cout << "   Player 1 drawing...\n";
						if (standard_deck.size() == 0) break;
						random_card_for_used_pile = rand() % standard_deck.size();
						hand1.push_back (standard_deck.at(random_card_for_used_pile));
						removeFromStandardDeck (standard_deck, hand1);
					}
					if (matchFoundHeart(hand1))
					{
						cout << "   Player 1 chose " << hand1.back() << endl << endl;
						cout << "Pile has " << hand1.back() << endl;
						addToUsedPile(used_pile, hand1.back());
						hand1.erase(hand1.begin() + hand1.size() - 1);
					}
				}
			}	
		}
		eightHolder.push_back(used_pile.back());
		if (find(eightHolder.begin(), eightHolder.end(), "C8") != eightHolder.end() || find(eightHolder.begin(), eightHolder.end(), "D8") != eightHolder.end() || find(eightHolder.begin(), eightHolder.end(), "S8") != eightHolder.end() || find(eightHolder.begin(), eightHolder.end(), "H8") != eightHolder.end())
		{
			int suiteDeclare = rand () % 4;
			cout << "   Player 1 chose " << suiteToPlay[suiteDeclare] << endl; 
			cout << "   Player 1 declared suite " << suiteToPlay[suiteDeclare] << endl;
			cout << "Pile has " << suiteToPlay[suiteDeclare] << "*" << endl; 
			eightHolder.erase (eightHolder.begin() + eightHolder.size() - 1 ); // Fix it
		}
		cout << endl;		
// ---------------------------------------------------------------Player 1 put down their card-----------------------------------------------------------------


// ---------------------------------------------------------------Player 2 turn -----------------------------------------------------------------------
	//}
		flag = false;
		vector <string> :: iterator deckIndex2 = find(original_deck.begin(), original_deck.end(), used_pile.back());
		if (deckIndex2 != original_deck.end()) // --------------------------------------------- Need to find a matching rank
		{
			tempIndexHolder = distance (original_deck.begin(), deckIndex2);
			if (playerSuiteDeclare ==  'C' || playerSuiteDeclare == 'c') tempIndexHolder = 12;  // if an eight is present 
			if (playerSuiteDeclare == 'D' || playerSuiteDeclare == 'd') tempIndexHolder = 25;   // if an eight is present 
			if (playerSuiteDeclare == 'S' || playerSuiteDeclare == 's') tempIndexHolder = 38;   // if an eight is present 
			if (playerSuiteDeclare == 'H' || playerSuiteDeclare == 'h') tempIndexHolder = 51;   // if an eight is present 
			
			if (tempIndexHolder <= 12)   // --------------------------------------- get a card of the matching rank from player's hand
			{
				if (matchFoundClover (hand2))
				{
					tempIndexHolder = getMatchingClover(hand2);
					flag = true;
				}
			}
			else if (tempIndexHolder <= 25) 	// --------------------------------------- get a card of the matching rank from player's hand
			{
				if (matchFoundDiamond (hand2))
				{
					tempIndexHolder = getMatchingDiamond (hand2);
					flag = true;
				}
			}
			else if (tempIndexHolder <= 38)		// --------------------------------------- get a card of the matching rank from player's hand
			{
				if (matchFoundSpade(hand2))
				{
					tempIndexHolder = getMatchingSpade (hand2);
					flag = true;
				}
			}
			else if (tempIndexHolder <= 51)    // --------------------------------------- get a card of the matching rank from player's hand
			{
				if (matchFoundHeart(hand2))
				{
					tempIndexHolder = getMatchingHeart (hand2);
					flag = true;
				}
			}
			if (flag)
			{
				cout << "   Player 2 chose " << hand2.at(tempIndexHolder) << endl << endl;
				cout << "Pile has " << hand2.at(tempIndexHolder) << endl;
				addToUsedPile (used_pile, hand2.at(tempIndexHolder));
				hand2.erase (hand2.begin() + tempIndexHolder);
			}
			else       //-------------------------------------------------- try to get a new card if no match 
			{
				if (tempIndexHolder <= 12)
				{
					while (!(matchFoundClover(hand2)))
					{
						cout << "   Player 2 drawing...\n";
						random_card_for_used_pile = rand() % standard_deck.size();
						hand2.push_back (standard_deck.at(random_card_for_used_pile));
						removeFromStandardDeck (standard_deck, hand2);
					}
					if (matchFoundClover(hand2))
					{
						cout << "   Player 2 chose " << hand2.back() << endl << endl;
						cout << "Pile has " << hand2.back() << endl;
						addToUsedPile(used_pile, hand2.back());
						hand2.erase(hand2.begin() + hand2.size() - 1);
					}
				}
				else if (tempIndexHolder <= 25)
				{
					while (!(matchFoundDiamond(hand2)))
					{
						cout << "   Player 2 drawing...\n";
						if (standard_deck.size() == 0) break;
						random_card_for_used_pile = rand() % standard_deck.size();
						hand2.push_back (standard_deck.at(random_card_for_used_pile));
						removeFromStandardDeck (standard_deck, hand2);
					}
					if (matchFoundDiamond(hand2))
					{
						cout << "   Player 2 chose " << hand2.back() << endl << endl;
						cout << "Pile has " << hand2.back() << endl;
						addToUsedPile(used_pile, hand2.back());
						hand2.erase(hand2.begin() + hand2.size() - 1);
					}
				}
				else if (tempIndexHolder <= 38)
				{
					while (!(matchFoundSpade(hand2)))
					{
						cout << "   Player 2 drawing...\n";
						if (standard_deck.size() == 0) break;
						random_card_for_used_pile = rand() % standard_deck.size();
						hand2.push_back (standard_deck.at(random_card_for_used_pile));
						removeFromStandardDeck (standard_deck, hand2);
					}
					if (matchFoundSpade(hand2))
					{
						cout << "   Player 2 chose " << hand2.back() << endl << endl;
						cout << "Pile has " << hand2.back() << endl;
						addToUsedPile(used_pile, hand2.back());
						hand2.erase(hand2.begin() + hand2.size() - 1);
					}
				}
				else if (tempIndexHolder <= 51)
				{
					while (!(matchFoundHeart(hand2)))
					{
						cout << "   Player 2 drawing...\n";
						if (standard_deck.size() == 0) break;
						random_card_for_used_pile = rand() % standard_deck.size();
						hand2.push_back (standard_deck.at(random_card_for_used_pile));
						removeFromStandardDeck (standard_deck, hand2);
					}
					if (matchFoundHeart(hand2))
					{
						cout << "   Player 2 chose " << hand2.back() << endl << endl;
						cout << "Pile has " << hand2.back() << endl;
						
						addToUsedPile(used_pile, hand2.back());
						hand2.erase(hand2.begin() + hand2.size() - 1);
					}
				}
			}	
		}
		eightHolder.push_back(used_pile.back());
		if (find(eightHolder.begin(), eightHolder.end(), "C8") != eightHolder.end() || find(eightHolder.begin(), eightHolder.end(), "D8") != eightHolder.end() || find(eightHolder.begin(), eightHolder.end(), "S8") != eightHolder.end() || find(eightHolder.begin(), eightHolder.end(), "H8") != eightHolder.end())
		{
			int suiteDeclare = rand () % 4;
			cout << "   Player 2 chose " << suiteToPlay[suiteDeclare] << endl; 
			cout << "   Player 2 declared suite " << suiteToPlay[suiteDeclare] << endl; 
			cout << "Pile has " << suiteToPlay[suiteDeclare] << "*" << endl; 
			eightHolder.erase (eightHolder.begin() + eightHolder.size() - 1 ); // Fix it
		}
		cout << endl;
		
	//------------------------------------------------------------Player 2 put down the card------------------------------------------------------------------------
	
	// -----------------------------------------------------------Player 3 turn -------------------------------------------------------
		flag = false;
		vector <string> :: iterator deckIndex3 = find(original_deck.begin(), original_deck.end(), used_pile.back());
		if (deckIndex3 != original_deck.end()) // --------------------------------------------- Need to find a matching rank
		{
			tempIndexHolder = distance (original_deck.begin(), deckIndex3);
			if (playerSuiteDeclare ==  'C' || playerSuiteDeclare == 'c') tempIndexHolder = 12;  // if an eight is present 
			if (playerSuiteDeclare == 'D' || playerSuiteDeclare == 'd') tempIndexHolder = 25;   // if an eight is present 
			if (playerSuiteDeclare == 'S' || playerSuiteDeclare == 's') tempIndexHolder = 38;   // if an eight is present 
			if (playerSuiteDeclare == 'H' || playerSuiteDeclare == 'h') tempIndexHolder = 51;   // if an eight is present 
			
			if (tempIndexHolder <= 12)   // --------------------------------------- get a card of the matching rank from player's hand
			{
				if (matchFoundClover (hand3))
				{
					tempIndexHolder = getMatchingClover(hand3);
					flag = true;
				}
			}
			else if (tempIndexHolder <= 25) 	// --------------------------------------- get a card of the matching rank from player's hand
			{
				if (matchFoundDiamond (hand3))
				{
					tempIndexHolder = getMatchingDiamond (hand3);
					flag = true;
				}
			}
			else if (tempIndexHolder <= 38)		// --------------------------------------- get a card of the matching rank from player's hand
			{
				if (matchFoundSpade(hand3))
				{
					tempIndexHolder = getMatchingSpade (hand3);
					flag = true;
				}
			}
			else if (tempIndexHolder <= 51)    // --------------------------------------- get a card of the matching rank from player's hand
			{
				if (matchFoundHeart(hand3))
				{
					tempIndexHolder = getMatchingHeart (hand3);
					flag = true;
				}
			}
			if (flag)
			{
				cout << "   Player 3 chose " << hand3.at(tempIndexHolder) << endl << endl;
				cout << "Pile has " << hand3.at(tempIndexHolder) << " <--- your turn" << endl;
				addToUsedPile (used_pile, hand3.at(tempIndexHolder));
				hand3.erase (hand3.begin() + tempIndexHolder);
			}
			else       //-------------------------------------------------- try to get a new card if no match 
			{
				if (tempIndexHolder <= 12)
				{
					while (!(matchFoundClover(hand3)))
					{
						cout << "   Player 3 drawing...\n";
						random_card_for_used_pile = rand() % standard_deck.size();
						hand3.push_back (standard_deck.at(random_card_for_used_pile));
						removeFromStandardDeck (standard_deck, hand3);
					}
					if (matchFoundClover(hand3))
					{
						cout << "   Player 3 chose " << hand3.back() << endl << endl;
						cout << "Pile has " << hand3.back() << " <--- your turn" << endl;
						addToUsedPile(used_pile, hand3.back());
						hand3.erase(hand3.begin() + hand3.size() - 1);
					}
				}
				else if (tempIndexHolder <= 25)
				{
					while (!(matchFoundDiamond(hand3)))
					{
						cout << "   Player 3 drawing...\n";
						if (standard_deck.size() == 0) break;
						random_card_for_used_pile = rand() % standard_deck.size();
						hand3.push_back (standard_deck.at(random_card_for_used_pile));
						removeFromStandardDeck (standard_deck, hand3);
					}
					if (matchFoundDiamond(hand3))
					{
						cout << "   Player 3 chose " << hand3.back() << endl << endl;
						cout << "Pile has " << hand3.back() << " <--- your turn" << endl;
						addToUsedPile(used_pile, hand3.back());
						hand3.erase(hand3.begin() + hand3.size() - 1);
					}
				}
				else if (tempIndexHolder <= 38)
				{
					while (!(matchFoundSpade(hand3)))
					{
						cout << "   Player 3 drawing...\n";
						if (standard_deck.size() == 0) break;
						random_card_for_used_pile = rand() % standard_deck.size();
						hand3.push_back (standard_deck.at(random_card_for_used_pile));
						removeFromStandardDeck (standard_deck, hand3);
					}
					if (matchFoundSpade(hand3))
					{
						cout << "   Player 3 chose " << hand3.back() << endl << endl;
						cout << "Pile has " << hand3.back() << " <--- your turn" << endl;
						addToUsedPile(used_pile, hand3.back());
						hand3.erase(hand3.begin() + hand3.size() - 1);
					}
				}
				else if (tempIndexHolder <= 51)
				{
					while (!(matchFoundHeart(hand1)))
					{
						cout << "   Player 3 drawing...\n";
						if (standard_deck.size() == 0) break;
						random_card_for_used_pile = rand() % standard_deck.size();
						hand3.push_back (standard_deck.at(random_card_for_used_pile));
						removeFromStandardDeck (standard_deck, hand3);
					}
					if (matchFoundHeart(hand3))
					{
						cout << "   Player 3 chose " << hand3.back() << endl << endl;;
						cout << "Pile has " << hand3.back() << " <--- your turn" << endl;
						addToUsedPile(used_pile, hand3.back());
						hand3.erase(hand3.begin() + hand3.size() - 1);
					}
				}
			}	
		}
		eightHolder.push_back(used_pile.back());
		if (find(eightHolder.begin(), eightHolder.end(), "C8") != eightHolder.end() || find(eightHolder.begin(), eightHolder.end(), "D8") != eightHolder.end() || find(eightHolder.begin(), eightHolder.end(), "S8") != eightHolder.end() || find(eightHolder.begin(), eightHolder.end(), "H8") != eightHolder.end())
		{
			int suiteDeclare = rand () % 4;
			cout << "   Player 3 chose " << suiteToPlay[suiteDeclare] << endl; 
			cout << "   Player 3 declared suite " << suiteToPlay [suiteDeclare] << endl;
			cout << "Pile has " << suiteToPlay[suiteDeclare] << "*" << " <--- your turn" << endl; 
			eightHolder.erase (eightHolder.begin() + eightHolder.size() - 1 ); // Fix it
		}
		cout << endl;
	}
	if ((hand0.size() < hand1.size()) && (hand0.size() << hand2.size()) && (hand0.size() < hand3.size())) cout << "You won\n\n";	
	if ((hand1.size() < hand0.size()) && (hand1.size() << hand2.size()) && (hand1.size() < hand3.size())) cout << "Player 1 won\n\n";	
	if ((hand2.size() < hand0.size()) && (hand2.size() << hand1.size()) && (hand2.size() < hand3.size())) cout << "Player 2 won\n\n";	
	if ((hand3.size() < hand0.size()) && (hand3.size() << hand1.size()) && (hand3.size() < hand2.size())) cout << "Player 3 won\n\n";	
	cout << "[ Final Card Distributions ]" << endl;
	cout << "Player 0 "; printPlayersHand (hand0); cout << endl; 
	cout << "Player 1 "; printPlayersHand(hand1); cout << endl;
	cout << "Player 2 "; printPlayersHand(hand2); cout << endl;
	cout << "player 3 "; printPlayersHand(hand3); cout << endl;
return 0;	
}
// All the functions definitions

vector <string> removeDuplicates (vector <string> &hand, vector <string> &standard_deck)
{
    if (standard_deck.size() != 0)
    {
        for (unsigned int i = 0; i < hand.size(); i++) // to check for duplicates in its own hand
        {
            for (unsigned int j = 0; j < hand.size(); j++)
            {
                if (hand.at(i) == hand.at(j) && i != j)
                {
                    hand.erase(hand.begin() + i);
				    if (standard_deck.size() == 0) break; 
				    int random_card = rand() % standard_deck.size();
				    hand.push_back(standard_deck.at(random_card));
                }
            }
        }
    }
    return hand;
}
vector <string> eraseDuplicates3 (vector <string> &hand3, const vector <string> hand2, const vector <string> hand1, const vector <string> hand0, vector <string> &standard_deck)
{
    if (standard_deck.size() != 0)
	{
	    for (unsigned int i = 0; i < hand3.size(); i++)
	    {
		    for (unsigned int j = 0; j < hand2.size(); j++)			
		    {
			    while (hand3.at(i) == hand2.at(j))
			    {
				    hand3.erase (hand3.begin() + i);
				    if (standard_deck.size() == 0) break;
				    int random_card = rand () % standard_deck.size();
				    hand3.push_back(standard_deck.at(random_card));
			    }
		    }
	    }
	    for (unsigned int i = 0; i < hand3.size(); i++)
	    {
		    for (unsigned int j = 0; j < hand1.size(); j++)
		    {
			    while (hand3.at(i) == hand1.at(j))
			    {
				    hand3.erase (hand3.begin() + i);
				    if (standard_deck.size() == 0) break;
				    int random_card = rand () % standard_deck.size();
				    hand3.push_back(standard_deck.at(random_card));
			    }
		    }
	    }	
	    for (unsigned int i = 0; i < hand3.size(); i++)
	    {
		    for (unsigned int j = 0; j < hand0.size(); j++)
		    {
			    while (hand3.at(i) == hand0.at(j))
			    {
				    hand3.erase (hand3.begin() + i);
				    if (standard_deck.size() == 0) break;
				    int random_card = rand () % standard_deck.size();
				    hand3.push_back(standard_deck.at(random_card));
			    }
		    }
	    }
	}
	return hand3;
}
vector <string> eraseDuplicates2 (vector <string> &hand2, const vector <string> hand1, const vector <string> hand0,  vector <string> &standard_deck)
{
    if (standard_deck.size() != 0)
	{
	    for (unsigned int i = 0; i < hand2.size(); i++)
	    {
		    for (unsigned int j = 0; j < hand1.size(); j++)
		    {
			    while(hand2.at(i) == hand1.at(j))
			    {
				    hand2.erase (hand2.begin() +i);
				    if (standard_deck.size() == 0) break;
				    int random_card = rand () % standard_deck.size();
				    hand2.push_back(standard_deck.at(random_card));
			    }
		    }
	    }
	    for (unsigned int i = 0; i < hand2.size(); i++)
		{
			    for (unsigned int j = 0; j < hand0.size(); j++)
			    {
				    while (hand2.at(i) == hand0.at(j))
				    {
					    hand2.erase (hand2.begin() +i);
					    if (standard_deck.size() == 0) break;
					    int random_card = rand () % standard_deck.size();
					    hand2.push_back(standard_deck.at(random_card));
				    }
			    }
		}
	}
	return hand2;
}
vector <string> eraseDuplicates1 (vector <string> &hand1, const vector <string> hand0, vector <string> &standard_deck)
{
    if (standard_deck.size() != 0)
	{
	    for (unsigned int i =0; i < hand1.size(); i++)
	    {
		    for (unsigned int j = 0;  j < hand0.size(); j++)
		    {
			    while (hand1.at(i) == hand0.at(j))
			    {
				    hand1.erase (hand1.begin() +i);
				    if (standard_deck.size() == 0) break;
				    int random_card = rand () % standard_deck.size();
				    hand1.push_back(standard_deck.at(random_card));
			    }
		    }
	    }
	}
	return hand1;
}
vector <string> removeFromStandardDeck (vector <string> &standard_deck, const vector <string> hand)
{
    if (standard_deck.size() != 0)
    {
        for (unsigned int i = 0; i < hand.size(); i++)
        {
            for (unsigned int j = 0; j < standard_deck.size(); j++)
            {
                if (hand.at(i) == standard_deck.at(j)) standard_deck.erase(standard_deck.begin() + j);
            }
        }
    }
    return standard_deck;
}
vector <string> addToUsedPile (vector <string> &used_pile, const string used_card)
{
	used_pile.push_back(used_card);
	return used_pile;
}
void printPlayersHand (const vector <string> hand)
{
	char options [27] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z','A'};
	for (unsigned int i = 0; i <= hand.size(); i++)
		{
			if (i == hand.size()) cout << "(" << options [i] << ") " << "draw\n";
			else cout << "(" << options [i] << ") " << hand.at(i) << " ";
		}
}
int getMatchingClover (vector <string> hand)
{
	int i;
	vector <string> cloverSuite; 
	cloverSuite.insert (cloverSuite.end(), {"CA", "C2", "C3", "C4", "C5", "C6", "C7", "C8", "C9", "C10", "CJ", "CQ", "CK"});
	for (i = 0; i < hand.size(); i++)
	{
		for (unsigned int j = 0; j < cloverSuite.size(); j++)
		{
			if (hand.at(i) == cloverSuite.at(j)) return i;
		}
	}	
	return i;
}
int getMatchingDiamond (vector <string> hand)
{
	int i;
	vector <string> DiamondSuite; 
	DiamondSuite.insert (DiamondSuite.end(), {"DA", "D2", "D3", "D4", "D5", "D6", "D7", "D8", "D9", "D10", "DJ", "DQ", "DK"});
	for (i = 0; i < hand.size(); i++)
	{
		for (unsigned int j = 0; j < DiamondSuite.size() ; j++)
		{
			if (hand.at(i) == DiamondSuite.at(j)) return i;
		}
	}	
	return i;
}
int getMatchingSpade (vector <string> hand)
{
	int i;
	vector <string> SpadeSuite; 
	SpadeSuite.insert (SpadeSuite.end(), {"SA", "S2", "S3", "S4", "S5", "S6", "S7", "S8", "S9", "S10", "SJ", "SQ", "SK"});
	for (i = 0; i < hand.size(); i++)
	{
		for (unsigned int j = 0; j < SpadeSuite.size(); j++)
		{
			if (hand.at(i) == SpadeSuite.at(j)) return i;
		}
	}	
	return i;
}
int getMatchingHeart (vector <string> hand)
{
	int i;
	vector <string> HeartSuite; 
	HeartSuite.insert (HeartSuite.end(), {"HA", "H2", "H3", "H4", "H5", "H6", "H7", "H8", "H9", "H10", "HJ", "HQ", "HK"});
	for (i = 0; i < hand.size(); i++)
	{
		for (unsigned int j = 0; j < HeartSuite.size(); j++)
		{
			if (hand.at(i) == HeartSuite.at(j)) return i;
		}
	}	
	return i;
}
bool matchFoundClover (vector <string> hand)
{
	bool flag = false;
	vector <string> cloverSuite; 
	cloverSuite.insert (cloverSuite.end(), {"CA", "C2", "C3", "C4", "C5", "C6", "C7", "C8", "C9", "C10", "CJ", "CQ", "CK"});
	for (unsigned int i = 0; i < hand.size(); i++)
	{
		for (unsigned int j = 0; j < cloverSuite.size(); j++)
		{
			if (hand.at(i) == cloverSuite.at(j)) flag = true;
		}
	}	
	return flag;
}
bool matchFoundDiamond (vector <string> hand)
{
	bool flag = false;
	vector <string> DiamondSuite; 
	DiamondSuite.insert (DiamondSuite.end(), {"DA", "D2", "D3", "D4", "D5", "D6", "D7", "D8", "D9", "D10", "DJ", "DQ", "DK"});
	for (unsigned int i = 0; i < hand.size(); i++)
	{
		for (unsigned int j = 0; j < DiamondSuite.size() ; j++)
		{
			if (hand.at(i) == DiamondSuite.at(j)) flag  = true;
		}
	}	
	return flag;
}
bool matchFoundSpade (vector <string> hand)
{
	bool flag = false;
	vector <string> SpadeSuite; 
	SpadeSuite.insert (SpadeSuite.end(), {"SA", "S2", "S3", "S4", "S5", "S6", "S7", "S8", "S9", "S10", "SJ", "SQ", "SK"});
	for (unsigned int i = 0; i < hand.size(); i++)
	{
		for (unsigned int j = 0; j < SpadeSuite.size(); j++)
		{
			if (hand.at(i) == SpadeSuite.at(j)) flag = true;
		}
	}
	return flag;
}	
bool matchFoundHeart (vector <string> hand)
{
	bool flag = false;
	vector <string> HeartSuite; 
	HeartSuite.insert (HeartSuite.end(), {"HA", "H2", "H3", "H4", "H5", "H6", "H7", "H8", "H9", "H10", "HJ", "HQ", "HK"});
	for (unsigned int i = 0; i < hand.size(); i++)
	{
		for (unsigned int j = 0; j < HeartSuite.size(); j++)
		{
			if (hand.at(i) == HeartSuite.at(j)) flag = true;
		}
	}	
	return flag;
}