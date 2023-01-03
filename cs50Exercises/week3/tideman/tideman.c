#include <cs50.h>
#include <stdio.h>
#include <string.h>

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
    int numVotersWhoPreferWinner;
} pair;

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
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        int candidate_index = ranks[i];
        for (int j = i + 1; j < candidate_count; j++)
        {
            int opponent_index = ranks[j];
            preferences[candidate_index][opponent_index]++;
            // printf("incrementing preferences to say that this voter prefers %d to %d \n", candidate_index, opponent_index);
        }
    }

    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            int candidatePreferredCount = preferences[i][j];
            int opponentPreferredCount = preferences[j][i];

            // ok so first time the pair count is 0 right?
            if (candidatePreferredCount > opponentPreferredCount)
            {
                pair a = {.winner = i, .loser = j, .margin = candidatePreferredCount - opponentPreferredCount, .numVotersWhoPreferWinner = candidatePreferredCount};
                pairs[pair_count] = a;
                pair_count++;
                // printf("Adding a pair - winner is %d and loser is %d and margin is %d pair count is %d \n", a.winner, a.loser, a.margin, pair_count);
            }
            if (candidatePreferredCount < opponentPreferredCount)
            {
                pair a = {.winner = j, .loser = i, .margin = opponentPreferredCount - candidatePreferredCount, .numVotersWhoPreferWinner = opponentPreferredCount};
                pairs[pair_count] = a;
                pair_count++;
                // printf("Adding a pair - winner is %d and loser is %d and margin is %d  and pair count is %d \n", a.winner, a.loser, a.margin, pair_count);
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

void hardcodeValuesBeforeSorting(void)
{
    preferences[0][0] = 0;
    preferences[0][1] = 6;
    preferences[0][2] = 7;

    preferences[1][0] = 3;
    preferences[1][1] = 0;
    preferences[1][2] = 4;

    preferences[2][0] = 2;
    preferences[2][1] = 5;
    preferences[2][2] = 0;

    pairs[0].winner = 0;
    pairs[0].loser = 1;

    pairs[1].winner = 0;
    pairs[1].loser = 2;

    pairs[2].winner = 2;
    pairs[2].loser = 1;

    printf("\n final preferences state \n");
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            printf("preferences[%d][%d] = %d \n", i, j, preferences[i][j]);
            // printf("incrementing preferences to say that this voter prefers %d to %d \n", candidate_index, opponent_index);
        }
    }
}

void printTestResults(void)
{
    printf("test results \n");
    for (int i = 0; i < 3; i++)
        printf("%i %i ", pairs[i].winner, pairs[i].loser);
    printf("\n end of test results \n");
}

// someone elses sort pairs from here - to see if it passes the tests - https://www.reddit.com/r/cs50/comments/wqze44/tideman_tests_show_the_code_works_properly/
// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // bubble sort in descending order
    for (int i = 0; i < pair_count - 1; i++)
    {
        // the '- i' in the upper bound of j ensures
        // the code doenst operate over sorted area
        for (int j = 0; j < pair_count - 1 - i; j++)
        {
            if (preferences[pairs[j].winner][pairs[j].loser] <
                preferences[pairs[j + 1].winner][pairs[j + 1].loser])
            {
                int w = pairs[j].winner;
                int l = pairs[j].loser;
                pairs[j].winner = pairs[j + 1].winner;
                pairs[j].loser = pairs[j + 1].loser;
                pairs[j + 1].winner = w;
                pairs[j + 1].loser = l;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs_old(void)
{

    int debug = 1;

    // hardcode values before sortinng
    if (debug == 0)
    {
        hardcodeValuesBeforeSorting();

        printf("\nPairs before sorting:\n");
        for (int i = 0; i < pair_count; i++)
        {
            printf("Winner: %d, Loser %d, Margin %d, numVotersWhoPrefer %d \n", pairs[i].winner, pairs[i].loser, pairs[i].margin, pairs[i].numVotersWhoPreferWinner);
        }
    }

    for (int i = 0; i < pair_count - 1; i++)
    {
        // 1 and 2
        // ie all up 0 and 1, 0 and 2
        // 1 and 1, 1 and 2
        for (int j = 1; j < pair_count; j++)
        {
            if (pairs[i].numVotersWhoPreferWinner < pairs[j].numVotersWhoPreferWinner)
            {
                // temp = pairs[i];
                pair temp = {.winner = pairs[i].winner, .loser = pairs[i].loser, .margin = pairs[i].margin, .numVotersWhoPreferWinner = pairs[i].numVotersWhoPreferWinner};
                pairs[i] = pairs[j];
                pairs[j] = temp;
            }
        }
    }

    if (debug == 0)
    {
        printf("\nPairs after sorting:\n");
        for (int i = 0; i < pair_count; i++)
        {
            printf("Winner: %d, Loser %d, Margin %d, numVotersWhoPrefer %d \n", pairs[i].winner, pairs[i].loser, pairs[i].margin, pairs[i].numVotersWhoPreferWinner);
        }

        // TODO - return to this, as I believe the program description doesn't want you to sort manually
        // ok guess I'll look at it right now, since though it compiles with gcc, check50 says fails to compile
        // qsort(pairs, pair_count, sizeof(pair), pairs_comparator);

        printTestResults();
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO
    return;
}

// Print the winner of the election
void print_winner(void)
{
    // TODO
    return;
}