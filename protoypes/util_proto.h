#ifndef UTIL_PROTO_H
#define UTIL_PROTO_H

void printSpace(int nNumSpace);
void printLeftStart();
void printRightRemain(int nContentLen);
void printBottomRemain(int currRow);
void printFillerLines(int nQuantity, int *currRow);
void printHeader(char sArtText[][WIDTH]);
void printRemark(char *sMessage);
int getInput(char *sInput, int nInputSize, char *sErrorFeedBack);

#endif