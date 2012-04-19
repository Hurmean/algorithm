#include <stdio.h>
#include <malloc.h>
#include <memory.h>
#include <stdlib.h>
#include <time.h>

/*
 * �ⷨ: ��һ����Χ���������һ���ƣ�ȡ�������ƣ�Ȼ����С��Χ����˼�����ȥ��
 */

/* �����������:
[********** Before Deal **********]
����A, ����2, ����3, ����4, ����5, ����6, ����7, ����8, ����9, ����10,
����J, ����Q, ����K, ÷��A, ÷��2, ÷��3, ÷��4, ÷��5, ÷��6, ÷��7,
÷��8, ÷��9, ÷��10, ÷��J, ÷��Q, ÷��K, ����A, ����2, ����3, ����4,
����5, ����6, ����7, ����8, ����9, ����10, ����J, ����Q, ����K, ����A,
����2, ����3, ����4, ����5, ����6, ����7, ����8, ����9, ����10, ����J,
����Q, ����K, С��, ����

[********** After Deal **********]
Person 1:
����A, ����2, ÷��3, ����9, ����J, ����Q, ����3, ����3, ÷��2, ����,
����8, ����7, ÷��A, ÷��K, ����5, ÷��4, ����7
Person 2:
С��, ����5, ÷��8, ����K, ����8, ����10, ����4, ����7, ����Q, ÷��10,
����10, ÷��Q, ����A, ����5, ÷��7, ����Q, ����6
Person 3:
����6, ����10, ����9, ����4, ����8, ����J, ����2, ����6, ����A, ����4,
÷��J, ����K, ����2, ����9, ÷��5, ����K, ÷��6
Remain:
÷��9, ����J, ����3
*/

#define POKER_NUM 54
#define REMAIN_POKER_NUM 3
#define EVERY_PERSON_POKER_NUM (POKER_NUM - REMAIN_POKER_NUM) / 3
#define PART_POKER_NUM 13
#define POKER_COLOR_NUM 4

typedef enum 
{
	// ����
	PT_DIAMONDS,
	// ÷��
	PT_CLUBS,
	// ����
	PT_HEARTS,
	// ����
	PT_SPADES,
	// С��
	PT_SMALLJOKER,
	// ����
	PT_BIGJOKER
} PokerType;

typedef struct
{
	int nNum;
	PokerType pt;
} Poker;

/*
 * ����: ���ơ�
         ѭ������(nLength - nRemainLength)�ˣ�ÿһ�˵�ѭ�����£�
         �������һ��[0, i - 1]��Χ�ڵ���nPokerIndex��
		 ���nPokerIndexС��i - 1���Ͱ�pTempPoker[nPokerIndex]��pTempPoker[i - 1]����������i��1��
         ���nPokerIndex����i - 1���Ͱ�i��1��
 * ����: Deal��
 * ����: const Poker* pPoker��ָ��һ�����飬�������������������ݡ�
 * ����: int nLength��pPoker����ĳ��ȡ�
 * ����: Poker* pPoker1��ָ���ŵ�1�����Ƶ����飬������������������ݡ�
 * ����: Poker* pPoker2��ָ���ŵ�2�����Ƶ����飬������������������ݡ�
 * ����: Poker* pPoker3��ָ���ŵ�3�����Ƶ����飬������������������ݡ�
 * ����: int nEveryPersonLength��pPoker1��pPoker2��pPoker3����ĳ��ȡ�
 * ����: Poker* pPokerRemain��ָ����ʣ��δ���Ƶ����飬������������������ݡ�
 * ����: int nRemainLength��pPokerRemain����ĳ��ȡ�
 * ����ֵ: void��
 */
void Deal(const Poker* pPoker, int nLength, Poker* pPoker1, Poker* pPoker2, Poker* pPoker3, int nEveryPersonLength,
			Poker* pPokerRemain, int nRemainLength);
void Output(const Poker* pPoker, int nLength);

