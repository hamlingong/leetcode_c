//
// Created by hamlingong on 2023/10/22.
//

#ifndef LEETCODE_ALGORITHM_H
#define LEETCODE_ALGORITHM_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/**
 * 1. 两个有序数组合并去重
 */
void mergeArray(int* array, int array1len, int* array2, int array2len, int** stored, int* outLen) {
  if (array == NULL || array2 == NULL) {
    return;
  }

  int p1 = 0;
  int p2 = 0;
  int index = 0;
  int current = -1;
  while (p1 < array1len && p2 < array2len) {
    printf("array[%d] = %d, array2[%d] = %d\n", p1, array[p1], p2, array2[p2]);
    if (array[p1] < array2[p2]) {
      if (current != array[p1]) {
        (*stored)[index++] = array[p1];
        current = array[p1];
      }
      p1++;
    } else if (array[p1] > array2[p2]) {
      if (current != array2[p2]) {
        (*stored)[index++] = array2[p2];
        current = array2[p2];
      }
      p2++;
    } else if (array[p1] == array2[p2]) {
      if (current != array[p1]) {
        (*stored)[index++] = array[p1];
        current = array[p1];
      }
      p1++;
      p2++;
    }
  }

  if (p1 != 0 && p1 < array1len) {
    while(p1 < array1len) {
      if (current != array[p1]) {
        (*stored)[index++] = array[p1];
        current = array[p1];
      }
      p1++;
    }
  }

  if (p2 != 0 && p2 < array2len) {
    while(p2 < array2len) {
      if (current != array2[p2]) {
        (*stored)[index++] = array2[p2];
        current = array2[p2];
      }
      p2++;
    }
  }

  *outLen = index;
  *stored = (int*) realloc(*stored, index * sizeof(int));
}

/**
 * 1. 测试两个有序数组合并去重
 */
void testMergeArray() {
  int array[] = {1, 2,3,3,6, 8};
  int array2[] = {2, 3, 5, 6, 6,7, 8, 8, 9};

  int len = sizeof(array) / sizeof(array[0]);
  int len2 = sizeof(array2) / sizeof(array2[0]);
  // calloc 函数会做初始化操作
  int* sorted = (int*) calloc(len + len2, sizeof(int));
  int outLen = -1;
  mergeArray(array, len, array2, len2, &sorted, &outLen);
  printf("testMergeArray!\n");
  for (int i = 0; i < outLen; i++) {
    printf("sorted[%d] = %d\n", i, sorted[i]);
  }
}

/**
 * 2. 有序数组中，查找某个数的个数
 */
int findTargetInArray(int* array, int len, int target) {
  if (array == NULL || len == 0) {
    return 0;
  }
  int low = 0;
  int high = len - 1;
  while (low <= high) {
    int mid = low + (high - low) / 2;
    if (array[mid] < target) {
      low = mid + 1;
    } else if (array[mid] > target) {
      high = mid -1;
    } else {
      return mid;
    }
  }
  return -1;
}

/**
 * 2. 测试有序数组中，查找某个数的个数
 */
void testFindTargetInArray() {
  int array[] = {1, 2,3,3,6, 8, 9, 11};
  int len = sizeof(array) / sizeof(array[0]);
  int target = 3;
  int count = findTargetInArray(array, len, target);
  printf("testFindTargetInArray: \n");
  printf("find: %d, count: %d\n", target, count);
}

/**
 * 3. 找出字符串中，第一个匹配的下标
 */
int findSubString(const char* src, int srcLength, const char* sub, int subLength) {
  if (src == NULL || sub == NULL) {
    return -1;
  }
  int p1 = 0;
  while ( p1 < (srcLength - subLength + 1)) {
    while (p1 < (srcLength - subLength + 1) && src[p1] != sub[0]) {
      p1++;
    }

    int p2 = 0;
    while (p1 < srcLength && src[p1] == sub[p2]) {
      p1++;
      p2++;
    }
    if (p2 == subLength) {
      return p1 - p2;
    }

    p1 = p1 - p2 + 1;
  }

  return -1;
}

/**
 * 3. 测试找出字符串中，第一个匹配的下表
 */
