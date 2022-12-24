#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>


// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
   for (int i=0; i < candidate_count; i++)
    {
        string nameToCheck = candidates[i].name;
        if  (strcmp(name, nameToCheck) == 0)
        {
            
            // example 
            // voter 0 lists Alice(index zero of candidates) as her first preference 
            // voter 0 lists Charlie(index two of candidates) as her second preference 
            // voter 0 lists Bob(index one of candidates) as her third preference 
            // preferences[0][0] = 0
            // preferences[0][1] = 2
            // preferences[0][2] = 1
            
            // printf("setting preferences for voter %d and rank %d to candidate %d", voter, rank, i);
            preferences[voter][rank] = i;
            return true;
        }
    }
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
// printf("entering tabulate function \n");
// preferences[i][j] is jth preference for voter i
// int preferences[MAX_VOTERS][MAX_CANDIDATES];

           // example 
            // voter 0 lists Alice(index zero of candidates) as her first preference 
            // voter 0 lists Charlie(index two of candidates) as her second preference 
            // voter 0 lists Bob(index one of candidates) as her third preference 
            // preferences[0][0] = 0
            // preferences[0][1] = 2
            // preferences[0][2] = 1
 
//int voter_count;
//int candidate_count;

//candidate candidates[MAX_CANDIDATES]; (votes, eliminated)

// reset candidates vote count 
    // printf("resetting candidate counts \n");
   for (int i=0; i < candidate_count; i++)
    {
        candidates[i].votes = 0;
    }

    // iterate through each voter and find their first preference that hasn't been eliminated, and count that vote
   // for each voter
   // printf("tabulating each voters votes\n");
   for (int i=0; i < voter_count; i++)
   {
   //  printf("starting loop for voter %d\n", i);

    // for each preference
    for (int j=0; j< candidate_count; j++)
    {
//        printf("considering voter %d and candidate %d \n", i, j);
       int preferenceIndex = preferences[i][j];
       if (!candidates[preferenceIndex].eliminated ) 
       {
            candidates[preferenceIndex].votes++;
           //  printf("breaking from preference loop for voter %d as vote found for active candidate %d \n", i, j);
            break;
       }
    }
   }
    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    // math ceiling 
    int votesRequired =  (int)ceil(voter_count / 2);

    // exactly half the votes is not enough.. this is a bit hacky, revisit once tests are passing 
    // maybe math.floor instead of math.ceil above and always add one (think it through first!)
    if ((votesRequired * 2) == voter_count)
    {
        votesRequired++;
    }

    for (int i=0; i < candidate_count; i++)
    {
        int voteCount = candidates[i].votes;
        if (voteCount >= votesRequired)
        {
            printf("%s\n",candidates[i].name);
            return true;
        }
    }
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    int lowestVoteCountFound = voter_count;
    for (int i=0; i < candidate_count; i++)
    {
        if (!candidates[i].eliminated)
        {
            int voteCount = candidates[i].votes;
            if (voteCount < lowestVoteCountFound)
            {
                lowestVoteCountFound = voteCount;
            }
        }
    }
    return lowestVoteCountFound;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    for (int i=0; i < candidate_count; i++)
    {
        if (!candidates[i].eliminated)
        {
            int voteCount = candidates[i].votes;
            if (voteCount != min)
            {
                return false;
            }
        }
    }
    return true;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{

    for (int i=0; i < candidate_count; i++)
    {
        if (!candidates[i].eliminated)
        {
            int voteCount = candidates[i].votes;
            if (voteCount == min)
            {
                candidates[i].eliminated = true;
            }
       }
    }
    return;
}