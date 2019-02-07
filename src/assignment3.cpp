/********************************************
 * @author : Gökhan ÖZELOĞLU                *
 *                                          *
 * @date : 07.12.2018 - 12.12.2018          *
 *                                          *
 * @email : b21627557@cs.hacettepe.edu.tr   *
 ********************************************
 * */


#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstring>
#include <map>

using namespace std;

class Match {
    string away_team;
    string match_ID;
    int minute;
public:
    Match *next_match_node;
    Match *prev_match_node;

    Match(string away, int minu, string id) {
        away_team = away;
        minute = minu;
        match_ID = id;
        next_match_node = NULL;
        prev_match_node = NULL;
    }

    ~Match() {

    }
    string get_away_team() {
        return away_team;
    }

    string get_match_ID() {
        return match_ID;
    }

    int get_minute() {
        return minute;
    }

    Match* addNewMatch(Match *match_node, string away_team, int minute, string match_id);
};

class Footballer {
    string footballer_name;
    string team_name;
public:
    Footballer *next_footballer_node;
    Match *match_node;

    /*Constructors*/
    Footballer() {

    }

    Footballer(string name, string team) {
        footballer_name = name;
        team_name = team;
        next_footballer_node = NULL;
        match_node = NULL;
    }

    // Destructor
    ~Footballer() {

    }
    /*Accessor methods*/
    string get_footballer_name() {
        return footballer_name;
    }

    string get_team_name() {
        return team_name;
    }

    Footballer* addNewFootballer(Footballer *head, string name, string team_name, string away_team, int minute, string match_ID);
    int findPeriod(Footballer *head);
};

class Team {
    string team_name;
public:
    Team *next_team;

    Team(string team) {
        team_name = team;
        next_team = NULL;
    }

    Team() {

    }

    // Destructor
    ~Team() {

    }

    // Accessor method
    string get_team() {

        return team_name;
    }
    Team* addTeamsToList(Team* head, string team_name);
};

Match* Match::addNewMatch(Match *match_node, string away_team, int minute, string match_id) {

    if (match_node == NULL) {   // If any match did not add to the linked list situation
        Match *newMatchNode = new Match(away_team, minute, match_id);   // Created a new match node
        match_node  = newMatchNode;                                     // match_node points to the newMatchNode's prev node

        return match_node;
    } else {
        Match *tmpMatch = match_node;
        Match *prevMatch = match_node;

        if (tmpMatch -> next_match_node == NULL && stoi(match_id) >= stoi((tmpMatch->get_match_ID()))) {
            Match *newMatchNode = new Match(away_team, minute, match_id);   // Created new match node
            tmpMatch -> next_match_node = newMatchNode;                     // The first node's next_match pointer points to the newMatchNode's prev node
            newMatchNode -> prev_match_node = tmpMatch;                     // newMatchNode's prev pointer points to the the first node's prev node

            return match_node;
        }
        else if (tmpMatch -> next_match_node == NULL && stoi(match_id) < stoi(tmpMatch->get_match_ID())) {
            Match *newMatchNode = new Match(away_team, minute, match_id);   // Created new match node
            newMatchNode -> next_match_node = tmpMatch;                     // newMatch node's next node points to the the first node's prev pointer
            tmpMatch -> prev_match_node = newMatchNode;                     // The first match's prev node points to the newMath node's prev pointer
            tmpMatch = newMatchNode;                                        // The match_node pointer points to the newMatch's prev pointer
            tmpMatch -> next_match_node = NULL;

            return match_node;

        } else {

            while (tmpMatch -> next_match_node != NULL) {

                if (stoi(match_id) <= stoi(tmpMatch -> get_match_ID())) {            // If newMatch node wanted to be added middle of the linked list
                    Match *newMatchNode = new Match(away_team, minute, match_id);    // Created new match node
                    newMatchNode -> next_match_node = tmpMatch;                      // newMatch node's next pointer points to the the next node's prev pointer
                    prevMatch -> next_match_node = newMatchNode;                     // The previous node's next pointer points to the newMatch's prev pointer
                    newMatchNode -> prev_match_node = prevMatch;                     // The newNode's prev pointer points to the previous' pointer
                    tmpMatch -> prev_match_node = newMatchNode;                      // The next node's prev pointer points to the newMatch node's prev pointer

                    return match_node;
                }

                prevMatch = tmpMatch;
                tmpMatch = tmpMatch -> next_match_node;
            }

            if (stoi(match_id) <= (stoi(tmpMatch -> get_match_ID())) ) {            // If the last match node is bigger than match_id
                Match *newMatchNode = new Match(away_team, minute, match_id);       // Match node is created

                newMatchNode -> next_match_node = tmpMatch;                         // newMatch node's points to the the last node
                prevMatch -> next_match_node = newMatchNode;                        // Previous node points to the new node
                tmpMatch -> prev_match_node = newMatchNode;                         // Last node's prev node points to the new node
                newMatchNode -> prev_match_node = prevMatch;                        // new node's prev pointer points to the previous node

                return match_node;
            }
            // If the new match node has to be added end of the linked list
            Match *newMatchNode = new Match(away_team, minute, match_id);
            tmpMatch -> next_match_node = newMatchNode;                     // The last node's next pointer points to the newMatch node
            newMatchNode -> prev_match_node = tmpMatch;                     // The newMatch node's prev pointer points to the last node's prev pointer

            return match_node;
        }
    }
}

