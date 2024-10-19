#include "algorithm/algorithm.h"

int main() {
  // 1. 两个有序数组合并去重
  testMergeArray();
  // 2. 有序数组中，查找某个数的个数
  testFindTargetInArray();
  // 3. 找出字符串中，第一个匹配的下表
  testFindSubString();
  // 4. 合并两个有序链表
  testMergeListNode();
  // 5. 两数之和
  testTwoSum();
  // 6. 测试字母异位词
  testIsAnagram();
  // 7. 测试两个字符串，最大的公共子串
  testFindMaxSubString();
  // 8. 测试数组最大区间和
  testMaxSubArray();
  return 0;
}