int main()
{
	Poker arrPoker[POKER_NUM] =
	{
		{1, PT_DIAMONDS}, {2, PT_DIAMONDS}, {3, PT_DIAMONDS}, {4, PT_DIAMONDS}, {5, PT_DIAMONDS}, {6, PT_DIAMONDS}, {7, PT_DIAMONDS},
		{8, PT_DIAMONDS}, {9, PT_DIAMONDS}, {10, PT_DIAMONDS}, {11, PT_DIAMONDS}, {12, PT_DIAMONDS}, {13, PT_DIAMONDS},
		{1, PT_CLUBS}, {2, PT_CLUBS}, {3, PT_CLUBS}, {4, PT_CLUBS}, {5, PT_CLUBS}, {6, PT_CLUBS}, {7, PT_CLUBS},
		{8, PT_CLUBS}, {9, PT_CLUBS}, {10, PT_CLUBS}, {11, PT_CLUBS}, {12, PT_CLUBS}, {13, PT_CLUBS},
		{1, PT_HEARTS}, {2, PT_HEARTS}, {3, PT_HEARTS}, {4, PT_HEARTS}, {5, PT_HEARTS}, {6, PT_HEARTS}, {7, PT_HEARTS},
		{8, PT_HEARTS}, {9, PT_HEARTS}, {10, PT_HEARTS}, {11, PT_HEARTS}, {12, PT_HEARTS}, {13, PT_HEARTS},
		{1, PT_SPADES}, {2, PT_SPADES}, {3, PT_SPADES}, {4, PT_SPADES}, {5, PT_SPADES}, {6, PT_SPADES}, {7, PT_SPADES},
		{8, PT_SPADES}, {9, PT_SPADES}, {10, PT_SPADES}, {11, PT_SPADES}, {12, PT_SPADES}, {13, PT_SPADES},
		{14, PT_SMALLJOKER}, {15, PT_BIGJOKER}
	};
	Poker arrPoker1[EVERY_PERSON_POKER_NUM] = {0};
	Poker arrPoker2[EVERY_PERSON_POKER_NUM] = {0};
	Poker arrPoker3[EVERY_PERSON_POKER_NUM] = {0};
	Poker arrPokerRemain[REMAIN_POKER_NUM] = {0};

	printf("[********** Before Deal **********]\n");
	Output(arrPoker, POKER_NUM);
	Deal(arrPoker, POKER_NUM, arrPoker1, arrPoker2, arrPoker3, EVERY_PERSON_POKER_NUM, arrPokerRemain, REMAIN_POKER_NUM);

	printf("\n[********** After Deal **********]\n");
	printf("Person 1:\n");
	Output(arrPoker1, EVERY_PERSON_POKER_NUM);
	printf("Person 2:\n");
	Output(arrPoker2, EVERY_PERSON_POKER_NUM);
	printf("Person 3:\n");
	Output(arrPoker3, EVERY_PERSON_POKER_NUM);
	printf("Remain:\n");
	Output(arrPokerRemain, REMAIN_POKER_NUM);

	return 0;
}

void Deal(const Poker* pPoker, int nLength, Poker* pPoker1, Poker* pPoker2, Poker* pPoker3, int nEveryPersonLength,
		  Poker* pPokerRemain, int nRemainLength)
{
	int i = 0;
	int j = 0;
	int k = 0;

	int nCount1 = 0;
	int nCount2 = 0;
	int nCount3 = 0;

	int nPokerIndex = 0;
	Poker pokerTemp = {0};
	Poker* pTempPoker = (Poker*)malloc(sizeof(Poker) * nLength);

	for (i = 0; i < nLength; ++i)
	{
		pTempPoker[i] = pPoker[i];
	}

	srand((unsigned int)time(NULL));
	for (i = nLength; i > nRemainLength; --i)
	{
		nPokerIndex = rand() % i;

		++k;
		if (k == 1)
		{
			pPoker1[nCount1++] = pTempPoker[nPokerIndex];
		}
		else if (k == 2)
		{
			pPoker2[nCount2++] = pTempPoker[nPokerIndex];
		}
		else
		{
			pPoker3[nCount3++] = pTempPoker[nPokerIndex];
			k = 0;
		}

		if (nPokerIndex != i - 1)
		{
			pokerTemp = pTempPoker[nPokerIndex];
			pTempPoker[nPokerIndex] = pTempPoker[i - 1];
			pTempPoker[i - 1] = pokerTemp;
		}
	}
	
	for (i = 0; i < nRemainLength; ++i)
	{
		pPokerRemain[i] = pTempPoker[i];
	}

	free(pTempPoker);
	pTempPoker = NULL;
}

void Output(const Poker* pPoker, int nLength)
{
	const char* arrPokerNumber[PART_POKER_NUM] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
	const char* arrPokerType[POKER_COLOR_NUM] = {"����", "÷��", "����", "����"};
	const char* pchSmallJoker = "С��";
	const char* pchBigJoker = "����";
	int i = 0;
	int j = 0;
	int nShowForOneLine = 10;

	for (i = 0; i < nLength; ++i)
	{
		if (pPoker[i].nNum == 14)
		{
			printf("%s", pchSmallJoker);
		}
		else if (pPoker[i].nNum == 15)
		{
			printf("%s", pchBigJoker);
		}
		else
		{
			j = (pPoker[i].nNum - 1) % PART_POKER_NUM;
			printf("%s%s", arrPokerType[pPoker[i].pt], arrPokerNumber[j]);
		}

		if (i != nLength - 1)
		{
			printf(", ");
			if ((i + 1) % nShowForOneLine == 0)
			{
				printf("\n");
			}
		}
		else 
		{
			printf("\n");
		}
	}
}