Footballer* Footballer::addNewFootballer(Footballer *head, string name, string team_name, string away_team, int minute, string match_ID) {

    /*Controls the linked list is empty or not
     * If it is empty, creates and adds the first node(footballer)*/
    if (head == NULL) {
        Footballer *newFootballer = new Footballer(name, team_name);    // Creates a new footballer object

        head = newFootballer;                                           // Links the new footballer to the head pointer

        newFootballer -> match_node = newFootballer -> match_node -> addNewMatch(newFootballer -> match_node, away_team, minute, match_ID);
        return head;
    } else {
        Footballer *newFootballer = new Footballer(name, team_name);    // Creates the new footballer object from Footballer class

        Footballer *tmpNode = head;         // Declared a new pointer for traversing the linked list
        Footballer *prev_node = head;       // To store the previous node

        /**@purpose: This if statement controls the head's next node is NULL or not. While adding second footballer, the program must add here.
         * Because below while loop, it does not add and terminates the loop before adding.*/
        if (tmpNode -> next_footballer_node == NULL) {
            if (name.compare(tmpNode->get_footballer_name()) == 0) {     // Just adds new match to first node
                tmpNode -> match_node = tmpNode -> match_node -> addNewMatch(tmpNode -> match_node, away_team, minute, match_ID);
                return head;
            }

            else if (name.compare(tmpNode -> get_footballer_name()) > 0) {  // Adds the second node after first node
                tmpNode -> next_footballer_node = newFootballer;            // The first node's next footballer pointer points to the new footballer
                newFootballer -> match_node = newFootballer -> match_node -> addNewMatch(newFootballer -> match_node, away_team, minute, match_ID);

                return head;
            }

            else if (name.compare(tmpNode -> get_footballer_name()) < 0) {  // Adds the new node as a first node
                newFootballer -> next_footballer_node = tmpNode;            // newFootballer node's next footballer pointer points to the first node
                head = newFootballer;                                       // head points to the newFootballer

                newFootballer -> match_node = newFootballer -> match_node -> addNewMatch(newFootballer -> match_node, away_team, minute, match_ID);
                return head;
            }

        } else {    // After third node
            int counter = 0;
            while (tmpNode -> next_footballer_node != NULL) {   // Loop goes until finding NULL pointer

                if (name.compare(tmpNode -> get_footballer_name()) == 0) {      // If the new footballer is exists in linked list
                    tmpNode -> match_node = tmpNode -> match_node -> addNewMatch(tmpNode -> match_node, away_team, minute, match_ID);
                    return head;                                                // does nothing and returns thee head without any changes
                }


                if (name.compare(tmpNode -> get_footballer_name()) < 0 && counter == 0) {     // Adds the new footballer as a first node
                    newFootballer -> next_footballer_node = tmpNode;
                    head = newFootballer;                                                   // Updates the head node

                    newFootballer -> match_node = newFootballer -> match_node -> addNewMatch(newFootballer -> match_node, away_team, minute, match_ID);
                    return head;
                }
                if (name.compare(tmpNode  -> get_footballer_name()) < 0 && counter != 0) {  // Adds the new footballer node middle of the linked list
                    newFootballer -> next_footballer_node = tmpNode;    // Firstly, New footballer node points to the next node to not lose
                    prev_node -> next_footballer_node = newFootballer;  // Secondly, previous node points to the new added node

                    newFootballer -> match_node = newFootballer -> match_node -> addNewMatch(newFootballer -> match_node, away_team, minute, match_ID);
                    return head;
                }

                prev_node = tmpNode;
                tmpNode = tmpNode -> next_footballer_node;      // Changes the current node
                counter++;
            }

            /**@purpose: There was a bug while adding the node which is in the 2nd line of the input file, so I added this if statement
             * to control.
             * If the 1st name is bigger than 2nd name, this if statement changes them in ascending order.*/
            if (counter == 1 && name.compare(tmpNode -> get_footballer_name()) < 0) {
                newFootballer -> next_footballer_node = tmpNode;    // New footballer node points to the first node(head)
                head -> next_footballer_node = newFootballer;                               // head points to the new footballer node
                newFootballer -> match_node = newFootballer -> match_node -> addNewMatch(newFootballer -> match_node, away_team, minute, match_ID);

                return head;
            }

            /**@purpose: Below 2 if statement controls the newFootballer node should add to end of the list or before end of the list.*/
            if (name.compare(tmpNode -> get_footballer_name()) < 0) {   // If newFootballer is smaller than last node
                prev_node -> next_footballer_node = newFootballer;      // Last but one node points to the newFootballer node
                newFootballer -> next_footballer_node = tmpNode;        // newFootballer node points to the last node
                newFootballer -> match_node = newFootballer -> match_node -> addNewMatch(newFootballer -> match_node, away_team, minute, match_ID);

                return head;
            }

            if (name.compare(tmpNode -> get_footballer_name()) == 0) {  // If the newFootballer is the same as last node

                // Just adds the new match
                newFootballer -> match_node = newFootballer -> match_node -> addNewMatch(tmpNode -> match_node, away_team, minute, match_ID);

                return head;
            }

            tmpNode -> next_footballer_node = newFootballer;    // Adds the new node end of the list

            newFootballer -> match_node = newFootballer -> match_node -> addNewMatch(newFootballer -> match_node, away_team, minute, match_ID);
            return head;
        }
    }
}

