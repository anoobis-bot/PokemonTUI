#ifndef UTIL_PROTO_H
#define UTIL_PROTO_H

void printSpace(int nNumSpace);
void printLeftStart();
void printRightRemain(int nContentLen);
void printHeader(char sArtText[][WIDTH]);
void printRemark(char *sMessage);
int getInput(char *sInput, int nInputArrSize, char *sErrorFeedBack, int nMsgArrSize);

#endif