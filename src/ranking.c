#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/ranking.h"

#define RANKING_FILE "data/ranking.txt"

static int compareRanks(const void *left_ptr, const void *right_ptr) {
    const RankEntry *left_rank = (const RankEntry *)left_ptr;
    const RankEntry *right_rank = (const RankEntry *)right_ptr;
    return right_rank->score - left_rank->score;
}

void ensureRankingFile(void) {
    FILE *file_ptr = fopen(RANKING_FILE, "a");
    if (file_ptr != NULL) {
        fclose(file_ptr);
    }
}

int loadRanking(RankEntry ranks[], int maxRanks) {
    FILE *file_ptr = fopen(RANKING_FILE, "r");
    int count_val = 0;

    if (file_ptr == NULL) {
        return 0;
    }

    while (count_val < maxRanks &&
           fscanf(file_ptr, "%31[^;];%d;%d;%d\n",
                  ranks[count_val].name,
                  &ranks[count_val].score,
                  &ranks[count_val].level,
                  &ranks[count_val].difficulty) == 4) {
        count_val++;
    }

    fclose(file_ptr);
    return count_val;
}

void saveRanking(RankEntry ranks[], int count) {
    FILE *file_ptr = fopen(RANKING_FILE, "w");
    int idx_vals = 0;

    if (file_ptr == NULL) {
        return;
    }

    for (idx_vals = 0; idx_vals < count; idx_vals++) {
        fprintf(file_ptr, "%s;%d;%d;%d\n",
                ranks[idx_vals].name,
                ranks[idx_vals].score,
                ranks[idx_vals].level,
                ranks[idx_vals].difficulty);
    }

    fclose(file_ptr);
}

void insertRanking(const RankEntry *entry) {
    RankEntry ranks[MAX_RANKS + 1];
    int count_val = loadRanking(ranks, MAX_RANKS);
    int insert_idx = count_val;

    ranks[insert_idx] = *entry;
    count_val++;

    qsort(ranks, count_val, sizeof(RankEntry), compareRanks);

    if (count_val > MAX_RANKS) {
        count_val = MAX_RANKS;
    }

    saveRanking(ranks, count_val);
}

void printRankingTable(void) {
    RankEntry ranks[MAX_RANKS];
    int count_val = loadRanking(ranks, MAX_RANKS);
    int idx_vals = 0;

    if (count_val == 0) {
        printf("Sem pontuações registadas ainda.\n");
        return;
    }

    printf("%-4s %-18s %-10s %-8s %-10s\n", "Pos", "Nome", "Score", "Nivel", "Dific.");
    printf("----------------------------------------------------\n");

    for (idx_vals = 0; idx_vals < count_val; idx_vals++) {
        const char *diff_text = "MEDIO";
        if (ranks[idx_vals].difficulty == DIFFICULTY_EASY) {
            diff_text = "FACIL";
        } else if (ranks[idx_vals].difficulty == DIFFICULTY_HARD) {
            diff_text = "DIFICIL";
        }

        printf("%-4d %-18s %-10d %-8d %-10s\n",
               idx_vals + 1,
               ranks[idx_vals].name,
               ranks[idx_vals].score,
               ranks[idx_vals].level,
               diff_text);
    }
}