int Footballer::findPeriod(Footballer *head) {
    int first_half_count = 0;
    int second_half_count = 0;

    Footballer *tmpNode = head;
    Match *matchNode = tmpNode -> match_node;

    while (tmpNode -> next_footballer_node != NULL) {   // Loop goes to until footballer node's next is NULL

        while (matchNode -> next_match_node != NULL) {  // Loop goes to until match node's next is NULL

            // Minute comparison
            if (matchNode -> get_minute() >= 0 && matchNode -> get_minute() <= 45) {first_half_count++;}
            else if (matchNode -> get_minute() >= 46 && matchNode -> get_minute() <= 90) {second_half_count++;}
            matchNode = matchNode -> next_match_node;       // The temp match node points to the next match node
        }

        // For the last node which could not comparison because of while statement
        // Compares and increments
        if (matchNode -> get_minute() >= 0 && matchNode -> get_minute() <= 45) {first_half_count++;}
        else if (matchNode -> get_minute() >= 46 && matchNode -> get_minute() <= 90) {second_half_count++;}

        tmpNode = tmpNode -> next_footballer_node;      // The temp footballer node points to the next footballer node
        matchNode = tmpNode -> match_node;              // The temp match node points to the next match node


    } // The while loop, which traversing footballer list, finishes here

    while (matchNode -> next_match_node != NULL) {          // The last footballer's node
        if (matchNode -> get_minute() >= 0 && matchNode -> get_minute() <= 45) {first_half_count++;}
        else if (matchNode -> get_minute() >= 46 && matchNode -> get_minute() <= 90) {second_half_count++;}

        matchNode = matchNode -> next_match_node;           // The temp match node points to the next match
    }

    // For the last footballer's last match
    if (matchNode -> get_minute() >= 0 && matchNode -> get_minute() <= 45) {first_half_count++;}
    else if (matchNode -> get_minute() >= 46 && matchNode -> get_minute() <= 90) {second_half_count++;}


    if (first_half_count > second_half_count) { return 0;}
    else if (first_half_count < second_half_count) { return 1;}
    else { return -1;}

}

