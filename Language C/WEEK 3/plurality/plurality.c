#include <cs50.h>
#include <stdio.h>
#include <string.h>

typedef struct
{
    string name;
    int votes;
} candidate;

candidate candidates[3];

int candidate_count = 3;

bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Set up candidates
    for (int i = 0; i < 3; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    // Get number of voters
    int no_voters = get_int("Number of voters: ");

    // Get each vote
    for (int i = 0; i < no_voters; i++)
    {
        string vote_name = get_string("Vote: ");

        if (!vote(vote_name))
        {
            printf("Invalid vote.\n");
        }
    }

    print_winner();
}

bool vote(string name)
{
    for (int i = 0; i < 3; i++)
    {
        if (strcmp(name, candidates[i].name) == 0)
        {
            candidates[i].votes++;
            return true;
        }
    }

    return false;
}

void print_winner(void)
{
    int highest_voter = 0;

    // Find highest number of votes
    for (int i = 0; i < 3; i++)
    {
        if (candidates[i].votes > highest_voter)
        {
            highest_voter = candidates[i].votes;
        }
    }

    // Print winner(s)
    for (int i = 0; i < 3; i++)
    {
        if (candidates[i].votes == highest_voter)
        {
            printf("%s\n", candidates[i].name);
        }
    }
}
