#ifndef RANKING_H
#define RANKING_H

#include "game.h"

void ensureRankingFile(void);
int  loadRanking(RankEntry ranks[], int maxRanks);
void saveRanking(RankEntry ranks[], int count);
void insertRanking(const RankEntry *entry);
void printRankingTable(void);

#endif