Team* Team::addTeamsToList(Team *head, string team_name) {

    if (head == NULL) {                         // If head is pointing to the NULL
        Team *newTeam = new Team(team_name);    // Creates a new team node
        head = newTeam;                         // head points to the newTeam
        return head;
    } else {
        Team *tmpTeam = head;

        // If the head's next pointer points to the NULL and the first node is not the same with parameter team_name
        if (tmpTeam -> next_team == NULL && team_name.compare(tmpTeam->get_team()) != 0) {
            Team *newTeam = new Team(team_name);
            tmpTeam -> next_team = newTeam;         // Adds the new team

            return head;
        }

        while (tmpTeam -> next_team != NULL) {

            if (team_name.compare(tmpTeam -> get_team()) == 0) {    // If team_name is in the linked list
                return head;                                        // Returns without any changing
            }

            tmpTeam = tmpTeam -> next_team;                         // Points to the next team node
        }

        if (team_name.compare(tmpTeam -> get_team()) != 0) {        // If the last team is not the same as team_name
            Team *newTeam = new Team(team_name);
            tmpTeam -> next_team = newTeam;                         // Adds the after last node

            return head;
        }

        return head;    // Not added
    }
}

void printGivenFootballer(fstream& outputFile, Footballer *head, string name) {
    Footballer *tmpNode = head;

    while (tmpNode -> next_footballer_node != NULL) {       // Searches the given footballer

        if (name.compare(tmpNode->get_footballer_name()) == 0) {    // If given  footballer is found in the linked list

            Match *matchNode = tmpNode->match_node;                 // Created a new node for traversing matches node

            outputFile << "Matches of " << name << endl;

            while (matchNode->next_match_node != NULL) {            // Writes on the output file
                outputFile << "Footballer Name: " << name << ",";
                outputFile << "Away Team: " << matchNode->get_away_team() << ",";
                outputFile << "Min of Goal: " << matchNode->get_minute() << ",";
                outputFile << "Match ID: " << matchNode->get_match_ID() << endl;

                matchNode = matchNode->next_match_node;
            }

            // Writes the last match on the output file
            outputFile << "Footballer Name: " << name << ",";
            outputFile << "Away Team: " << matchNode->get_away_team() << ",";
            outputFile << "Min of Goal: " << matchNode->get_minute() << ",";
            outputFile << "Match ID: " << matchNode->get_match_ID() << endl;

            return; // Terminates the function
        }
        tmpNode = tmpNode->next_footballer_node;    // If not found, points to thee next footballer
    }

    if (name.compare(tmpNode -> get_footballer_name()) == 0) {      // If the last footballer is the same as with  given name
        Match *matchNode = tmpNode -> match_node;                   // Created a new match node to traversing on match nodes

        outputFile << "Matches of " << name << endl;

        while (matchNode -> next_match_node != NULL) {              // Writes on the output file
            outputFile << "Footballer Name: " << name << ",";
            outputFile << "Away Team: " << matchNode->get_away_team() << ",";
            outputFile << "Min of Goal: " << matchNode->get_minute() << ",";
            outputFile << "Match ID: " << matchNode->get_match_ID() << endl;

            matchNode = matchNode->next_match_node;
        }

        // Writes the last match on the output file
        outputFile << "Footballer Name: " << name << ",";
        outputFile << "Away Team: " << matchNode->get_away_team() << ",";
        outputFile << "Min of Goal: " << matchNode->get_minute() << ",";
        outputFile << "Match ID: " << matchNode->get_match_ID() << endl;
    }
}

