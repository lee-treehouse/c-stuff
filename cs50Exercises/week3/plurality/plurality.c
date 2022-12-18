#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        // printf("candidate %i name being set to %s \n", i, argv[i + 1]);
        candidates[i].votes = 0;
        // printf("candidate %i votes being set to 0 \n", i);
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{

//candidates
    bool candidateFound = false;
    // printf("candidate count is %d \n", candidate_count);
    for (int i=0; i < candidate_count; i++)
    {
        string nameToCheck = candidates[i].name;
        if  (strcmp(name, nameToCheck) == 0)
        {
            // printf("match found - %s matches %s, incremeneting votes \n", name, nameToCheck);
            candidates[i].votes++;
            candidateFound = true;
        }
        // } else 
        // {
        //     printf("match not found - %s doesn't matches %s \n", name, nameToCheck);
        // }
    }
    // TODO
    return candidateFound;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    //determine winning number of votes
    int highestNumberVotes = 0;
    for (int i=0; i < candidate_count; i++)
    {
        int currentVoteCount = candidates[i].votes;
        if (currentVoteCount > highestNumberVotes)
        {
            highestNumberVotes = currentVoteCount;
        }
    }
  
    // count the winners to be able to size array (maybe there's a better way, but start here )
    int winnerCount = 0;
    for (int i=0; i < candidate_count; i++)
    {
        int currentVoteCount = candidates[i].votes;
        if (currentVoteCount == highestNumberVotes)
        {
            winnerCount ++;
        }
    }

    // print winner(s)
    // int winnersOutputted = 0;
    for (int i=0; i < candidate_count; i++)
    {
        int currentVoteCount = candidates[i].votes;
        if (currentVoteCount == highestNumberVotes)
        {
            printf("%s\n", candidates[i].name);
            // winnersOutputted++;
            // if (winnersOutputted == 1 || winnersOutputted < winnerCount)
            // {
            //     printf("\n");
            // }
        }
    }
    return;
}