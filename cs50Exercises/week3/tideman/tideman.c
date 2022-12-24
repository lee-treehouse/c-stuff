#include <cs50.h>
#include <stdio.h>
#include <string.h>


// gcc -o tideman tideman.c -lcs50


// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
    int margin;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
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
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
 for (int i=0; i < candidate_count; i++)
 {
    if (strcmp(name, candidates[i]) == 0)
    {
        ranks[rank] = i;
        return true;
    }
 }
/* 
 The function takes arguments rank, name, and ranks. If name is a match for the name of a valid candidate, then you should update the ranks array to 
 indicate that the voter has the candidate as their rank preference (where 0 is the first preference, 1 is the second preference, etc.)
Recall that ranks[i] here represents the user’s ith preference.
The function should return true if the rank was successfully recorded, and false otherwise (if, for instance, name is not the name of one of the candidates).
You may assume that no two candidates will have the same name.
 */
 
    // TODO
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{

/*for example 
candidate number - name 
0 Holly
1 Kate
2 Evan

so I run it like ./tideman Holly Kate Evan 
number o voters 1
votes 
Kate 
Evan
Holly

now this persons vote goes Kate, Evan, Holly 
so their ranks array looks like this [1, 2, 0]

preferences array is going to look like 

people who prefer holly to kate
preferences[0][1]
people who prefer holly to evan
preferences[0][2]

people who prefer kate to holly
preferences [1][0]
people who prefer kate to evan
preferences [1][2]

people who prefer evan to holly
preferences [2][0]
people who prefer evan to kate
preferences [2][1]

for this set of ranks (again - [1,2,0]) we would be incrementing 

people who prefer kate to evan
preferences [1][2]

people who prefer kate to holly
preferences [1][0]

people who prefer evan to holly
preferences [2][0]

so we would loop through the ranks as the first port of call - the size of the ranks is already in a variable, candidate count
*/

for (int i=0; i<candidate_count; i++)
{
    int candidate_index = ranks[i];
    for (int j=i+1; j<candidate_count; j++)
    {
        int opponent_index = ranks[j];
        preferences[candidate_index][opponent_index]++;
        printf("incrementing preferences to say that this voter prefers %d to %d \n", candidate_index, opponent_index);
    }
}
/*
The function is called once for each voter, and takes as argument the ranks array, (recall that ranks[i] is the voter’s ith preference, 
where ranks[0] is the first preference).
The function should update the global preferences array to add the current voter’s preferences. Recall that preferences[i][j] should 
represent the number of voters who prefer candidate i over candidate j.
You may assume that every voter will rank each of the candidates.
*/
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    /*
The function should add all pairs of candidates where one candidate is preferred to the pairs array. 
A pair of candidates who are tied (one is not preferred over the other) should not be added to the array.
The function should update the global variable pair_count to be the number of pairs of candidates. (The pairs 
should thus all be stored between pairs[0] and pairs[pair_count - 1], inclusive).

ok so pair is a struct that has a winner (int) and loser (int)

I guess those ints are referring to candidate index.. 

then we have 
pair pairs[MAX * (MAX - 1) / 2];
int pair_count;

so to use our example before 

./tideman Holly Kate Evan
Number of voters: 1
Rank 1: Kate
Rank 2: Evan
Rank 3: Holly
incrementing preferences to say that this voter prefers 1 to 2 
incrementing preferences to say that this voter prefers 1 to 0 
incrementing preferences to say that this voter prefers 2 to 0 
what would we do in this function?

well we probably need more voters!

ok I found this 
Next up is a struct called pair, used to represent a pair of candidates: each pair 
includes the winner’s candidate index and the loser’s candidate index.

so then, in our example the pairs we could report on are 
Holly & Kate 
Holly & Evan
Kate & Evan 

I guess this is going to relate to 
preferences [2][0]

basically we can look at each prefence and see who wins (not by how much though i think)
eg.. wan compare how many prefer evan to holly (2 to 0) and how many prefer holly to evan (0 to 2) to see who wins? 
*/

// we gotta check if we could count a pair twice this way, let's see

// holly-kate holly-evan
// kate-evan

//nope looks good

for (int i=0; i<candidate_count; i++)
{
    for (int j=i+1; j<candidate_count; j++)
    {
        int candidatePreferredCount = preferences[i][j];
        int opponentPreferredCount = preferences[j][i];
                
        // ok so first time the pair count is 0 right? 
        if (candidatePreferredCount > opponentPreferredCount)
        {
            pair a = { .winner = i, .loser = j, .margin = candidatePreferredCount - opponentPreferredCount };
            pairs[pair_count] = a;
            pair_count++;
            printf("Adding a pair - winner is %d and loser is %d and margin is %d pair count is %d \n", a.winner, a.loser, a.margin, pair_count);
        }
        if (candidatePreferredCount < opponentPreferredCount)
        {
            pair a = { .winner = j, .loser = i, .margin = opponentPreferredCount - candidatePreferredCount };
            pairs[pair_count] = a;
            pair_count++;
            printf("Adding a pair - winner is %d and loser is %d and margin is %d  and pair count is %d \n", a.winner, a.loser, a.margin, pair_count);
        }
    }
}

    return;
}

// https://stackoverflow.com/questions/8721189/how-to-sort-an-array-of-structs-in-c
int pairs_comparator(const void *v1, const void *v2)
{
    const pair *p1 = (pair *)v1;
    const pair *p2 = (pair *)v2;
    if (p1->margin < p2->margin)
        return -1;
    else if (p1->margin > p2->margin)
        return +1;
    else
        return 0;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{



qsort(pairs, pair_count, sizeof(pair), pairs_comparator);

    /*
    The function should sort the pairs array in decreasing order of strength of victory, 
    where strength of victory is defined to be the number of voters who prefer the preferred candidate. 
    If multiple pairs have the same strength of victory, you may assume that the order does not matter.
    */
    // TODO
    // ok so we are going to sort pairs by .margin
    // just saw that we shouldn't have modified this struct but i'll start there and iterate
    // i think it's also ok to sort in the simplest way imaginable and then improve

    return;
}

bool wouldCycleBeCreatedIfILockedInThisPair(int winner, int loser)
{
    // locked[i][j] means i is locked in over j
// bool locked[MAX][MAX];
   // for (int 0 )
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
 // locked[i][j] means i is locked in over j
 // bool locked[MAX][MAX];
 
for (int i=0; i<pair_count; i++)
{
    pair pair = pairs[i];
    
    // how to calculate
    //bool cyclesCreated = false;

    printf("the pair i am going to check is %d - %d \n", pair.winner, pair.loser);

    //locked[pair.winner][pair.loser] = !cyclesCreated;
}


 
    // TODO
    return;
}

// Print the winner of the election
void print_winner(void)
{
    // TODO
    return;
}