void printAscendingMatchID(fstream& outputFile, Footballer *head, string name) {
    Footballer *tmpNode = head;     // A temp pointer to traversing footballer linked list
    string prevID;                  // Stores the previous ID for comparision match ID's for not repetition

    while (tmpNode -> next_footballer_node != NULL) {

        if (name.compare(tmpNode -> get_footballer_name()) == 0) {      // If the name is found in linked list
            Match *matchNode = tmpNode -> match_node;                   // matchNode points to the footballer's match node

            while (matchNode -> next_match_node != NULL) {              // Traverse the match linked list until NULL
                if (prevID.compare(matchNode -> get_match_ID()) != 0) { // If the ID is not printed out
                    prevID = matchNode -> get_match_ID();               // Updates the new ID
                    outputFile  << "footballer Name: " << name << "," << "Match ID: " << matchNode -> get_match_ID() << endl;
                }
                matchNode = matchNode -> next_match_node;               // Match node points to the next match
            }
            // For the last match node
            if (prevID.compare(matchNode -> get_match_ID()) != 0) {     // Compares the previous match ID
                outputFile << "footballer Name: " << name << "," << "Match ID: " << matchNode -> get_match_ID() << endl;
            }
            return;     // Function terminates
        }
        tmpNode = tmpNode -> next_footballer_node;                      // tmpNode points to the new footballer node
    }

    if (name.compare(tmpNode -> get_footballer_name()) == 0) {          // Compares the name with last footballer node if not found in while loop
        Match *matchNode = tmpNode -> match_node;                       // matchNode points to the footballer's first match

        while (matchNode -> next_match_node != NULL) {                  // Traverse the matches
            if (prevID.compare(matchNode  -> get_match_ID()) != 0) {    // If the previous ID not printed out
                prevID = matchNode -> get_match_ID();                   // prevID updates the new one
                outputFile << "footballer Name: " << name << "," << "Match ID: " << matchNode -> get_match_ID() << endl;
            }

            matchNode = matchNode -> next_match_node;                   // matchNode points the next match
        }
        if (prevID.compare(matchNode -> get_match_ID()) != 0) {         // Prints out the last match if not printed before
            outputFile << "footballer Name: " << name << "," << "Match ID: " << matchNode -> get_match_ID() << endl;
        }
        return;
    }
}

