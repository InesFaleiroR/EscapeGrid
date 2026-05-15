#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/ranking.h"
#define RANKING_FILE "data/ranking.txt"
static int compareRanks(const void *a, const void *b) {
    return ((const RankEntry *)b)->score - ((const RankEntry *)a)->score;
}
void ensureRankingFile(void) {
    FILE *f = fopen(RANKING_FILE, "a");
    if (f) fclose(f);
}
int loadRanking(RankEntry ranks[], int maxRanks) {
    FILE *f = fopen(RANKING_FILE, "r");
    int   n = 0;
    if (!f) return 0;
    while (n < maxRanks &&
           fscanf(f, "%31[^;];%d;%d;%d\n",
                  ranks[n].name, &ranks[n].score,
                  &ranks[n].level, &ranks[n].difficulty) == 4)
        n++;
    fclose(f);
    return n;
}
void saveRanking(RankEntry ranks[], int count) {
    FILE *f = fopen(RANKING_FILE, "w");
    int   i;
    if (!f) return;
    for (i = 0; i < count; i++)
        fprintf(f, "%s;%d;%d;%d\n",
                ranks[i].name, ranks[i].score,
                ranks[i].level, ranks[i].difficulty);
    fclose(f);
}
void insertRanking(const RankEntry *entry) {
    RankEntry ranks[MAX_RANKS + 1];
    int n = loadRanking(ranks, MAX_RANKS);
    ranks[n++] = *entry;
    qsort(ranks, n, sizeof(RankEntry), compareRanks);
    if (n > MAX_RANKS) n = MAX_RANKS;
    saveRanking(ranks, n);
}
void printRankingTable(void) {
    RankEntry ranks[MAX_RANKS];
    int n = loadRanking(ranks, MAX_RANKS), i;
    if (n == 0) { printf("  Sem pontuacoes registadas ainda.\n"); return; }
    for (i = 0; i < n; i++) {
        const char *d = (ranks[i].difficulty == DIFFICULTY_EASY)  ? "FACIL"   :
                        (ranks[i].difficulty == DIFFICULTY_HARD)  ? "DIFICIL" : "MEDIO";
        printf("  %-4d %-18s %-10d %-8d %-8s\n",
               i + 1, ranks[i].name, ranks[i].score, ranks[i].level, d);
    }
}