void testFindSubString() {
  char src[] = {'h', 'e','l','l','0'};
  char sub[] = {'l', 'l'};
  int srcLength = sizeof(src) / sizeof(src[0]);
  int subLength = sizeof(sub) / sizeof(sub[0]);
  int index = findSubString(src, srcLength, sub, subLength);
  printf("testFindSubString: \n");
  printf("index: %d\n", index);

  char src2[] = {'h', 'e','l','l','0'};
  char sub2[] = {'b', 'b'};
  int src2Length = sizeof(src2) / sizeof(src2[0]);
  int sub2Length = sizeof(sub2) / sizeof(sub2[0]);
  int index2 = findSubString(src2, src2Length, sub2, sub2Length);
  printf("testFindSubString2: \n");
  printf("index2: %d\n", index2);
}

struct ListNode {
  int value;
  struct ListNode *next;
};

/**
 * 4. 合并两个有序链表
 */
struct ListNode * mergeListNode(struct ListNode * list1, struct ListNode *list2) {
  if (list1 == NULL) {
    return list2;
  }
  if (list2 == NULL) {
    return list1;
  }
  if (list1->value < list2->value) {
    list1->next = mergeListNode(list1->next, list2);
    return list1;
  } else if (list1->value > list2->value) {
    list2->next = mergeListNode(list1, list2->next);
    return list2;
  } else {
    // 如果l1和l2的值相等，跳过l2的当前节点
    list1->next = mergeListNode(list1->next, list2->next);
    return list1;
  }
}

void printList(struct ListNode* list) {
  struct ListNode* currentList;
  currentList = list;
  while(currentList != NULL) {
    printf("list value: %d\n", currentList->value);
    currentList = currentList->next;
  }
}

/**
  * 4. 测试合并两个有序链表
  */
void testMergeListNode() {
  // 1,3,5
  struct ListNode *list1 = (struct ListNode*)malloc(sizeof(struct ListNode));
  list1->value = 1;
  list1->next = (struct ListNode*)malloc(sizeof(struct ListNode));
  list1->next->value = 3;
  list1->next->next = (struct ListNode*)malloc(sizeof(struct ListNode));
  list1->next->next->value = 5;
  list1->next->next->next = NULL;

  struct ListNode *list2 = (struct ListNode*)malloc(sizeof(struct ListNode));
  list2->value = 2;
  list2->next = (struct ListNode*)malloc(sizeof(struct ListNode));
  list2->next->value = 3;
  list2->next->next = (struct ListNode*)malloc(sizeof(struct ListNode));
  list2->next->next->value = 4;
  list2->next->next->next = NULL;

  struct ListNode* mergedList = mergeListNode(list1, list2);
  printList(mergedList);
}

/**
 * 5. 两数之和
 */
int* twoSum(const int* nums, int numsSize, int target, int* returnSize) {
  for(int i = 0; i < numsSize; ++i) {
    for(int j = i + 1; j < numsSize; ++j) {
      if(nums[i] + nums[j] == target) {
        int* ret = (int*)malloc(sizeof(int) * 2);
        ret[0] = i;
        ret[1] = j;
        *returnSize = 2;
        return ret;
      }
    }
  }
  *returnSize = 0;
  return NULL;
}

/**
 * 5. 测试两数之和
 */
void testTwoSum() {
  int nums[] = {2, 7, 11, 15};
  int target = 9;
  int returnSize;
  int* indexes = twoSum(nums, sizeof(nums) / sizeof(int), target, &returnSize);
  if (indexes != NULL) {
    printf("%d %d\n", indexes[0], indexes[1]);
    free(indexes);
  }
}

/**
 * 字母异位词 是由重新排列源单词的所有字母得到的一个新单词。
 */
bool isAnagram(char * s, char * t){
  int s_len = strlen(s);
  int t_len = strlen(t);
  if (s_len != t_len) {
    return false;
  }

  int count[26] = {0};
  for (int i = 0; i < s_len; i++) {
    count[s[i] - 'a'] ++;
    count[t[i] - 'a'] --;
  }

  for (int i = 0; i < 26; i++) {
    if (count[i] != 0) {
      return false;
    }
  }

  return true;
}

/**
 * 6. 测试字母异位词
 */
void testIsAnagram() {
  char s[4] = "abcd";
  char t[4] = "abdd";
  printf("testIsAnagram: \n");
  printf("s: %s\n", s);
  printf("t: %s\n", t);
  bool result = isAnagram(s, t);
  printf("result: %d\n", result);
}

#endif//LEETCODE_ALGORITHM_H