void printDescendingMatchID(fstream& outputFile, Footballer *head, string name) {
    Footballer *tmpNode = head;     // Temp pointer points to the first footballer node
    string prevID;                  // Stores the previous match ID for not repetition

    while (tmpNode -> next_footballer_node != NULL) {

        if (name.compare(tmpNode -> get_footballer_name()) == 0) {
            Match *matchNode = tmpNode -> match_node;                   // matchNode points to the first match

            while (matchNode -> next_match_node != NULL) {              // Traverse the match list until NULL
                matchNode = matchNode -> next_match_node;               // Updates the matchNode for each iteration
            }

            while (matchNode -> prev_match_node != NULL) {              // Traverse the match list in back direction with prev pointer
                if (prevID.compare(matchNode -> get_match_ID()) != 0) { // If the ID is not printed out previous
                    prevID = matchNode -> get_match_ID();               // prevID is updated
                    outputFile << "footballer Name: " << name << "," << "Match ID: " << matchNode -> get_match_ID() << endl;
                }

                matchNode = matchNode -> prev_match_node;               // matchNode points the previous match node
            }
            if (prevID.compare(matchNode -> get_match_ID()) != 0) {     // Prints out the last match
                outputFile << "footballer Name: " << name << "," << "Match ID: " << matchNode -> get_match_ID() << endl;
            }

            return;     // Function terminates here
        }
        tmpNode = tmpNode -> next_footballer_node;                      // Points to the next footballer node
    }

    if (name.compare(tmpNode -> get_footballer_name()) == 0) {          // If the name in the last footballer node
        Match *matchNode = tmpNode -> match_node;

        while (matchNode -> next_match_node != NULL) {                  // Traverse the match node until NULL
            matchNode = matchNode -> next_match_node;                   // matchNode points to the next match node
        }

        while (matchNode -> prev_match_node != NULL) {                  // Traverse the back direction by using prev pointer

            if (prevID.compare(matchNode -> get_match_ID()) != 0) {     // If the ID was not being printed out previous
                prevID = matchNode  -> get_match_ID();                  // Updates the prevID with new ID
                outputFile << "footballer Name: " << name << "," << "Match ID: " << matchNode -> get_match_ID() << endl;
            }
            matchNode = matchNode -> prev_match_node;                   // matchNode points to the previous node
        }

        if (prevID.compare(matchNode -> get_match_ID()) != 0) {         // Prints out the last match
            outputFile << "footballer Name: " << name << "," << "Match ID: " << matchNode -> get_match_ID() << endl;
        }

        return;
    }
}

void printTopGoalScorers(fstream& outputFile, Footballer *head) {
    map<string, int> topScorerMap;      // Map declaration to store footballer's goal scores in key-value structure
    Footballer *tmpNode = head;         // tmpNode for traversing linked list
    int counter = 0;                    // Counts the goal scores

    while (tmpNode -> next_footballer_node != NULL) {       // Loop goes to until last footballer node

        Match *matchNode = tmpNode -> match_node;           // Match pointer for traversing on match linked list

        while (matchNode -> next_match_node != NULL) {      // Counts the goal scores until last match
            counter++;                                      // Increments the goal counts for each iteration
            matchNode = matchNode -> next_match_node;       // matchNode points to the next match node
        }
        counter++;                                          // Increments the goal score for last match
        topScorerMap.insert(make_pair(tmpNode -> get_footballer_name(), counter));  // Adds the footballer name and his goal
        counter = 0;                                        // Updates the counter for next footballer
        tmpNode = tmpNode -> next_footballer_node;          // Points  to the next footbaler
    }

    Match *matchNode = tmpNode -> match_node;               // Declared a new match node for last footballer after while loop

    while (matchNode  -> next_match_node != NULL) {         // Loop goes to until last match
        counter++;                                          // Increments the counter for each match
        matchNode = matchNode -> next_match_node;           // Points to the net match
    }
    counter++;                                              // Increments the counter for last match
    topScorerMap.insert(make_pair(tmpNode -> get_footballer_name(), counter));  // Adds the new footballer and his goal score into map

    map<string, int>::iterator it = topScorerMap.begin();       // Declared a iterator to traversing map
    int topGoal = 0;                                            // The highest goal score in the league

    while (it != topScorerMap.end()) {                          // Loop goes until the end of the map
        if (it -> second > topGoal) {                           // If footballer's goal score is higher than topGoal
            topGoal = it -> second;                             // updates the top goal
        }
        it++;
    }

    it = topScorerMap.begin();                                  // Re-defined iterator to traverse map again

    while (it != topScorerMap.end()) {                          // iterator traverse the map again to print out
        if (it -> second == topGoal) {                          // If the footballer's goal score equal to the top goal
            outputFile << it -> first << endl;                  // Writes on the output file
        }
        it++;
    }
}

void printHattrickScorers(fstream& outputFile, Footballer *head) {
    Footballer *tmpNode = head;                 // Points to the footballer nodes
    int counter = 0;                            // Counts the goal scores
    bool hattrick = false;                      // If none of footballers scored hat-trick

    while (tmpNode -> next_footballer_node != NULL ){       // Traverse the linked list until NULL

        Match *matchNode = tmpNode -> match_node;           // Points to the first match node
        string prevMatchID = matchNode -> get_match_ID();   // Stores the previous match node

        while (matchNode -> next_match_node != NULL) {      // Traverse the match node's until facing NULL

            if (prevMatchID.compare(matchNode -> get_match_ID()) == 0) {    // If the previous match ID matches with the match ID
                counter++;                                                  // Increments the goal score
            }

            if (counter == 3) {                                             // If the goal score is 3 prints out the name
                outputFile << tmpNode -> get_footballer_name() << endl;
                hattrick = true;
                break;  // Terminates the inner-while loop
            }
            prevMatchID = matchNode -> get_match_ID();                      // Updates the prevMatchID with current match
            matchNode = matchNode -> next_match_node;                       // Points to the next match node

        }

        if (prevMatchID.compare(matchNode -> get_match_ID()) == 0) {        //  Controls the last match of the footballer
            counter++;
        }

        if (counter == 3) {                                                 // If the last match and previous 2 matches is the same, prints out the name
            outputFile << tmpNode -> get_footballer_name() << endl;
            hattrick = true;
        }

        counter = 0;                                                        // counter updated for  the next footballer
        tmpNode = tmpNode -> next_footballer_node;                          // Points to the next footballer
    }

    Match *matchNode = tmpNode -> match_node;                               // matchNode for the last footballer
    string prevMatchID = matchNode -> get_match_ID();

    while (matchNode -> next_match_node != NULL) {                          // Traverse the last footballer's matches

        if (prevMatchID.compare(matchNode -> get_match_ID()) == 0) {        // Controls the previous match and current mactch
            counter++;
        }

        if (counter == 3) {                                                 // If the footballer scored 3  goals
            outputFile << tmpNode -> get_footballer_name() << endl;
            hattrick = true;
            break;
        }
        prevMatchID = matchNode -> get_match_ID();                          // prevMatchID updated
        matchNode = matchNode -> next_match_node;                           // Points to the next match
    }

    if (prevMatchID.compare(matchNode -> get_match_ID()) == 0) {            // Controls the last match
        counter++;
    }

    if (counter == 3) {                                                     // Prints out if the last 3 match is the same
        outputFile << tmpNode -> get_footballer_name() << endl;
        hattrick = true;
    }

    if (hattrick == false) {
        outputFile << "False" << endl;
    }
}

int main(int argc, char **argv) {
    // Files declared
    fstream inputFile;
    fstream operationFile;
    fstream outputFile;

    // Opens the file
    inputFile.open(argv[1], ios::in);
    operationFile.open(argv[2], ios::in);
    outputFile.open(argv[3], ios::out);
    string line;

    Footballer *head = new Footballer();
    head = NULL;

    if (inputFile.good()) {         // Input file control
        int counter = 0;
        string name, team, away_team, id;
        int minute;

        string delimiter = ",";
        string token;
        size_t pos = 0;
        while (getline(inputFile, line)) {                                      // Reads the input file line by line
            while((pos = line.find(delimiter)) != std::string::npos) {          // While end of the line
                token = line.substr(0, pos);                                    // Tokenizing operation
                if (counter == 0) { name = token; counter++;}
                else if (counter == 1) { team = token; counter++;}
                else if (counter == 2) { away_team = token ; counter++;}
                else if (counter == 3) { minute = std::stoi(token);counter++;}
                line.erase(0, pos + delimiter.length());
            }
            token = line.substr(0, pos);
            id = token;
            head = head -> addNewFootballer(head, name, team, away_team, minute, id);   // Adds the footballers into linked list
            counter = 0;
        }

    } else {    // If the file cannot open successfully
        cout << "There is a problem while opening input file!" << endl;
        exit(EXIT_FAILURE);
    }

    if (!outputFile.good()) {       // If there is some problem while opening output file
        cout << "There is a problem while opening output file!" << endl;
    }

    int which_period = head -> findPeriod(head);    // Finds the period

    outputFile << "1)THE MOST SCORED HALF" << endl;
    outputFile << which_period << endl;

    outputFile << "2)GOAL SCORER" << endl;
    printTopGoalScorers(outputFile, head);

    outputFile << "3)THE NAMES OF FOOTBALLERS WHO SCORED HAT-TRICK" << endl;
    printHattrickScorers(outputFile, head);

    outputFile << "4)LIST OF TEAMS" << endl;
    Footballer *footballerList = head;
    Team *teamList = new Team();
    teamList = NULL;

    while (footballerList -> next_footballer_node != NULL) {
        teamList = teamList -> addTeamsToList(teamList, footballerList->get_team_name());
        footballerList = footballerList -> next_footballer_node;
    }

    teamList = teamList -> addTeamsToList(teamList, footballerList -> get_team_name());

    while (teamList -> next_team != NULL) {
        outputFile << teamList -> get_team() << endl;
        teamList = teamList -> next_team;
    }
    outputFile << teamList -> get_team() << endl;


    outputFile << "5)LIST OF FOOTBALLERS" << endl;
    Footballer *tmpFootballerNode = head;

    while (tmpFootballerNode -> next_footballer_node != NULL) {
        outputFile << tmpFootballerNode -> get_footballer_name() << endl;
        tmpFootballerNode = tmpFootballerNode -> next_footballer_node;
    }
    outputFile << tmpFootballerNode -> get_footballer_name() << endl;

    if (operationFile.good()) {     // Operation file control
        string delimiter = ",";
        string token;
        size_t pos = 0;
        string first_name, second_name;

        getline(operationFile, line);
        pos = line.find(delimiter);
        first_name = line.substr(0, pos);
        second_name = line.substr(pos+1, line.length());

        outputFile << "6)MATCHES OF GIVEN FOOTBALLER" << endl;
        printGivenFootballer(outputFile, head, first_name);
        printGivenFootballer(outputFile, head, second_name);

        outputFile << "7)ASCENDING ORDER ACCORDING TO MATCH ID" << endl;
        getline(operationFile, line);
        pos = line.find(delimiter);
        first_name = line.substr(0,  pos);
        second_name = line.substr(pos+1, line.length());

        printAscendingMatchID(outputFile, head, first_name);
        printAscendingMatchID(outputFile, head, second_name);

        outputFile << "8)DESCENDING ORDER ACCORDING TO MATCH ID" << endl;
        getline(operationFile, line);
        pos = line.find(delimiter);
        first_name = line.substr(0, pos);
        second_name = line.substr(pos+1, line.length());

        printDescendingMatchID(outputFile, head, first_name);
        printDescendingMatchID(outputFile, head, second_name);
    } else {    // Error situation
        cout << "There is a problem while opening operation file!" << endl;
        exit(EXIT_FAILURE);
    }

    // Files are closed
    inputFile.close();
    operationFile.close();
    outputFile.close();

    // Linked lists are freed
    Footballer *tmp = head;

    while (head -> next_footballer_node != NULL) {
        tmp = head -> next_footballer_node;

        Match *tmpMatch = head -> match_node;
        while (tmpMatch -> next_match_node != NULL) {
            tmpMatch = head -> match_node -> next_match_node;
            delete head -> match_node;
            head -> match_node = tmpMatch;
        }
        tmpMatch = NULL;
        delete tmpMatch;
        delete head -> match_node;
        delete head;
        head = tmp;
    }
    tmp = NULL;
    delete tmp;
    delete head;

    Team *tempTeam = teamList;

    while (tempTeam -> next_team != NULL) {
        tempTeam = teamList -> next_team;
        delete teamList;
        teamList = tempTeam;
    }
    delete teamList;

    return 0;
}